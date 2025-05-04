#include <cstddef>
#include <array>

#include <rigtorp/MPMCQueue.h>
#include <work_contract/work_contract.h>
#include <work_contract/work_contract_group.h>

namespace mr {

  template <typename T>
  struct Handle {
    std::optional<std::reference_wrapper<bcpp::work_contract>> contract {};
    std::reference_wrapper<T> resource;

    Handle(bcpp::work_contract& c, T& r) : contract(c), resource(r) {}

    Handle() = default;

    Handle(const Handle &) = delete;
    Handle & operator=(const Handle &) = delete;

    Handle(Handle && other) noexcept : resource(std::move(other.resource)) {
      std::swap(contract, other.contract);
    }
    Handle& operator=(Handle && other) noexcept {
      resource = std::move(other.resource);
      std::swap(contract, other.contract);
      return *this;
    }

    ~Handle() noexcept {
      if (contract.has_value()) { contract.value().get().schedule(); }
    }

    T & get() {
      return resource.get();
    }
  };

  template <typename T, std::size_t N>
  struct AsyncResourcePool {
    bcpp::work_contract_group group {};
    std::array<bcpp::work_contract, N> contracts {};
    std::array<T, N> resources {};
    rigtorp::MPMCQueue<int> idqueue {N};

    AsyncResourcePool() {
      for (int i = 0; i < N; i++) {
        contracts[i] = group.create_contract([&, i] {
          idqueue.push(i);
        }, bcpp::work_contract::initial_state::scheduled);
      }
    }

    Handle<T> acquire() {
      group.execute_next_contract();
      int i;
      idqueue.pop(i);
      return {{contracts[i]}, {resources[i]}};
    }
  };

}

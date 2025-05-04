#include <chrono>
#include <thread>
#include <print>
#include <async-pool/pool.hpp>

int main() {
  constexpr int size = 10;

  mr::AsyncResourcePool<int, size> pool;

  // write
  for (int i = 0; i < size; i++) {
    auto reshandle = pool.acquire();
    reshandle.get() = i;
  }

  std::vector<std::thread> threads(size);

  // read
  std::array<std::atomic_uint64_t, size> counters;
  for (int i = 0; i < size; i++) {
    threads[i] = std::thread([&pool, &counters] {
      // std::this_thread::sleep_for(std::chrono::milliseconds(i));
      auto reshandle = pool.acquire();
      counters[reshandle.get()]++;
    });
  }

  for (int i = 0; i < size; i++) {
    threads[i].join();
  }

  for (int i = 0; i < size; i++) {
    if (counters[i].load() != 0) {
      std::println("data[{}] = {}", i, counters[i].load());
    }
  }
}

cmake_minimum_required(VERSION 4.0.0)
project(mr-async-pool)

include(cmake/deps.cmake)

set(LIB_NAME ${CMAKE_PROJECT_NAME}-lib)
add_library(${LIB_NAME} INTERFACE "")
target_include_directories(${LIB_NAME} INTERFACE include)
target_compile_features(${LIB_NAME} INTERFACE cxx_std_23)
target_link_libraries(${LIB_NAME} INTERFACE work_contract MPMCQueue)

set(TESTS_EXE_NAME ${CMAKE_PROJECT_NAME}-tests)
add_executable(${TESTS_EXE_NAME} tests/main.cpp)
target_link_libraries(${TESTS_EXE_NAME} PUBLIC ${LIB_NAME})


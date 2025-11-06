cmake_minimum_required(VERSION 3.28)
project(cpp-minibench)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")
set(BENCHMARK_USE_BUNDLED_GTEST OFF CACHE BOOL "")
FetchContent_Declare(
		benchmark
		GIT_REPOSITORY https://github.com/google/benchmark.git
		GIT_TAG v1.7.1  # You can choose the latest stable release
)
FetchContent_MakeAvailable(benchmark)

add_executable(cpp-minibench main.cpp)
target_link_libraries(cpp-minibench PRIVATE benchmark::benchmark)
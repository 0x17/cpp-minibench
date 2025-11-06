cmake_minimum_required(VERSION 3.28)
project(cpp-minibench)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")
set(BENCHMARK_USE_BUNDLED_GTEST OFF CACHE BOOL "")
FetchContent_Declare(
		benchmark
		GIT_REPOSITORY https://github.com/CodSpeedHQ/codspeed-cpp # Target the codspeed cpp repository
		SOURCE_SUBDIR google_benchmark # Make sure to target the google_benchmark subdirectory
		GIT_TAG main # Or chose a specific version or git ref, check the releases page on the repository
)

FetchContent_MakeAvailable(benchmark)

add_executable(cpp-minibench main.cpp) # main2.cpp)
target_link_libraries(cpp-minibench PRIVATE benchmark::benchmark)
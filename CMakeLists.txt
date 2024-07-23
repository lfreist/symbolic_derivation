cmake_minimum_required(VERSION 3.2)
project(symderiv)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

option(BUILD_BENCHMARKS "Build benchmarks using Google Benchmark" ON)
option(BUILD_TESTS "Build tests using Google Test" ON)

add_subdirectory(src)

add_subdirectory(example)

if (BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif ()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
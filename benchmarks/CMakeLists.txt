FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.4
)

set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_USE_BUNDLED_GTEST OFF)
set(BENCHMARK_ENABLE_ASSEMBLY_TESTS OFF)

FetchContent_MakeAvailable(benchmark)

add_executable(derivatives_benchmark derivatives.cpp)
target_link_libraries(derivatives_benchmark benchmark::benchmark)

add_executable(evaluation_benchmark evaluation.cpp)
target_link_libraries(evaluation_benchmark benchmark::benchmark)

add_executable(parsing_benchmark parsing.cpp)
target_link_libraries(parsing_benchmark benchmark::benchmark)
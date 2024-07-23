enable_testing()

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(gtest)

add_executable(tokenizer_test tokenizer_test.cpp)
target_include_directories(tokenizer_test PRIVATE ../include)
target_link_libraries(tokenizer_test PRIVATE fsd::parser gtest gtest_main)

add_executable(parser_test parser_test.cpp)
target_link_libraries(parser_test PRIVATE fsd::parser gtest gtest_main)
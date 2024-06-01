cmake_minimum_required(VERSION 3.2)
project(symderiv)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(src)

add_executable(main main.cpp include/fsd/term.h)
target_include_directories(main PRIVATE include)
target_link_libraries(main PRIVATE fsd)
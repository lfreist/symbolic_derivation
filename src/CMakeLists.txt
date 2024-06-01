add_library(fsd constant.cpp parser.cpp variable.cpp operations.cpp term.cpp)
target_include_directories(fsd PUBLIC ../include)
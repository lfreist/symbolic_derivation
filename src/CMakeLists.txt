add_library(fsd SHARED constant.cpp variable.cpp operations.cpp term.cpp)
target_include_directories(fsd PUBLIC ../include)
add_library(fsd::fsd ALIAS fsd)

add_library(fsd_static STATIC constant.cpp variable.cpp operations.cpp term.cpp)
target_include_directories(fsd_static PUBLIC ../include)
add_library(fsd::fsd_static ALIAS fsd_static)

# --- parser -----------------------------------------------------------------------------------------------------------
add_library(parser SHARED parser.cpp tokenizer.cpp)
target_include_directories(parser PUBLIC ../include)
target_link_libraries(parser PUBLIC fsd::fsd)
add_library(fsd::parser ALIAS parser)

add_library(parser_static STATIC parser.cpp tokenizer.cpp)
target_include_directories(parser_static PUBLIC ../include)
target_link_libraries(parser_static PUBLIC fsd::fsd_static)
add_library(fsd::parser_static ALIAS parser_static)
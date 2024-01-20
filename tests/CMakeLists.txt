cmake_minimum_required(VERSION 3.5)
project(test VERSION 0.0.1)

add_subdirectory(Catch2)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/..)
get_filename_component(LEXER ../lexer ABSOLUTE)
include_directories(${LEXER})
add_executable(test test.cpp ${LEXER}/lexer.cpp)

target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
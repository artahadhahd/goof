cmake_minimum_required(VERSION 3.10)
set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
project(goof)
add_executable(goof ${sources})

include_directories(lexer)
target_sources(goof PUBLIC
    ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/lexer/lexer.cpp
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS ${PROJECT_SOURCE_DIR}
)

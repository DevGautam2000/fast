cmake_minimum_required(VERSION 3.21)
project(fast)

set(CMAKE_CXX_STANDARD 20)

add_library(fastl
        src/Lexer.cpp
        src/Lexer.hpp
        )

add_executable(main src/start.cpp)

target_link_libraries(main fastl)

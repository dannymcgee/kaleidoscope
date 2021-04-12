cmake_minimum_required(VERSION 3.19)
project(kaleidoscope)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    kaleidoscope
    main.cpp
    lexer/lexer.h
    lexer/lexer.cpp
    ast/expr.hpp
    ast/stmt.hpp
    parser/parser.h
    parser/parser.cpp
)

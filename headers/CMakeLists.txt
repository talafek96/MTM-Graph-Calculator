cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0)

set(CMAKE_C_FLAGS "-std=c++11 -Wall -pedantic-errors -Werror -g")
add_executable(test test.cpp graph.cpp GraphLexer.cpp GraphParser.cpp Lexer.cpp Exception.cpp) 
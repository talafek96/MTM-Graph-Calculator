cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0)

set(CMAKE_C_FLAGS "-std=c++11 -Wall -pedantic-errors -Werror -g")
add_executable(calculator main.cpp Lexer.cpp GraphParser.cpp GraphLexer.cpp graph.cpp CalcParser.cpp CalcLexer.cpp Exception.cpp) 
cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0)

set(CMAKE_C_FLAGS "-std=c++11 -Wall -pedantic-errors -Werror -g")
add_executable(gcalc main.cpp Lexer.cpp GraphParser.cpp GraphLexer.cpp GraphClass.cpp CalcParser.cpp CalcLexer.cpp Exception.cpp) 
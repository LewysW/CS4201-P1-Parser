cmake_minimum_required(VERSION 3.9)
project(CS4201_P1_Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS4201_P1_Parser main.cpp Pattern.h Lexer.cpp Lexer.h LexException.h Token.cpp Token.h)
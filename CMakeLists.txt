cmake_minimum_required(VERSION 3.9)
project(CS4201_P1_Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(CS4201_P1_Parser src/main.cpp src/Pattern.h src/Lexer.cpp src/Lexer.h src/LexException.h src/Token.cpp src/Token.h)
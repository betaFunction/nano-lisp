cmake_minimum_required(VERSION 3.4)
project(nanolisp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/executable.cpp src/nanolisp.cpp src/lexer.cpp src/parser.cpp)
add_executable(nanolisp ${SOURCE_FILES})
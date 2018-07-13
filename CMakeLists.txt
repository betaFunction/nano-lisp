cmake_minimum_required(VERSION 3.8)
project(nano-pass-lisp)
# required base

set(CMAKE_CXX_STANDARD 14)
# include_directories(../include)
include_directories(include)

add_subdirectory(lib/googletest)

add_subdirectory(src)
add_subdirectory(test)



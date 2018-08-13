cmake_minimum_required(VERSION 3.8)


project(nano-pass-lisp CXX)
# required base
set(CMAKE_MODULE_PATH /home/luoxing/lib/cmake/llvm/)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(~/include)

link_directories(~/lib)

#set(CMAKE_CXX_FLAGS "-stdlib=libc++")
add_subdirectory(lib/googletest)

add_subdirectory(src)
add_subdirectory(test)



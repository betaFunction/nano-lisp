
# learing shodow project cmakelists


project(nano-pass-lisp CXX)
set(PLISP_VERSION_MAJOR 0)
set(PLISP_VERSION_MINOR 0)
set(PLISP_VERSION_BUILD 1)
message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "System version: ${CMAKE_SYSTEM_VERSION}")
message(STATUS "System processor: ${CMAKE_SYSTEM_PROCESSOR}")


cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

## ensure linux environment (CMAKE_SYSTEM_NAME == "Linux")
if (NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux"))
  message(FATAL_ERROR "Shadow requires Linux environment.")
endif(NOT (CMAKE_SYSTEM_NAME STREQUAL "Linux"))

## ensure out of source build
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Shadow requires an out-of-source build")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})
message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

## get general includes
include(CheckIncludeFile)
include(CheckFunctionExists)
include(CheckLibraryExists)
include(TestBigEndian)
include(ShadowTools)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/shd-config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/shd-config.h DESTINATION include/)



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



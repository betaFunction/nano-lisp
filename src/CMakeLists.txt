

add_library(nanolisp interpreter.cc parser.cc)
#target_include_directories(nanolisp - lib INTERFACE src / include)


set(REPL_SOURCE_FILES main.cc)
add_executable(repl ${REPL_SOURCE_FILES})
#target_include_directories(nanolisp PUBLIC src / include)
target_link_libraries(repl nanolisp)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

add_executable(diagnostics diagnostics.cc)
target_link_libraries(diagnostics clang LLVMSupport z rt dl tinfo pthread m)

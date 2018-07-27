
set(CMAKE_CXX_FLAGS "-stdlib=libc++")
add_library(nanolisp interpreter.cc lexer.cc parser.cc)
#target_include_directories(nanolisp - lib INTERFACE src / include)


set(REPL_SOURCE_FILES main.cc)
add_executable(repl ${REPL_SOURCE_FILES})
#target_include_directories(nanolisp PUBLIC src / include)
target_link_libraries(repl nanolisp)

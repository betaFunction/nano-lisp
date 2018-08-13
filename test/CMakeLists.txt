
        #test_parser.cc
        #test_interpreter.cc
        #test_main.cc


#set(CMAKE_CXX_FLAGS "-stdlib=libc++")

function(add_nano_test arg1)
add_executable(test_${arg1} test_${arg1}.cc)
target_link_libraries(test_${arg1} gtest nanolisp)
add_test(test_${arg1} test_${arg1})
  
endfunction(add_nano_test)

add_nano_test(lexer)
add_nano_test(parser)
add_nano_test(interpreter)



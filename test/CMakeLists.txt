
        #test_parser.cc
        #test_interpreter.cc
        #test_main.cc


set(CMAKE_CXX_FLAGS "-stdlib=libc++")

function(add_nano_test arg1)
add_executable(test_${arg1} test_${arg1}.cc)
target_link_libraries(test_${arg1} gtest nanolisp)
add_test(test_${arg1} test_${arg1})
  
endfunction(add_nano_test)

# add_executable(test_lexer test_lexer.cc)
# target_link_libraries(test_lexer gtest nanolisp)
# add_test(test_lexer test_lexer)
add_nano_test(lexer)
add_nano_test(parser)
add_nano_test(interpreter)

# add_executable(test_parser test_parser.cc)
# target_link_libraries(test_parser nanolisp gtest c++)
# add_test(test_parser test_parser)


# add_executable(test_parser test_parser.cc)
# target_link_libraries(test_parser nanolisp gtest c++)
# add_test(test_parser test_parser)

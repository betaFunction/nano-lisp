
        #test_parser.cc
        #test_interpreter.cc
        #test_main.cc


set(CMAKE_CXX_FLAGS "-stdlib=libc++")
add_executable(test_lexer test_lexer.cc)
target_link_libraries(test_lexer gtest nanolisp)
add_test(test_lexer test_lexer)


add_executable(test_parser test_parser.cc)
target_link_libraries(test_parser nanolisp gtest c++)
add_test(test_parser test_parser)

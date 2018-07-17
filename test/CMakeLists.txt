set(GTEST_FILES
        test_parser.cc
        test_interpreter.cc
        test_main.cc
        )

add_executable(nanolisp-test ${GTEST_FILES})
target_link_libraries(nanolisp-test gtest nanolisp-lib)
target_include_directories(nanolisp-test
        INTERFACE gtest
        PUBLIC include
        PUBLIC src/include)

add_test(${GTEST_FILES} nanolisp-test)

add_executable(test_lexer test_lexer.cc)
target_link_libraries(test_lexer gtest nanolisp-lib)
target_include_directories(test_lexer
	        INTERFACE gtest)
add_test(test_lexer test_lexer)

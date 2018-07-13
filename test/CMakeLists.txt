

set(GTEST_FILES
	        test_lexer.cc
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

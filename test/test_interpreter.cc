//
// Created by Francesco Fiduccia on 13/04/16.
//

#include "gtest/gtest.h"
#include "nanolisp/checkers.hpp"

using namespace std;

TEST(INTERPRETER, SUM_OPERATION_WITH_TWO_OPERANDS) {
    string program = "(def a 5)"
            "(def b 6)"
            "(print (sum a b))";
    string output = "11";
    EXPECT_TRUE(check_interpreter(program, output));

}

TEST(INTERPRETER, SUM_OPERATION_THREE_OPERAND_ONE_IS_ANOTHER_SUM) {
    string program = "(def a 5)"
            "(def b 6)"
            "(print (sum a b (sum a b)))";

    string output = "22";
    EXPECT_TRUE(check_interpreter(program, output));
}

TEST(INTERPRETER, SUM_OPERATION_HIERARCHICAL_MULTIPLE_OPERANDS) {
    string program = "(def a 5)"
            "(def b 6)"
            "(print (sum a b (sum a b) (sum a 1 2 3 4 5)))";

    string output = "42";
    EXPECT_TRUE(check_interpreter(program, output));
}



TEST(INTERPRETER, SUM_OPERATION_WRONG_PARANTHESIS) {
    // SHOULD FAIL

    string program = "(def a 5)"
            "(def b 6)"
            /* Missing 1 right parenthesis at the end */
            "(print (sum a b (sum a b) (sum a 1 2 3 4 5))";

    string output = "42";
    EXPECT_FALSE(check_interpreter(program, output));
}

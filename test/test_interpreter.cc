//
// Created by Francesco Fiduccia on 13/04/16.
//

#include "gtest/gtest.h"
#include "nanolisp/checkers.hpp"
#include "nanolisp/interpreter.h"
using namespace std;
using namespace nl;
class QueueTest : public ::testing::Test {
protected:
  void SetUp() override{
    runtime = nanolisp_runtime::create();
  }
  nl::nanolisp_runtime* runtime;
};

TEST_F(QueueTest, SUM_OPERATION_WITH_TWO_OPERANDS) {
    string program = "(defvar a 5)"
            "(defvar b 6)"
            "(print (sum a b))";
    string output = "11";

    

    
    nl::nl_expression* root = nl::parse(program);
    
    
    nl::nl_expression *result = runtime->eval(root);
    nl::nl_expression *expact = new nl_number_expression(11);
    ASSERT_TRUE(*result == *expact);

}

// TEST(INTERPRETER, SUM_OPERATION_THREE_OPERAND_ONE_IS_ANOTHER_SUM) {
//     string program = "(def a 5)"
//             "(def b 6)"
//             "(print (sum a b (sum a b)))";

//     string output = "22";
//     EXPECT_TRUE(check_interpreter(program, output));
// }

// TEST(INTERPRETER, SUM_OPERATION_HIERARCHICAL_MULTIPLE_OPERANDS) {
//     string program = "(def a 5)"
//             "(def b 6)"
//             "(print (sum a b (sum a b) (sum a 1 2 3 4 5)))";

//     string output = "42";
//     EXPECT_TRUE(check_interpreter(program, output));
// }



// TEST(INTERPRETER, SUM_OPERATION_WRONG_PARANTHESIS) {
//     // SHOULD FAIL

//     string program = "(def a 5)"
//             "(def b 6)"
//             /* Missing 1 right parenthesis at the end */
//             "(print (sum a b (sum a b) (sum a 1 2 3 4 5))";

//     string output = "42";
//     EXPECT_FALSE(check_interpreter(program, output));
// }
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

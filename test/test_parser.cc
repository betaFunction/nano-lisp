//
// Created by Francesco Fiduccia on 13/04/16.
//
#include "gtest/gtest.h"
#include "nanolisp/checkers.hpp"
#include "nanolisp/parser.h"

using namespace std;
using namespace nl;
void equal_expression(nl_expression * left, nl_expression * right){
  if (left == right){
	return ;
  }
  ASSERT_TRUE(left->operator==(*right));
}
TEST(PARSER, DEFINITION_OF_VARIABLE) {

  vector<nl::lex_token> expected_lexer =  nl::lex_token_builder()
	.add_lp(0)
	.add_id("defvar")
	.add_id("a")
	.add_number(5)
	.add_rp(0)
	.build();
  
    
  nl_list_expression *expected_expression = nl_list_expression::create()->
	addArgId("defvar")->
	addArgString("a")->
	addArgNumber(5);

  check_parser("(defvar a 5)", expected_lexer, expected_expression);
  
	//nl::nl_expression* result = nl::parse(input);
}

TEST(PARSER, DEFINITION_WHICH_SHOULD_NOT_MAKE_SENSE) {
  nl_list_expression *expression = nl_list_expression::create()
            ->addArgId("defun")
            ->addArgString("a")
            ->addArgNumber(5)
            ->addArgString("ciao");

  vector<nl::lex_token> expected_lexer =  nl::lex_token_builder()
    .add_lp(0)
      .add_id("defun")
      .add_id("a")
      .add_number(5)
      .add_string("ciao")
      .add_rp(0)
    .build();

  check_parser("(defun a 5 \"ciao\")", expected_lexer, expression);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

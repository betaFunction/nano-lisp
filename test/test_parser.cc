//
// Created by Francesco Fiduccia on 13/04/16.
//
#include "gtest/gtest.h"
#include "nanolisp/checkers.hpp"

using namespace std;
using namespace nl;

TEST(PARSER, DEFINITION_OF_VARIABLE) {

  vector<nl::lex_token> expected_lexer =  nl::lex_token_builder()
      .add_lp(0)
      .add_id("def")
      .add_number(5)
      .add_rp(0)
      .build();
    
    
    nl_list_expression *expression = nl_list_expression::create()->
            addArgId("def")->
            addArgString("a")->
            addArgNumber(5);
    EXPECT_TRUE(check_parser("(def a 5)", expected_lexer, expression));
}

TEST(PARSER, DEFINITION_WHICH_SHOULD_NOT_MAKE_SENSE) {
  nl_list_expression *expression = nl_list_expression::create()
            ->addArgId("def")
            ->addArgString("a")
            ->addArgNumber(5)
            ->addArgString("ciao");

  vector<nl::lex_token> expected_lexer =  nl::lex_token_builder()
    .add_lp(0)
      .add_id("def")
      .add_id("a")
      .add_number(5)
      .add_string("ciao")
      .add_rp(0)
    .build();

    check_parser("(def a 5 \"ciao\")", expected_lexer, expression);
}

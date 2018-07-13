//
// Created by crypt on 17/10/17.
//
#include "nanolisp/lexer.h"
#include "nanolisp/checkers.hpp"
#include "gtest/gtest.h"

using namespace std;
vector<nl::lex_token *> result{};

TEST(LEXER, PARENTHESIS_STRING) {
  vector<nl::lex_token *> result = nl::lex_token_builder()
    .add_lp()
    .add_string("falcon")
    .add_rp()
    .build();
    EXPECT_TRUE(check_lexer(true, "(\"falcon\")", result));
}

TEST(LEXER, PARENTHESIS_TWO_STRINGS) {
  vector<nl::lex_token *> result = nl::lex_token_builder()
    .add_lp()
    .add_string("falcon")
    .add_string("space-x")
    .add_rp()
    .build();
    EXPECT_TRUE(check_lexer(true, "(\"falcon\"\"space-x\")", result));
}


TEST(LEXER, PARENTHESIS_TWO_STRINGS_ONE_NUMBER) {

  vector<nl::lex_token *> result = nl::lex_token_builder()
    .add_lp()
    .add_string("falcon")
    .add_string("space-x")
    .add_number(123451)
    .add_rp()
    .build();

    EXPECT_TRUE(check_lexer(true, "(\"falcon\"\"space-x\"   123451)", result));
}

TEST(LEXER, PARANTHESIS_TWO_SYMBOLS_TWO_STRINGS_NUMBER) {
  vector<nl::lex_token *> result = nl::lex_token_builder()
    .add_lp()
    .add_id("Hello")
    .add_id("World")
    .add_string("falcon")
    .add_string("space-x")
    .add_number(123451)
    .add_rp()
    .build();

    EXPECT_TRUE(check_lexer(true, "(Hello World \"falcon\"\"space-x\"   123451)", result));
}

TEST(LEXER, PARANTHESIS_TWO_LINE_STRING) {
  result = nl::lex_token_builder()
    .add_string("falcon\r\nsuper hero")
    .add_rp()
    .build();
    EXPECT_TRUE(check_lexer(true, "(\"falcon\r\nsuper hero\")", result));
}


TEST(LEXER, PARANTHESIS_MULTIPLE_LINES_STRING) {
  result = nl::lex_token_builder()
    .add_string("falcon\r\nsuper\r\nhero")
    .add_rp()
    .build();
  EXPECT_TRUE(check_lexer(true, "(\"falcon\r\nsuper\r\nhero\")", result));
}

//
// Created by crypt on 17/10/17.
//
#include "nanolisp/lexer.h"
//#include "nanolisp/checkers.hpp"
#include "gtest/gtest.h"

using namespace std;
vector<nl::lex_token *> result{};
void check_lexer(bool value, std::string input, vector<nl::lex_token> &  expected){
  EXPECT_TRUE(value);

  vector<nl::lex_token> result = nl::lexical(input);;
  
  ASSERT_EQ(result.size(), expected.size());
  for(int i=0;i<result.size();i++){
    if(result[i].symbol == nl::lex_symbol::STRING){
      std::cout << result[i].string_value
		<< ","
		<< expected[i].string_value << std::endl;
    }
    ASSERT_EQ(result[i], expected[i]);
    
  }
}

TEST(LEXER, PARENTHESIS_DUMP) {
  vector<nl::lex_token> result = nl::lex_token_builder()
    .add_lp(0)
    .add_rp(0)
    .build();

  
  check_lexer(true, "()", result);
}

TEST(LEXER, PARENTHESIS_EQUAL) {
  vector<nl::lex_token> result = nl::lex_token_builder()
    .add_string("falcon")
    .build();
  vector<nl::lex_token> expected = nl::lex_token_builder()
    .add_string("falcon")
    .build();
  ASSERT_EQ(result[0], expected[0]);

}

TEST(LEXER, PARENTHESIS_ADD_STRING) {
  vector<nl::lex_token> result = nl::lex_token_builder()
    .add_string("falcon")
    .build();
  ASSERT_EQ(result.size(), 1);
  
}
    
TEST(LEXER, PARENTHESIS_STRING) {
  vector<nl::lex_token> result = nl::lex_token_builder()
    .add_lp(0)
    .add_string("falcon")
    .add_rp(0)
    .build();

  
  check_lexer(true, "(\"falcon\")", result);
}

TEST(LEXER, PARENTHESIS_TWO_STRINGS) {
  vector<nl::lex_token> result = nl::lex_token_builder()
    .add_lp(0)
    .add_string("falcon")
    .add_string("space-x")
    .add_rp(0)
    .build();
  check_lexer(true, "(\"falcon\"\"space-x\")", result);
}


TEST(LEXER, PARENTHESIS_TWO_STRINGS_ONE_NUMBER) {

  vector<nl::lex_token> result = nl::lex_token_builder()
    .add_lp(0)
    .add_string("falcon")
    .add_string("space-x")
    .add_number(123451)
    .add_rp(0)
    .build();

  check_lexer(true, "(\"falcon\"\"space-x\"   123451)", result);
}

TEST(LEXER, PARANTHESIS_TWO_SYMBOLS_TWO_STRINGS_NUMBER) {
  vector<nl::lex_token > result = nl::lex_token_builder()
    .add_lp(0)
    .add_id("Hello")
    .add_id("World")
    .add_string("falcon")
    .add_string("space-x")
    .add_number(123451)
    .add_rp(0)
    .build();

  check_lexer(true, "(Hello World \"falcon\"\"space-x\"   123451)", result);
}

TEST(LEXER, PARANTHESIS_TWO_LINE_STRING) {
  vector<nl::lex_token >  result = nl::lex_token_builder()
    .add_lp(0)
    .add_string("falcon\r\nsuper hero")
    .add_rp(0)
    .build();

  check_lexer(true, "(\"falcon\r\nsuper hero\")", result);
}


TEST(LEXER, PARANTHESIS_MULTIPLE_LINES_STRING) {
  vector<nl::lex_token > result = nl::lex_token_builder()
    .add_lp(0)
    .add_string("falcon\r\nsuper\r\nhero")
    .add_rp(0)
    .build();
  check_lexer(true, "(\"falcon\r\nsuper\r\nhero\")", result);
}

//
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

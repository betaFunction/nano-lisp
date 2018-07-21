//
// Created by crypt on 17/10/17.
//

#ifndef NANOLISP_CHECKERS_HPP
#define NANOLISP_CHECKERS_HPP

//
// Created by Francesco Fiduccia on 13/04/16.
//
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "interpreter.h"

void check_lexer(std::string input, vector<nl::lex_token> &  expected){

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

void check_parser(string input,
				  std::vector<nl::lex_token> &expected_lexer,
				  nl::nl_list_expression *expected_expression) {
  nl::nl_expression * result = nl::parse(expected_lexer);
  check_lexer(input, expected_lexer);
  ASSERT_TRUE(result->isList());
  nl::nl_list_expression *result1 = (nl::nl_list_expression *)result;
  
  //ASSERT_EQ(*expected_expression, *result);
  for(int i=0;i<result1->size() ;i++){
	ASSERT_TRUE(result1->arguments[i]->operator==(*expected_expression->arguments[i]));
  }


}

static bool check_interpreter(std::string &program, std::string &expected) {
  return false;
}

#endif // NANOLISP_CHECKERS_HPP

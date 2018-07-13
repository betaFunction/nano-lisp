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
#include "interpreter.h"

static bool check_lexer(bool match, std::string input,
                        std::vector<nl::lex_token *> &expected) {
  return false;
}

static bool check_parser(string input,
                         std::vector<nl::lex_token *> &expected_lexer,
                         nl::nl_expression *expected_parser) {
  return false;
}

static bool check_interpreter(std::string &program, std::string &expected) {
  return false;
}

#endif // NANOLISP_CHECKERS_HPP

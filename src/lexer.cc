//
// Created by crypt on 4/9/2016.
//

#include <vector>
#include <string>
#include <iostream>
#include "nanolisp/lexer.h"

using namespace std;
namespace nl {
vector<string> lex_symbols{ "NUMBER", "STRING", "ID", "LP", "RP" };

lex_token::lex_token(lex_symbol _symbol) : symbol(_symbol), start(0), end(0) {};

lex_token::lex_token(lex_symbol _symbol, size_t _start, size_t _end)
    : symbol(_symbol), start(_start), end(_end) {};

lex_token *lexer_string(string &input, size_t start) {
  size_t i = start + 1;
  char c = input.at(i);
  while (c != '"') {
    i++;
    c = input.at(i);
  }
  size_t end = i;
  lex_token *token = new lex_token(lex_symbol::STRING, start, end);
  token->string_value = input.substr(start + 1, end - start - 1);
  return token;
}

lex_token *lexer_number(string &input, size_t start) {
  size_t i = start + 1;
  char c = input.at(i);
  while (isdigit(c)) {
    i++;
    c = input.at(i);
  }
  if (c == '.') {
    i++;
    while (isdigit(c)) {
      i++;
      c = input.at(i);
    }
  }
  size_t end = i - 1;
  lex_token *token = new lex_token(lex_symbol::NUMBER, start, end);
  token->double_value = stod(input.substr(start, end - start + 1));
  return token;
}

lex_token *lexer_id(string &input, size_t start) {
  size_t i = start + 1;
  char c = input.at(i);
  while (isalnum(c) || c == '_') {
    i++;
    c = input.at(i);
  }
  size_t end = i - 1;
  lex_token *token = new lex_token(lex_symbol::ID, start, end);
  token->id_name = input.substr(start, end - start + 1);
  return token;
}

void lexical(string &input, vector<lex_token *> &tokens) {

  for (size_t i = 0; i < input.length(); ++i) {
    char c = input.at(i);
    if (isalpha(c)) {
      // SYMBOL
      lex_token *token = lexer_id(input, i);
      tokens.push_back(token);
      i = token->end;
    } else if (isdigit(c) || c == '-') {
      // NUMBER
      lex_token *token = lexer_number(input, i);
      tokens.push_back(token);
      i = token->end;
    } else if (c == '"') {
      // STRING
      lex_token *token = lexer_string(input, i);
      tokens.push_back(token);
      i = token->end;
    } else if (c == '(') {
      lex_token *token = new lex_token(lex_symbol::LP, i, i);
      tokens.push_back(token);
    } else if (c == ')') {
      lex_token *token = new lex_token(lex_symbol::RP, i, i);
      tokens.push_back(token);
    } else if (isblank(c)) {
      // nothing to do
    } else {
      cout << "unrecognized character '" << c
           << "' found in input at position: " << i << endl;
      cout << "####" << input << "####" << input.substr(0, i) << "^" << c << "^"
           << input.substr(i + 1, input.length()) << "####" << endl;
    }
  }
};
}

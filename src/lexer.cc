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

vector<lex_token> lexical(string &input) {

  lex_token_builder builder;
  size_t i = 0;
  for (size_t i = 0; i < input.length(); ++i) {
    char c = input.at(i);
    if (isalpha(c)) {
      // SYMBOL
      builder.add_id(input, i);
      i = builder.end();
    } else if (isdigit(c) || c == '-') {
      // NUMBER
      builder.add_number(input, i);
      i = builder.end();
    } else if (c == '"') {
      // STRING
      builder.add_string(input, i);
      i = builder.end();
    } else if (c == '(') {
      builder.add_lp(i);
    } else if (c == ')') {
      builder.add_rp(i);
    } else if (isblank(c)) {
      // nothing to do
    } else {

      cout << "unrecognized character '" << c
           << "' found in input at position: " << i << endl;
      cout << "####" << input << "####" << input.substr(0, i) << "^" << c << "^"
           << input.substr(i + 1, input.length()) << "####" << endl;
      assert(false);
    }
  }
  return builder.build();
};
}

//
// Created by Francesco Fiduccia on 11/04/16.
//

#ifndef NANOLISP_LEXER_H_H
#define NANOLISP_LEXER_H_H
#include <cstddef>
#include <string>
#include <vector>
#include <assert.h>
#include <boost/operators.hpp>

using namespace std;
namespace nl {
enum lex_symbol {
  NUMBER,
  STRING,
  ID,
  LP,
  RP
};

extern vector<string> lex_symbols;
struct lex_token : public boost::equality_comparable<lex_token> {
public:
  lex_symbol symbol;
  size_t start;
  size_t end;
  double double_value;
  string string_value;
  string id_name;

public:
  lex_token(lex_symbol _symbol);

  lex_token(lex_symbol _symbol, size_t _start, size_t _end);

  inline bool operator==(const lex_token &other) const {
    if (this->symbol != other.symbol) {
      return false;
    }
    switch (this->symbol) {
    case STRING:
      return this->string_value == other.string_value;
    case ID:
      return this->id_name == other.id_name;
    case NUMBER:
      return this->double_value == other.double_value;
    case LP:
    case RP:
      return true;
    default:
      assert(false && "");
      return false;
    }
  }
};

void lexical(string &input, vector<lex_token *> &tokens);

struct lex_token_builder {
  lex_token *_token;
  lex_token_builder() {}
  lex_token_builder &add_lp() { return *this; }

  lex_token_builder &add_rp() { return *this; }

  lex_token_builder &add_id(std::string v) { return *this; }

  lex_token_builder &add_string(std::string v) { return *this; }

  lex_token_builder &add_number(int v) { return *this; }

  static lex_token_builder *
  new_lex_token_builder_with_symbol(lex_symbol symbol) {
    lex_token_builder *builder = new lex_token_builder();
    builder->_token = new lex_token(symbol);
    return builder;
  }
  lex_token_builder *with_string(std::string value) {
    _token->string_value = value;
    return this;
  }
  lex_token_builder *with_number(double value) {
    _token->double_value = value;
    return this;
  }
  lex_token_builder *with_id(string value) {
    _token->id_name = value;
    return this;
  }

  std::vector<lex_token *> build() {
    std::vector<lex_token *> token;
    return token;
  }
};
}
#endif // NANOLISP_LEXER_H_H

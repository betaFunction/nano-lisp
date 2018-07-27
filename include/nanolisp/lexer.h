//
// Created by Francesco Fiduccia on 11/04/16.
//
#pragma once
#include <cstddef>
#include <string>
#include <vector>
#include <assert.h>
#include <boost/operators.hpp>
#include <iostream>
using namespace std;
namespace nl {
enum lex_symbol {
  NUMBER,
  STRING,
  ID,
  LP,
  RP
};


struct lex_token : public boost::equality_comparable<lex_token> {
public:
  lex_symbol symbol;
  size_t start;
  size_t end;
  int64_t number_value;
  string string_value;
  string id_name;

public:
  lex_token(lex_symbol _symbol);

  lex_token(size_t _start, size_t _end) : start(_start), end(_end) {}

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
      return this->number_value == other.number_value;
    case LP:
    case RP:
      return true;
    default:
      assert(false && "");
      return false;
    }
  }
};

struct lex_token_builder {
  vector<lex_token> _tokens;
  lex_token_builder() {}
  lex_token_builder &add_lp(size_t i) { return push_token(LP, i); }
  lex_token_builder &add_rp(size_t i) { return push_token(RP, i); }

  lex_token_builder &add_id(std::string v) {
    lex_token token(0, 0);
    token.symbol = lex_symbol::ID;
    token.id_name = v;
    _tokens.push_back(token);
    return *this;
  }
  lex_token_builder &add_id(std::string const &input, size_t start, size_t end) {
    lex_token token(start, end);
    token.symbol = lex_symbol::ID;
    token.id_name = input.substr(start, end - start + 1);
    _tokens.push_back(token);
    return *this;
  }
  lex_token_builder &add_id(std::string const &input, size_t start) {
    size_t i = start + 1;
    char c = input.at(i);
    while (isalnum(c) || c == '_') {
      i++;
      c = input.at(i);
    }
    size_t end = i - 1;
    return add_id(input, start, end);
  }

  lex_token_builder &add_string(const std::string &input) {
    int start = 0;
    int end = 0;
    _tokens.push_back(lex_token(start, end));
    assert(_tokens.back().start == start && _tokens.back().end == end);
    return push_token(STRING, input);
  }

  lex_token_builder &add_string(std::string const &input, size_t start) {
    assert(input[start] == '"');

    size_t i = start + 1;
    char c = input.at(i);
    while (c != '"') {
      i++;
      c = input.at(i);
    }
    size_t end = i;
    return push_token(STRING, input, start, end);
  }

  size_t end() { return _tokens.back().end; }

  lex_token_builder &add_number(int64_t v) {
    _tokens.push_back(lex_token(0, 0));
    _tokens.back().number_value = v;
    _tokens.back().symbol = NUMBER;
    return *this;
  }
  lex_token_builder &add_number(string const &input, size_t start) {
    size_t i = start + 1;
    // char c = input.at(i);
    for (; isdigit(input[i]) && i < input.size(); i++)
      ;
    size_t end = i - 1;

    _tokens.push_back(lex_token(start, end));
    _tokens.back().number_value =
        std::stoi(input.substr(start, end - start + 1));
    _tokens.back().symbol = NUMBER;
    return *this;
  }

  lex_token_builder &push_token(lex_symbol s, const std::string &input) {
    assert(_tokens.size() > 0);
    _tokens.back().symbol = s;
    _tokens.back().string_value = input;
    return *this;
  }

  lex_token_builder &push_token(lex_symbol s, const std::string &input, size_t start,
                                size_t end) {
    assert(input.size() > start + 1 && "start ");
    if (end <= start) {
      end = start;
    }
    _tokens.push_back(lex_token(start, end));
    return push_token(s, input.substr(start + 1, end - start - 1));
  }

  lex_token_builder &push_token(lex_symbol s, size_t start) {
    _tokens.push_back(lex_token(start, start));
    _tokens.back().symbol = s;
    return *this;
  }

  static lex_token_builder *
  new_lex_token_builder_with_symbol(lex_symbol symbol) {
    lex_token_builder *builder = new lex_token_builder();
    // builder->_token = new lex_token(symbol);
    return builder;
  }
  lex_token_builder *with_string(std::string value) {
    //_token->string_value = value;
    return this;
  }
  lex_token_builder *with_number(double value) {
    //_token->double_value = value;
    return this;
  }
  lex_token_builder *with_id(string value) {
    //_token->id_name = value;
    return this;
  }

  std::vector<lex_token> build() { return _tokens; }
};

static vector<string> lex_symbols{ "NUMBER", "STRING", "ID", "LP", "RP" };

static vector<lex_token> lexical(const string &input) {

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


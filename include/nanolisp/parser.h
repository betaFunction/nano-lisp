//
// Created by Francesco Fiduccia on 13/04/16.
//

#ifndef NANOLISP_PARSER_H_H
#define NANOLISP_PARSER_H_H

#include "lexer.h"
#include "vector"
#include "string"

using namespace std;
namespace nl {

/*
 class nl_string_expression;
class nl_number_expression;
class nl_id_expression;
 */
class nl_expression {
public:
  virtual ostream &print(ostream &os) = 0;

  virtual bool isPrimitive() = 0;

  string toString();

  virtual string valueToString();
};

class nl_number_expression : public nl_expression {
public:
  double value;

  nl_number_expression(double _value);

  ostream &print(ostream &os) override;

  inline bool isPrimitive() override { return true; }

  virtual string valueToString() override;
};

class nl_id_expression : public nl_expression {
public:
  string id;

  ostream &print(ostream &os) override;

  nl_id_expression(string &_id);

  inline bool isPrimitive() override { return false; }

  virtual string valueToString() override;
};

class nl_string_expression : public nl_expression {
public:
  string value;

  ostream &print(ostream &os) override;

  nl_string_expression(string &_value);

  inline bool isPrimitive() override {
    return true;
  };

  virtual string valueToString() override;
};

class nl_list_expression : public nl_expression {

public:
  inline bool isPrimitive() override {
    return false;
  };
  vector<nl_expression *> arguments;

  ostream &print(ostream &os) override;

  inline nl_list_expression *addArgId(string identifier) {
    this->arguments.push_back(new nl_id_expression(identifier));
    return this;
  }

  inline nl_list_expression *addArgNumber(double value) {
    this->arguments.push_back(new nl_number_expression(value));
    return this;
  }

  inline nl_list_expression *addArgString(string value) {
    this->arguments.push_back(new nl_string_expression(value));
    return this;
  }

  inline nl_list_expression *
  addArgListExpression(nl_list_expression *expression) {
    this->arguments.push_back(expression);
    return this;
  }

  static inline nl_list_expression *create() {
    nl_list_expression *expression = new nl_list_expression;
    return expression;
  }
};

nl_expression *parse(string &input);
}

ostream &operator<<(ostream &os, const nl::nl_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_list_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_id_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_string_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_number_expression &exp);

#endif // NANOLISP_PARSER_H_H

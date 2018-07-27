//
// Created by Francesco Fiduccia on 13/04/16.
//

#pragma once 
#include "lexer.h"
#include <vector>
#include <string>

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
  bool isId(){  // true when id_expresion
    return false;
  }

  // true when list expression
  virtual bool isList() const{
    return false;
  }
  //true when function expression
  bool isFun(){
    return false;
  }
  virtual bool operator==(const nl_expression& other) =0;

};

class nl_number_expression : public nl_expression {
public:
  int64_t value;

 nl_number_expression(int64_t _value):value(_value){}

  ostream &print(ostream &os) override;

  inline bool isPrimitive() override { return true; }
  
  virtual string valueToString() override;
  
  bool operator==(const nl_expression& other) override{
	const nl_number_expression* number_other =(const nl_number_expression*)&other;
	if(number_other == NULL){
	  return false;
	}
	return value == number_other->value;
  }
};

class nl_id_expression : public nl_expression {
public:
  string id;

  ostream &print(ostream &os) override;

 nl_id_expression(string &_id):id(_id){}

  inline bool isPrimitive() override { return false; }

  virtual string valueToString() override;
  bool operator==(const nl_expression& other) override{
	const nl_id_expression* number_other =(const nl_id_expression*)&other;
	if(number_other == NULL){
	  return false;
	}
	return id == number_other->id;
  }
};

class nl_string_expression : public nl_expression {
public:
  string value;

  ostream &print(ostream &os) override;

 nl_string_expression(string &_value):value(_value){}

  inline bool isPrimitive() override {
    return true;
  };

  virtual string valueToString() override;
  bool operator==(const nl_expression& other) override{
  const nl_string_expression* number_other =(const nl_string_expression*)&other;
	if(number_other == NULL){
	  return false;
	}
	return value == number_other->value;
  }
};

class nl_list_expression : public nl_expression {

public:
  inline bool isPrimitive() override {
    return false;
  };
  
  bool isList()  const  override{
	return true;
  }
  inline size_t size() const {
	return this->arguments.size();
  }
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

  bool operator==(const nl_expression& other) override{
	const nl_list_expression* number_other =(const nl_list_expression*)&other;
	if(number_other == NULL){
	  return false;
	}
	
	if (size() != number_other->size()){
	  return false;
	}
	for(int i=0;i<size();i++){
	  if(!(*arguments[i] == *(number_other->arguments[i]))){
		return false;
	  }
	}
	return true;
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

 nl_expression *parse(const string &input);
 nl_expression *parse(std::vector<lex_token> const& tokens);

}

ostream &operator<<(ostream &os, const nl::nl_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_list_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_id_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_string_expression &exp);

ostream &operator<<(ostream &os, const nl::nl_number_expression &exp);



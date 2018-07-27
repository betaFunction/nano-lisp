//
// Created by Francesco Fiduccia on 13/04/16.
// modify by luo xing on 18/7/27
//
#pragma once 
#include "parser.h"
#include <unordered_map>
using namespace std;
#define IFDEBUG(...)


namespace nl {
string eval_string(string &input);
 
class nanolisp_runtime;

class nl_runtime : public nl_expression {
private:
public:
  nl_runtime(string _id);

  string id;

  virtual nl_expression *run(nanolisp_runtime *runtime,
                             vector<nl_expression *> arguments) = 0;
  bool operator==(const nl_expression& other) override{
	return true;
  }
  virtual ostream &print(ostream &os) override;

  virtual bool isPrimitive() override;
};





class nanolisp_runtime {
private:
  std::unordered_map<string, nl_expression *> symbols;

public:
  bool operator==(nl_expression const & other)  {
	return true;
  }

  nanolisp_runtime();
  

  void add(nl_runtime *runtime){
    this->symbols[runtime->id] = runtime;
    this->symbols["platform_" + runtime->id] = runtime;
  }

  inline void add(string identifier, nl_expression *expression){
    this->symbols[identifier] = expression;
  }

  nl_expression *get(string identifier); // only for id_expression


  nl_expression *eval(nl_expression *expression){
      if (expression == nullptr) {
    return nullptr;
  } else if (expression->isPrimitive()) {
    return expression;
  }else if(expression->isId()){
    nl_id_expression *id_expression =
      dynamic_cast<nl_id_expression *>(expression);
    assert(id_expression!= nullptr);
    nl_expression *result = this->get(id_expression->id);
    if (result == nullptr) {
      cout << "Unable to recognize a symbol "
	   << expression->toString()
	   << endl;
      IFDEBUG(this->print_symbols());
      return nullptr;
    }
    return result;
  }else if (!expression->isList()){
    return nullptr;
  }

  nl_list_expression *list_expression =
    dynamic_cast<nl_list_expression *>(expression);
  assert(list_expression != nullptr);

  if(!list_expression->arguments[0]->isFun()){
    return nullptr;
  }
  
  assert(list_expression->arguments[0]->isFun());
  nl_runtime *fun = dynamic_cast<nl_runtime *>(list_expression->arguments[0]);
  assert(fun != nullptr && "should not nullptr Unable to recognize a function for symbol");
  auto first = list_expression->arguments.begin() + 1;
  auto last = list_expression->arguments.end();
  auto sub_arguments = vector<nl_expression *>(first, last);
  IFDEBUG(cout << "running " << fun->id << " ");
  IFDEBUG(this->print_arguments(sub_arguments));
  IFDEBUG(cout << endl);
  return fun->run(this, sub_arguments);
  }
  nl_expression *eval(const std::string & input){
    nl_expression * root = parse(input);
    return eval(root);
  }
  void print_symbols();

  void print_arguments(vector<nl_expression *> arguments);
};
}


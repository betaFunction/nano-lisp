//
// Created by Francesco Fiduccia on 13/04/16.
// modify by luo xing on 18/7/27
//
#pragma once 
#include "parser.h"
#include <unordered_map>
using namespace std;
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

  static nanolisp_runtime *create();

  void add(nl_runtime *runtime);

  void add(string identifier, nl_expression *expression);

  nl_expression *get(string identifier); // only for id_expression


  nl_expression *eval(nl_expression *expression);
  nl_expression *eval(const std::string & input){
    nl_expression * root = parse(input);
    return eval(root);
  }
  void print_symbols();

  void print_arguments(vector<nl_expression *> arguments);
};
}


//
// Created by Francesco Fiduccia on 14/04/16.
//

#ifndef NANOLISP_NANOLISP_H_H
#define NANOLISP_NANOLISP_H_H

#include "parser.h"
#include <unordered_map>
namespace nl {

class nanolisp_runtime;

class nl_runtime : public nl_expression {
private:
public:
  nl_runtime(string _id);

  string id;

  virtual nl_expression *run(nanolisp_runtime *runtime,
                             vector<nl_expression *> arguments) = 0;

  virtual ostream &print(ostream &os) override;

  virtual bool isPrimitive() override;
};

class nanolisp_runtime {
private:
  unordered_map<string, nl_expression *> symbols;

public:
  nanolisp_runtime();

  static nanolisp_runtime *create();

  void add(nl_runtime *runtime);

  void add(string identifier, nl_expression *expression);

  nl_expression *get(string identifier); // only for id_expression


  nl_expression *eval(nl_expression *expression);

  void print_symbols();

  void print_arguments(vector<nl_expression *> arguments);
};
}
#endif // NANOLISP_NANOLISP_H_H

//
// Created by Francesco Fiduccia on 13/04/16.
//
#include "nanolisp/interpreter.h"
#include "nanolisp/nanolisp.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#define IFDEBUG(...)


namespace nl {

ostream &nl_runtime::print(ostream &os) {
  os << "RUNTIME(" << this->id << ")";
  return os;
}

bool nl_runtime::isPrimitive() {
  return false;
}

nl_runtime::nl_runtime(string _id) : id(_id) {};

class nl_print_runtime : public nl_runtime {

public:
  nl_print_runtime(const string &_id) : nl_runtime(_id) {}

  virtual nl_expression *run(nanolisp_runtime *runtime,
                             vector<nl_expression *> arguments) override {
    IFDEBUG(cout << "PRINT: " << flush);
    std::ostringstream stream;
    for (auto item : arguments) {
      nl_expression *exp = runtime->eval(item);
      stream << exp->valueToString() << " ";
    }
    string value = stream.str();
    return new nl_string_expression(value);
  }
};

class nl_defvar_runtime : public nl_runtime {

public:
  nl_defvar_runtime(const string &_id) : nl_runtime(_id) {}

  virtual nl_expression *run(nanolisp_runtime *runtime,
                             vector<nl_expression *> arguments) override {
    if (arguments.size() == 2) {
      // nl_expression *identifier = runtime->eval(arguments[1]);
      // if (identifier->isPrimitive()) {

      nl_id_expression *identifier =
          dynamic_cast<nl_id_expression *>(arguments[0]);
      if (identifier != nullptr) {
        runtime->add(identifier->id, runtime->eval(arguments[1]));
      } else {
        cerr << "def requires the first argument to be a identifier"
             << this->toString();
      }
    }
    return nullptr;
  }
};

class nl_sum_runtime : public nl_runtime {

public:
  nl_sum_runtime(const string &_id) : nl_runtime(_id) {}

  virtual nl_expression *run(nanolisp_runtime *runtime,
                             vector<nl_expression *> arguments) override {
    IFDEBUG(cout << "SUM: " << flush);

    double value = 0;
    if (arguments.size() >= 2) {
      IFDEBUG(cout << value << " ");
      for (auto item : arguments) {
        nl_expression *argument = runtime->eval(item);
        nl_number_expression *operand =
            dynamic_cast<nl_number_expression *>(argument);
        if (operand != nullptr) {
          IFDEBUG(cout << " " << value);
          value += operand->value;

        } else {
          cout << "Unexpected expression: " << argument->toString();
          return nullptr;
        }
      }
      nl_number_expression *result = new nl_number_expression(value);
      IFDEBUG(result->print(cout));
      IFDEBUG(cout << endl << flush);
      return result;
    }
    return nullptr;
  }
};

class nl_begin_runtime : public nl_runtime {

public:
  nl_begin_runtime(const string &_id) : nl_runtime(_id) {}

public:
  virtual nl_expression *run(nanolisp_runtime *runtime,
                             vector<nl_expression *> arguments) override {
    nl_expression *result = nullptr;
    if (arguments.size() > 1) {
      for (auto item : arguments) {
        result = runtime->eval(item);
      }
    }
    return result;
  }
};


nl_expression *nanolisp_runtime::get(string identifier) {

  nl_expression *result = this->symbols[identifier];
  IFDEBUG(cout << "SYMBOL: " << identifier << '=');
  IFDEBUG(result->print(cout));
  IFDEBUG(cout << endl << flush);
  return result;
}



void nanolisp_runtime::print_symbols() {
  cout << "RUNTIME STATUS:" << endl;
  auto i = 0;
  for (auto item : this->symbols) {
    cout << setw(3) << i << "] " << item.first << endl;
    ++i;
  }
}

void nanolisp_runtime::print_arguments(vector<nl_expression *> arguments) {
  for (auto item : arguments) {
    item->print(cout);
    cout << " ";
  }
}

void print_parsed(nl_expression *root) {
  cout << "INTERPRETER PARSED: ";
  root->print(cout);
  cout << endl;
}

string eval_string(string &input) {
  nl_expression *root = parse(input);
  print_parsed(root);
  nanolisp_runtime runtime;

  nl_expression *result = runtime.eval(root);
  if (result != nullptr) {
    return result->valueToString();
  } else {
    return "[nullptr]";
  }
}

  nanolisp_runtime::nanolisp_runtime(){
    this->add(new nl_begin_runtime("begin"));
    this->add(new nl_print_runtime("format"));
    this->add(new nl_defvar_runtime("defun"));
    this->add(new nl_sum_runtime("sum"));
  }


}

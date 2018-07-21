//
// Created by crypt on 4/8/2016.
//
#define IFDEBUG(...)

#include "nanolisp/nanolisp.h"
#include <iostream>
#include <sstream>
#include <iomanip>

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

class nl_def_runtime : public nl_runtime {

public:
  nl_def_runtime(const string &_id) : nl_runtime(_id) {}

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
        cout << "def requires the first argument to be a identifier"
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

nanolisp_runtime::nanolisp_runtime() {
  this->add(new nl_begin_runtime("begin"));
  this->add(new nl_print_runtime("format"));
  this->add(new nl_def_runtime("defun"));
  this->add(new nl_sum_runtime("sum"));
}

void nanolisp_runtime::add(nl_runtime *runtime) {
  this->symbols[runtime->id] = runtime;
  this->symbols["platform_" + runtime->id] = runtime;
}

nl_expression *nanolisp_runtime::get(string identifier) {

  nl_expression *result = this->symbols[identifier];
  IFDEBUG(cout << "SYMBOL: " << identifier << '=');
  IFDEBUG(result->print(cout));
  IFDEBUG(cout << endl << flush);
  return result;
}

void nanolisp_runtime::add(string identifier, nl_expression *expression) {
  this->symbols[identifier] = expression;
}

nl_expression *nanolisp_runtime::eval(nl_expression *expression) {
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

nanolisp_runtime *nanolisp_runtime::create() {

  nanolisp_runtime *runtime = new nanolisp_runtime();

  IFDEBUG(runtime->print_symbols());
  return runtime;
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
}

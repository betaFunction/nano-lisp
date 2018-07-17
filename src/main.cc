#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "nanolisp/nanolisp.h"
#include "nanolisp/interpreter.h"
namespace nl {
namespace info {
string executable = "nanolisp";
string fullname = "Nano Lisp";
string version = "dancing in the dark";
}

void version() {
  cout << info::executable << "\t"
       << " is " << info::fullname
       << " version '" << info::version
       << "'" << endl;
}

void help(int argc, char **argv) {
  version();
}

void repl() {
  int line = 0;
  string input_line = "start";
  while (input_line != "end") {
    cout << "[input|" << line << "]";

    getline(cin, input_line);
    string output_line = nl::eval_string(input_line);
    cout << ">> " << output_line << endl;
    line++;
  }
}
}

int main(int argc, char **argv) {
  if (argc == 1) {
    nl::version();
    nl::repl();
  } else {
    nl::help(argc, argv);
  }
  return 0;
}

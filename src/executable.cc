//
// Created by crypt on 4/7/2016.
//

#include <iostream>

using namespace std;

namespace nl {

namespace info {
string executable = "nl";
string fullname = "nanolip";
string version = "";
}

void version() {
  cout << info::executable << " is " << info::fullname << info::version << endl;
}

void help(int argc, char **argv) { version(); }
}
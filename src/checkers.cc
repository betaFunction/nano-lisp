//
// Created by crypt on 17/10/17.
//
#include "checkers.hpp"
#include <iostream>

bool
nltokenBinaryPredicate(const nl::lex_token *first, 
		       const nl::lex_token *second) {
    return *first == *second;
}

bool
check_lexer(bool match, string input,
	    vector<nl::lex_token *> &expected) {
  vector<nl::lex_token *> result;
    nl::lexical(input, result);

    if (match && result.size() == expected.size()) {
      cout << "String:" << endl << '\t'
	   << input << endl << "matches as:" << endl << "\t";
        for (auto item : expected) {
            cout << nl::lex_symbols.at(item->symbol) << " ";
        }
        cout << endl << endl;
        return true;
    } else if ((!match)){
               // (!equal(result.begin(), result.end(),
	       // 	       expected.begin(), expected.end(),
	       // 	       nltokenBinaryPredicate))) {

        auto diff = mismatch(result.begin(), result.end(),
			     expected.begin(), expected.end());

        if (*diff.first != *diff.second) {
            cout << nl::lex_symbols.at((*diff.first)->symbol) 
		 << " != "
		 << nl::lex_symbols.at((*diff.second)->symbol);
        }
        cout << endl;
        for (auto item : result) {
            cout << nl::lex_symbols.at(item->symbol) << " ";
        }
        cout << endl << endl;
        return false;
    } else {
        cout << "Expected and result doesn't have the same length"
	     << endl;
        for (auto item : result) {
            cout << nl::lex_symbols.at(item->symbol) << " ";
        }
        cout << endl << endl;
        return false;

    }

}


string trim(string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

bool
check_interpreter(string &program, string &expected) {
    string result = nl::run_interpreter(program);
    result = trim(result);
    if (result.compare(expected) != 0) {
        cout << "Interpretation has failed:" << endl
             << "[program]  `" << program << "`" << endl
             << "[expected] `" << expected << "`" << endl
             << "[received] `" << result << "`" << endl;
        return false;
    } else {
        cout << program << " interpreted correctly !!!" << std::endl;
        return true;
    }
}


bool check_parser(string input,
                  vector<nl::lex_token *> &expected_lexer,
                  nl::nl_expression *expected_parser) {
    if (check_lexer(true, input, expected_lexer)) {
        nl::nl_expression *result = nl::parse(input);
        cout << "print parsed: ";
        result->print(cout);
        cout << endl;
        return true;
    }
    return false;
}

#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <signal.h>

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

void signal_interrupt(int sig){
  signal(SIGINT, signal_interrupt);
  
}
void signal_alrm(int sig){
  
}


// unsigned int alarm(unsigned int seconds);
int sleep1(unsigned int  seconds){
  if(signal(SIGALRM, signal_alrm) == SIG_ERR){
    return seconds;
  }
  alarm(seconds);
  pause();
  return alarm(0);
}

//int sigemptyset(sigset_t *set);
//int sigfillset(sigset_t *set);
//int sigaddset(sigset_t* set, int signo);
//int sigdelset(sigset_t* set, int signo);
//int sigismember(const sigset_t* set, int signo);

//int sigprocmask(int how, const sigset_t* restrict set, sigset_t* restrict oset);
//int sigpending(sigset_t* set);


int main(int argc, char **argv) {
  if(signal(SIGINT, signal_interrupt) == SIG_ERR){
    return -1;
  }

  
  if (argc == 1) {
    nl::version();

    sigset_t newmask, oldmask, pendmask;
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);

    if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) <0){
      return -1;
    }

    if(sigpending(&pendmask) <0){
      return -1;
    }

    if(sigismember(&pendmask, SIGQUIT)){
      printf("\n sigquit pending\n");
    }
    
    nl::repl();
    
    if(sigprocmask(SIG_SETMASK, &oldmask, NULL)<0){
      return -1;
    }
    
    return 0;
  }
  nl::help(argc, argv);

}

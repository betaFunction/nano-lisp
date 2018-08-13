#include <signal.h>
int main(){
  // control-c SIGint
  // divide by 0 , sigsegv
  // sigurg sigpipe sigalrm
  // the process has to tell the kernel "if and when this signal occurs, do the following."


  // ignore the signal; sigkill. sigstop can never be ignored, 
  // catch the signal,
  // let the default action apply.
  // sig_ign, sig_def,
  // we are not able to determine the current disposition of a signal without changing the disposition. 
  // sigabrt , abnormal termination
  // sigalrm , timer expired
  // sigbus , hardware fault
  // cancel  , threads libray internal use, ignore
  // child , change in status of child
  // cont , continue stopped process, this job-control signal is sent to a stopped process when it is continued. The default action is to continue a stopped process.
  //       
  // emt , hardware fault
  // fpe , arithmetic exception
  // freeze, checkpoint freeze
  // hup, hangup
  // ill, illegal instruction
  // info, int, io, iot, jvm1, jvm2, kill, lost, lwp, pipe, poll, prof, pwr, quit, segv,
  // stkflt,  coprocessor stack fault
  // stop
  // sys, invalid system call
  // term
  // thaw
  // thr
  // trap
  // tstp, terminal stop character
  // ttin,
  // ttou, background write to control tty
  // urg, urgent condition
  // usr1, user-defined signal
  // usr2, user-defined signal
  // vtalrm, virtual time alarm
  // waiting, threads library internal use
  // winch, terminal window size change
  // xcpu, cpu limit exceeded
  // xfsz, file size limit exceeded
  // xres, resource control exceeded
  
  return 0;
}

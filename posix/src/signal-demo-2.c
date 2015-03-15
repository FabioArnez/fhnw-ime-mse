/*---------------------
  signal-demo-2
  (c) H.Buchmann FHNW 2015
  ---------------------*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
/*---------------------------------- objectives
 the signal handler
  onSignal
*/

void onSignal(int sig)
{
 printf("-------- onSignal %d '%s'\n",sig,strsignal(sig));
}

int main(int argc,char** args)
{
 printf("pid=%d\n",getpid());
 signal(SIGUSR1,onSignal);
 while(1)
 {
  printf("wait\n");
  pause(); 
  printf("done\n");
 }
 return 0;
}

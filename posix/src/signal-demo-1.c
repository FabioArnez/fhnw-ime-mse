/*---------------------
  signal-demo-1
  (c) H.Buchmann FHNW 2015
  ---------------------*/
#include <stdio.h>
#include <unistd.h>
/*---------------------------------- objectives
 - waiting for signals
 - generate signals 
   kill -signal pid
   kill -l lists all signals
*/

int main(int argc,char** args)
{
 printf("pid=%d\n",getpid());
 while(1)
 {
  printf("wait\n");
  pause(); 
  printf("done\n");
 }
 return 0;
}

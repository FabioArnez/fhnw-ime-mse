/*--------------------
  sys-call
  (c) H.Buchmann FHNW 2013
 --------------------- */
#include <unistd.h>
#include <sys/syscall.h>
const char s[]="Hello\n";
int main(int argc,char** args)
{
 syscall(__NR_write,0,s,5);
 return 0;
}
   

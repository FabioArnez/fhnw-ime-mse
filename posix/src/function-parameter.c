/*---------------------
 function-parameter
 (c) H.Buchmann FHNW 2011
 $Id$
-----------------------*/
#include <stdio.h>

/* two callees
  different names
  *but*
   - the same *signature* e.g.
    same return type
    same parameters
*/
int calleeA(int arg)  
{
 return arg+2; 
}
 
int calleeB(int arg)  
{
 return arg+4; 
}

/* quite cryptic: 

  int (*func)(int) 
  
  means:
  the parameter func is a function with the signature
  int aName(int)
*/
 
void theCaller(int (*func)(int))
{
 int value=8;
 /* call it */
 printf("func(%d)=%d\n",value,func(value));
}

int main(int argc,char** args)
{
 theCaller(calleeA); /* calleeA as parameter */
 theCaller(calleeB); /* calleeB as parameter */
 return 0;
}
 
 

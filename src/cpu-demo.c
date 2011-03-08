/*---------------------------
 cpu-demo
 (c) H.Buchmann FHNW 2010
 $Id$
 ----------------------------*/
#include<stdio.h>
#include "cpu-demo-ops.h" /* somtimes made in assembler */

#if 0
unsigned src=5;
unsigned dst=6;

int main(int argc,char** args)
{
 unsigned res=op(src,dst);
 printf("op(%d,%d)=%d\n",src,dst,res); 
 printf("before: src=%d dst=%d\n",src,dst);
 copy(&dst,&src);
 printf("after:  src=%d dst=%d\n",src,dst); 
 return 0;
}
#endif

extern unsigned x;
extern unsigned y;

unsigned test()
{
 return op(x,y);
}

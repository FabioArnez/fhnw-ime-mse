/*---------------------------
 cpu-demo
 (c) H.Buchmann FHNW 2010
 $Id$
 ----------------------------*/
#include<stdio.h>
 #define DONE_IN_ASSEMBLER

/* see assembler.S */
extern unsigned op(unsigned x,unsigned y);
extern void copy(unsigned* dst,unsigned* src);

#ifndef DONE_IN_ASSEMBLER
unsigned op(unsigned x,unsigned y)
{
 return x+y;
}
void copy(unsigned* dst,unsigned* src)
{
 *dst=*src;
}
#endif

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

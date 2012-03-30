/*-------------------------
  kmi-test keyboard mouse interface
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/pl050-keyboard-mouse.pdf
---------------------------*/
#include "stdio.h"

volatile struct
{
       unsigned CR;
 const unsigned STAT;
       unsigned DAT;
       unsigned CLKDIV;
       unsigned IR;
} KMI1;

static void cmd(unsigned v)
{
 while((KMI1.STAT&(1<<6))==0){}
 KMI1.DAT=v;
}

static unsigned read()
{
 while((KMI1.STAT&(1<<4))==0){}
 return KMI1.DAT;
}

static void set(unsigned v)
{
 cmd(v);
 unsigned ack=read();
 printf("set %x\t%x\n",v,ack);
}

static void data()
{
 unsigned in[3];
 for(unsigned i=0;i<3;++i)
 {
  in[i]=read();  
 }
 for(unsigned i=0;i<3;++i)
 {
  printf("%x ",in[i]);
 }
 printf("\n");
}


int main()
{
 KMI1.CR|=(1<<2);
 set(0xf4); /* enable */
 set(0xea); /* set stream */
 while(1)
 {
  data();
 }
 return 0;
}
  

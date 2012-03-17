/*----------------------------
  mmu.h
  (c) H.Buchmann FHNW 2012
  $Id$
  [1] literature/ARM-Architecture-Reference-Manual.pdf
------------------------------*/
#include "sys/deb.h"
#include "sys/mmu.h"
#include "sys/arm.h"
/* Translation table base [1] B4.7.1 */

unsigned TTB[0x1000] __attribute__((aligned(0x1000))); /* aligned on 4 KB boundary */

void call(void (*p)()) /* for looking how it is done */
{
 p();
}    
/* [1] B4-27 */
#define RAM  0xc1e
#define PHY  0xc12  
#define MEGA (1<<20)
static const MMU_Desc Desc[]=
{
 /* p-mem     v-mem size_MB     flags */
 {0x00000000,0x00000000,64*MEGA,PHY},
 {0x00000000,0x20000000,64*MEGA,RAM},
 {0         ,0,         0}
};

/* check if pic */
static void init(volatile unsigned* ttb)
{ 
 for(unsigned i=0;i<4096;++i) ttb[i]=0;
}

static void show(volatile unsigned* ttb)
{
 for(unsigned i=0;i<4096;++i)
 {
  deb_hex(i);deb_out('\t');deb_hex(ttb[i]);deb_out('\n');
 }
 deb_out('-');
}

volatile unsigned* mmu_enable(unsigned disp)
{
 volatile unsigned* ttb=(volatile unsigned*)((unsigned)TTB+disp); 
 init(ttb);
 MMU_Desc* desc=(MMU_Desc*)((unsigned)Desc+disp);
 while(desc->sizeMB)
 {
  unsigned p=desc->p_mem;
  unsigned v=desc->v_mem;
  unsigned s=desc->sizeMB;
  unsigned f=desc->flags;
  while(s>0)
  {
   ttb[v>>20]=p|f;
   v+=MEGA;
   p+=MEGA;
   s-=MEGA;
  }  
  ++desc;
 }
 show(ttb);
 return ttb;
}


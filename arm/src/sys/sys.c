/*--------------------
 sys important sys functions
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/ARM-Architecture-Reference-Manual.pdf
     [2] http://gcc.gnu.org/onlinedocs/gcc-4.5.2/gcc/
----------------------*/
#include "sys/sys.h"
void sys_undef()
{
 asm volatile /* see [2] Extended-Asm.html#Extended-Asm */
 (
  ".word 0xe7f000f0"           /* see [1] A3.16.5 p 147 */
  :
  :
 );
}

unsigned sys_getCPSR()
{
 unsigned v;
 asm volatile /* see [2] Extended-Asm.html#Extended-Asm */
 (
  "@--------------- sys_getCPSR\n"
  "\tmrs %[v],cpsr"            /* see [1] A3.10.2 128 */
  :[v] "=r" (v)/* out */
  :            /* in */
 );
 return v;
}
 
void sys_setCPSR(unsigned v)
{
  asm volatile /* see [2] Extended-Asm.html#Extended-Asm */
 (
  "@--------------- sys_setCPSR\n"
  "\tmsr cpsr,%[v]"            /* see [1] A3.10.2 128 */
  :            /* out */
  :[v] "r" (v)  /* in */
 );
}


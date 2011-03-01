/*--------------------
 sys important sys functions
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/ARM-Architecture-Reference-Manual.pdf
----------------------*/
#include "sys/sys.h"
void sys_undef()
{
 asm volatile
 (
  ".word 0xe7f000f0"  /* see [1] A3.16.5 p 147 */
  :
  :
 );
}

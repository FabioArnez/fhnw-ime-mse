#pragma once
/*--------------------
 arm important functions for arm architecture
 (c) H.Buchmann FHNW 2011
 $Id$
 [1] literature/ARM-Architecture-Reference-Manual.pdf
 exercise in inline assembler
----------------------*/
extern void sys_undef();  /* executes an undef instruction triggering the
                             undef exeception */

/* CPSR see [1] A2.5 */
extern unsigned sys_getCPSR(); 
extern void sys_setCPSR(unsigned val);


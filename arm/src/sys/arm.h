#pragma once
/*--------------------
 arm important functions for arm architecture
 (c) H.Buchmann FHNW 2011
 $Id$
 [1] literature/ARM-Architecture-Reference-Manual.pdf
 exercise in inline assembler
----------------------*/
      /*              interrupt attribute */
typedef enum { RESET, 
	       UNDEF,           /* UNDEF */ 
	       SWI,             /* SWI   */
	       PREFETCH,        /* ABORT */
	       DATA,            /* ABORT */
	       RESERVED,        
	       IRQ,             /* IRQ */
	       FIQ              /* FIQ */
	     } Exception;

extern void arm_set_exception(Exception ex,void (*exception)());
 /* guarantee that exception is defined with the appropriate attribute
   __attribute__((interrupt(attr)))
   
 */
extern void arm_undef();  /* executes an undef instruction triggering the
                             undef exeception */
/* CPSR see [1] A2.5 */
extern unsigned arm_getCPSR(); 
extern void arm_setCPSR(unsigned val);

inline unsigned arm_get_lr() /* return linkregister lr */
{
 unsigned lr;
 asm volatile
 (
 "@----------------- arm_get_lr\n"
 "\t mov %[lr],lr\n"
 :[lr] "=r" (lr)
 :
 );
 return lr;
}

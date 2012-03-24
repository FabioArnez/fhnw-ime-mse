#pragma once
/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 -----------------------*/
/*------------------------------------------------ without trap */
extern void uart_out(char ch); 
extern char uart_in();        /* waits until ready */
extern unsigned uart_avail(); /* returns true if char available */

/*--------------------------------------------------- with trap */
extern void uart_enable();                          /* the trap */
extern void uart_disable();
extern char uart_get();  
extern void uart_put(char ch);

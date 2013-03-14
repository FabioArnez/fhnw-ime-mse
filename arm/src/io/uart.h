#pragma once
/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 -----------------------*/
extern void uart_init();

/*------------------------------------------------------------- polling */
extern void uart_out(char ch); 
extern char uart_in();        /* waits until ready */
extern unsigned uart_avail(); /* returns true if char available */

/*------------------------------------------------------------ with trap */
extern void uart_install(void (*li)(char));                  /* the trap */
extern void uart_put(char ch);

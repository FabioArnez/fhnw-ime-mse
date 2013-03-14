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
#define FIFO 4                                /* size of fifo = 1<<FIFO  */
extern void uart_install(void (*li)(char));                  /* the trap */
extern void uart_start();                          /* with traps enabled */

extern void uart_put(char ch);
extern char uart_get();
extern unsigned uart_rx_size();

#pragma once
/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 -----------------------*/
extern void uart_out(char ch);
extern char uart_in();
extern unsigned uart_avail(); /* returns true if char available */

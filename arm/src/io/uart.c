/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 see [literature/realview_emulation_basebord_ug.pdf] 
     [literature/pl011-UART.pdf]
 -----------------------*/
#include"io/uart.h"

extern volatile struct 
{
 unsigned DR;                         /*Data register */ 
 unsigned SR;                       /* Receive status */
 unsigned res[4];                         /* reserved */
 unsigned FR;                                 /* Flag */  
} UART0;

void uart_out(char ch)
{
 while(UART0.FR&(1<<3)){} /* wait until busy cleared */
 UART0.DR=ch;
}

char uart_in()
{
 while(UART0.FR&(1<<4)){} /* wait until rx ready */
 return UART0.DR;
}


unsigned uart_avail()
{
 return (UART0.FR&(1<<4))==0;
}

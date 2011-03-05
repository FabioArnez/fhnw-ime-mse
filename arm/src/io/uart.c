/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 see [IntegratorCM] [UART]
 -----------------------*/

static volatile struct 
{
 unsigned DR;                         /*Data register */ 
 unsigned SR;                       /* Receive status */
 unsigned res[4];                         /* reserved */
 unsigned FR;                                 /* Flag */  
}* UART = 0x16000000;

void uart_out(char ch)
{
 while(UART->FR&(1<<3)){} /* wait until busy cleared */
 UART->DR=ch;
}

char uart_in()
{
 while(UART->FR&(1<<4)){} /* wait until rx ready */
 return UART->DR;
}


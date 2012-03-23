/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/realview_emulation_basebord_ug.pdf] 
     [2} literature/pl011-UART.pdf]
 -----------------------*/
#include "stdio.h"
#include"io/uart.h"
#include "sys/gic.h"

extern volatile struct 
{
       unsigned DR;                              /* Data register */ 
       unsigned SR;                             /* Receive status */
       unsigned res0[4];                              /* reserved */
 const unsigned FR;                                       /* Flag */
       unsigned res1[1]; 
       unsigned ILPR;          /* IrDA low-power counter register */
       unsigned IBRD;               /* Integer baud rate register */
       unsigned FBRD;            /* Fractional baud rate register */
       unsigned LCR_H;                  /* Line control register, */
       unsigned CR;                           /* Control register */
       unsigned IFLS;    /* Interrupt FIFO level select register, */
       unsigned IMSC;        /* Interrupt mask set/clear register */
 const unsigned RIS;             /* Raw interrupt status register */
 const unsigned MIS;          /* Masked interrupt status register */
       unsigned ICR;                  /* Interrupt clear register */
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

#define UART0_ID 44 /* [1] 4.12.2  */

static void onRX() /* a character is available */
{
 UART0.ICR=(1<<4);
 uart_out(UART0.DR);
}

void uart_enable()
{
 gic_init();
 gic_install(UART0_ID,onRX);
 gic_enable(UART0_ID);
 UART0.CR=(1<<0)|
          (1<<9)|
	      0;
 UART0.IMSC|=(1<<4); 
}

char uart_get()
{
 while(1)
 {
 // printf("%x\t%x\t%x\n",UART0.RIS,UART0.MIS,UART0.IMSC);
 }
}


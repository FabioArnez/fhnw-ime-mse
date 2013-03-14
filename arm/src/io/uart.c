/*----------------------
 uart
 (c) H.Buchmann FHNW 2011
 $Id$
 see [1] literature/realview_emulation_basebord_ug.pdf 
     [2] literature/pl011-UART.pdf
 TODO realize txQueue    
 -----------------------*/
#include"io/uart.h"
#include "sys/gic.h"

extern volatile struct                             /* see [2] 3.2 */
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

/*--------------------------------------------------------- flags */
#define RXFE (1<<4) /* see [2] 3.3.3  */
#define RXIM (1<<4) /* see [2] 3.3.10 */
#define RXIC (1<<4) /* see [2] 3.3.13 */

#define BUSY (1<<3)

void uart_init()
{
 static unsigned initalized=0;
 if (initalized) return;
 ++initalized;
 /* TODO initialize it */
  while(uart_avail())
 {
  uart_in();
 }
}

/*------------------------------------------------------- polling */
void uart_out(char ch)
{
 while(UART0.FR & BUSY ){}             /* wait until busy cleared */
 UART0.DR=ch;
}

char uart_in()
{
 while(UART0.FR & RXFE){}                 /* wait until rx ready */
 return UART0.DR;
}

unsigned uart_avail()
{
 return (UART0.FR & RXFE)==0;
}

#define UART0_ID 44 /* [1] 4.12.2  */

static void (*listener)(char) = 0;

static void onRX() /* a character is available */
{
 if (listener)
    {
     listener(UART0.DR);
    }
 UART0.ICR=RXIC;
}


void uart_install(void (*li)(char))
{
 uart_init();
 listener=li;
 gic_init();
 gic_install(UART0_ID,onRX);
 gic_enable(UART0_ID);
 UART0.IMSC|=RXIM;   /* enable interrupt */
}



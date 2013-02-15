/*----------------------
 accessing-hardware
 (c) H.Buchmann FHNW 2012
 $Id$
 see  [1]config/memory.map
      [2] literature/pl011-UART.pdf
----------------------*/  
/* accessing via pointer */

/* typedef */
typedef struct                         /* see [2] 3.2 */
{
 unsigned DR;                         /*Data register */ 
 unsigned SR;                       /* Receive status */
 unsigned res[4];                         /* reserved */
 unsigned FR;                                 /* Flag */  
}
UART;

/* the bits in uart->FR */
#define RXFE (1<<4) 
#define TXFF (1<<5)

volatile UART*const uart=(volatile UART*const)0x10009000;
/*|          |    |       |                 | |---- where it is see [1]
  |          |    |       |-----------------|------ cast 
  |          |    |-------------------------------- the value of dont change 
  |          |------------------------------------- pointer
  |------------------------------------------------ periphery may change the contents 
*/

/* TODO make functions */
void main()
{
 while(1)
 {   /* read from uart */
  while(uart->FR&RXFE)
  {
   /* Receive FIFO empty */
  }
  /* Receive FIFO not empty */ 
  unsigned ch=uart->DR; /* read it */
  while((uart->FR&TXFF))
  {
   /* transmit FIFO not empty */
  }
  /* transmit FIFO  empty */
  uart->DR=ch;
 }
}


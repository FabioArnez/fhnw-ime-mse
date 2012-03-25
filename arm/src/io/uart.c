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

/*------------------------------------------------------- polling */
void uart_out(char ch)
{
 while(UART0.FR & BUSY ){} /* wait until busy cleared */
 UART0.DR=ch;
}

char uart_in()
{
 while(UART0.FR & RXFE){} /* wait until rx ready */
 return UART0.DR;
}

unsigned uart_avail()
{
 return (UART0.FR & RXFE)==0;
}

/*---------------------------------------------------- fifo queue */
/* realized as ring buffer */
typedef struct
{
 unsigned getI;
 unsigned putI;
 volatile unsigned size; /* accessed by put and get functions */
 unsigned capacity;
 unsigned* pool;
} Queue;


static void queue_init(Queue*const queue,
                       unsigned capacity,unsigned* pool)
{
 queue->getI=0;
 queue->putI=0;
 queue->size=0;
 queue->capacity=capacity;
 queue->pool=pool;
}

static unsigned queue_empty(Queue*const queue)
{
 return queue->size==0;
}

static unsigned queue_full(Queue*const queue)
{
 return queue->size==queue->capacity;
}


/* called by foreground */
static void queue_put(Queue*const queue,unsigned val)
{
 queue->pool[queue->putI++]=val;
 if (queue->putI==queue->capacity) queue->putI=0;
 if (queue->size<queue->capacity) 
    {  /* common access */
     ++queue->size;
    }
}

/* called by background */
static unsigned queue_get(Queue*const queue)
{
 while(queue->size==0){} /* wait here */
 /* queue->size>0 */
 unsigned v=queue->pool[queue->getI++];
 if (queue->getI==queue->capacity) queue->getI=0;
/* common access */
 UART0.IMSC&=~RXIM; /* disable rx interrupt */
 --queue->size; 
  UART0.IMSC|=RXIM; /* enable */
 return v; 
}


#define RXPOOL 32
static unsigned rxPool[RXPOOL];
static Queue rxQ;

#define UART0_ID 44 /* [1] 4.12.2  */

static void onRX() /* a character is available */
{
 queue_put(&rxQ,UART0.DR);
 UART0.ICR=RXIC;
}

void uart_enable()
{
 queue_init(&rxQ,RXPOOL,rxPool);
 gic_init();
 gic_install(UART0_ID,onRX);
 gic_enable(UART0_ID);
 UART0.IMSC|=RXIM; /* enable interrupt */
}

char uart_get()
{
 return queue_get(&rxQ);
}


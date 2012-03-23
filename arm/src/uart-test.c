/*----------------------
  uart-test
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
  ----------------------*/
#include "io/uart.h"
#include "sys/arm.h"
#include "sys/gic.h"
static const char MSG[]="Hello World\n"
                        " pressing e reset\n";
int main()
{
 arm_init();
 arm_irq(1);
 gic_init();
 uart_enable();
 uart_get();
}  
  

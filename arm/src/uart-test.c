/*----------------------
  uart-test
  (c) H.Buchmann FHNW 2011
  $Id$
  ----------------------*/
#include "io/uart.h"
static const char MSG[]="Hello World\n"
                        " pressing e reset\n";
int main()
{
 for(unsigned i=0;MSG[i];++i) uart_out(MSG[i]);
 while(1)
 {
  char ch=uart_in();
  if (ch=='e') break;
  uart_out(ch);
 }
}  
  

//-----------------------
//uart an event driven driver
//(c) H.Buchmann FHNW 2015
//[1] AT91SAM ARM-based Flash MCU
//    SAM3X SAM3A Series
//    at91sam3x.pdf
//-----------------------
IMPLEMENTATION(sys_uart,$Id$)
#include "sys/uart.h"
#include "sys/soc.h"
#include "sys/deb/deb.h"
#include "sys/reg/uart.h"

namespace sys
{
 UART UART::uart;
 void UART::RX::listen(RX::Listener& li)
 {
  uart.rx.li=&li;
 }

 void UART::onUART()
 {
  unsigned sr=reg::UART.SR;
  if (sr&reg::UART.RXRDY)
     {
      uart.rx.rhr=reg::UART.RHR; //copy
      uart.rx.signal();
     }
  if (sr&reg::UART.TXRDY)
     {
      char ch=uart.tx.s[uart.tx.len++];
      if (ch)
         {
	  reg::UART.THR=ch;
	 }
	 else
	 {
	  reg::UART.IDR|=reg::UART.TXRDY;
	  uart.tx.signal();
	 }
     } 
 }
 
 UART::RX::RX()
 :sys::Event(this)
 {
  sys::reg::UART.IER=(1<<0);//RXRDY
 }

 void UART::RX::onEvent(Event&)
 {
  if (li) li->onRX(rhr);
 }
 
 UART::TX::TX()
 :sys::Event(this)
 {
  while((reg::UART.SR&reg::UART.TXRDY)==0){}
 }

 void UART::TX::onEvent(Event&)
 {
  const char*s=this->s;
  unsigned len=this->len;
  this->s=0; 
  this->len=0; 
  if (li) li->onTX(s,len);
 }
 
 
 //see [1] Figure 35.10
 bool UART::TX::txIt(const char s[],Listener& li)
 {
  if (s==0) return false; 
  reg::UART.IDR|=reg::UART.TXRDY; //disable interrupt
  if (this->s) return false; //not empty
  this->li=&li;
  this->s=s;
  while((reg::UART.SR&reg::UART.TXRDY)==0){}  //why
  reg::UART.THR=*s;
  this->len=1;
  reg::UART.IER=reg::UART.TXRDY; //enable interrupt
  return true; 
 }
 
 
 UART::UART()
 {
  SOC::install(SOC::UART,onUART);
  SOC::arm(SOC::UART);
 }
 
}

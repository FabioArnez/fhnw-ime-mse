#pragma once
//-----------------------
//uart an event driven driver
//(c) H.Buchmann FHNW 2015
//TODO 
//-----------------------
INTERFACE(sys_uart,$Id$)
#include "sys/event.h"
#include "util/fifo.h"
namespace sys
{
 class UART
 {
  public:
   class RX:Event,Event::Listener
   {
    public:
     struct Listener
     {
      virtual void onRX(char ch)=0; //call-back
     };
     static void listen(RX::Listener& li);
     
    private:
     friend class UART;
     Listener* li=0;  
     volatile unsigned rhr; // Receive Holding Register one char buffer
     RX();
     void onEvent(sys::Event&);
   }; //RX
 
   class TX:Event,Event::Listener
   {
    public:
     struct Listener
     {
      virtual void onTX(const char s[],unsigned len)=0;
     };
     static bool tx(const char s[],Listener& li)
     {
      return uart.tx.txIt(s,li);
     }
      //returns true if transmit starts (not busy before)
     static void tx(const char s[],unsigned len,Listener& li); //TODO

    private:
     friend class UART;
     Listener* li=0;
     volatile const char* s  =0; //the current
     volatile unsigned    len=0; //the length 
     TX();
     bool txIt(const char s[],Listener& li);
     void onEvent(sys::Event&); 
   }; //TX
   
  private:
   static UART uart;
   RX rx;
   TX tx;
   UART(); 
   static void onUART(); //the interrupt handler
 };
}

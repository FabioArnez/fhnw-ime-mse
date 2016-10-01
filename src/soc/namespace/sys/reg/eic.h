#pragma once
//------------------------
//eic external interrupt controller
//(c) H.Buchmann FHNW 2016
//------------------------
INTERFACE(sys_reg_eic,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct EIC
  {
   enum PIN   {P00,P01,P02,P03,P04,P05,P06,P07,P08,P09,
               P10,P11,P12,P13,P14,P15,P16,P17};
   enum SENSE {NONE,RISE,FALL,BOTH,HIGH,LOW};	     
   unsigned char CTRL;     // 0x00 
   unsigned char STATUS;   // 0x01 
   unsigned char NMICTRL;  // 0x02 
   unsigned char NMIFLAG;  // 0x03 
   unsigned EVCTRL;        // 0x04 
   unsigned INTENCLR;      // 0x08 
   unsigned INTENSET;      // 0x0c 
   unsigned INTFLAG;       // 0x10 
   unsigned WAKEUP;        // 0x14 
   unsigned CONFIG[3];     // 0x18 
   void regs()const volatile;
   void init() volatile;
   void enable(PIN p) volatile;
   void sense(PIN p,SENSE s) volatile;
   void filter(PIN p,bool v) volatile;
  }EIC;
 }
}


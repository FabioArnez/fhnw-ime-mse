#pragma once
//--------------------------
//wdt watch dog
//(c) H.Buchmann FHNW 2016
//--------------------------
INTERFACE(sys_reg_wdt,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct WDT
  {
   unsigned char CTRL;     //0x00
   unsigned char CONFIG;   //0x01
   unsigned char EWCTRL;   //0x02
   unsigned char res;      //0x03
   unsigned char INTENCLR; //0x04
   unsigned char INTENSET; //0x05
   unsigned char INTFLAG;  //0x06
   unsigned char STATUS;   //0x07
   unsigned char CLEAR;    //0x08
   void regs() volatile const;
  } WDT; 
 }
}

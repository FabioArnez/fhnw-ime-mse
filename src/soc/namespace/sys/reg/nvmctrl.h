#pragma once
//-----------------------------
//nvmctrl
//(c) H.Buchmann FHNW 2016
//-----------------------------
INTERFACE(sys_reg_nvmctrl,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct NVMCTRL
  {
   union
   {
    unsigned short CTRLA;      //0x00
    unsigned       RES0;
   };
   unsigned CTRLB;             //0x04
   unsigned PARAM;             //0x08
   union
   {
    unsigned char INTENCLR;    //0x0c
    unsigned      RES1;
   };
   union
   {
    unsigned char INTENSET;   //0x10
    unsigned      RES2;
   };
   union
   {
    unsigned char INTFLAG;   //0x14
    unsigned      RES3;
   };
   union
   {
    unsigned short STATUS;   //0x18
    unsigned       RES4;
   };
   unsigned        ADDR;     //0x1c
   unsigned short  LOCK;     //0x20;
   void regs() const volatile;
  } NVMCTRL;

 }
}


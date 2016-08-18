#pragma once
//--------------------------
//pm power manager
//(c) H.Buchmann FHNW 2016
//--------------------------
INTERFACE(sys_reg_pm,$Id$)
#include "sys/hwreg.h"
namespace sys
{
 namespace reg
 {
  extern volatile struct PM
  {
   union
   {
    struct
    {
     unsigned char CTRL;
     unsigned char SLEEP;
    };
    unsigned RES0[2];
   };
   unsigned char CPUSEL;
   unsigned char APBASEL;
   unsigned char APBBSEL;
   unsigned char ALBCSEL;
   ResW<0x0c,0x14> RES1;
   unsigned AHBMASK;    // 0x14 AHB Mask 
   unsigned APBAMASK;   // 0x18 APBA Mask 
   unsigned APBBMASK;   // 0x1C APBB Mask 
   unsigned APBCMASK;   // 0x20 APBC Mask
   ResW<0x24,0x34> RES2; 
   union
   {
    struct
    {
     unsigned char INTENCLR;   // 0x34 Interrupt Enable Clear 
     unsigned char INTENSET;   // 0x35 Interrupt Enable Set 
     unsigned char INTFLAG;    // 0x36 Interrupt Flag Status and Clear 
    };
    unsigned RES3;
   };
   unsigned char RCAUSE;     // 0x38 Reset Cause 
   void regs() const volatile;
  } PM;
 }
}


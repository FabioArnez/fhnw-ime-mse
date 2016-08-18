#pragma once
//---------------------------
//sysctrl [1] 16.7
//(c) H.Buchmann FHNW 2016
//----------------------------
INTERFACE(reg_sysctrl,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct SYSCTRL
  {
   unsigned INTENCLR;        // 0x00 Interrupt Enable Clear 
   unsigned INTENSET;        // 0x04 Interrupt Enable Set 
   unsigned INTFLAG;         // 0x08 Interrupt Flag Status and Clear 
   unsigned PCLKSR;          // 0x0C Power and Clocks Status
   union
   { 
    unsigned short XOSC;     // 0x10 External Multipurpose Crystal Oscillator // XOSC Control
    unsigned       RES0;
   };
   union
   { 
    unsigned short XOSC32K;  // 0x14 32kHz External Crystal Oscillator // XOSC32K Control
    unsigned       RES1; 
   };
   unsigned OSC32K;          // 0x18 32kHz Internal Oscillator // OSC32K Control 
   union
   {
    unsigned char OSCULP32K; // 0x1C 32kHz Ultra Low Power Internal Oscillator // OSCULP32K Control 
    unsigned      RES2;
   };
   unsigned OSC8M;           // 0x20 8MHz Internal Oscillator // OSC8M Control
   union
   { 
    unsigned short DFLLCTRL; // 0x24 DFLL48M Control 
    unsigned       RES3;
   };
   unsigned DFLLVAL;        // 0x28 DFLL48M Value 
   unsigned DFLLMUL;        // 0x2C DFLL48M Multiplier
   union
   { 
    unsigned char DFLLSYNC; // 0x30 DFLL48M Synchronization 
    unsigned      RES4;
   };
   unsigned BOD33;           // 0x34 3.3V Brown-Out Detector // BOD33 Control 
   unsigned RES5;
   union
   {
    unsigned short VREG;     // 0x3C Voltage Regulator System // VREG Control
    unsigned RES6;
   };
   unsigned VREF;           // 0x40 Voltage References System // VREF Control
   union
   { 
    unsigned char DPLLCTRLA; // 0x44 DPLL Control A 
    unsigned RES7;
   };
   unsigned DPLLRATIO;        // 0x48 DPLL Ratio Control 
   unsigned DPLLCTRLB;        // 0x4C DPLL Control B 
   unsigned char DPLLSTATUS;  // 0x50 DPLL Status 
   void regs()const volatile;
  } SYSCTRL;
 }
}


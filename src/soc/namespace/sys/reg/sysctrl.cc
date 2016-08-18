//---------------------------
//sysctrl [1] 16.7
//(c) H.Buchmann FHNW 2016
//----------------------------
IMPLEMENTATION(reg_sysctrl,$Id$)
#include "sys/reg/sysctrl.h"
#include "sys/deb/deb.h"
namespace sys
{
 namespace reg
 {
#define REG(name) \
deb::hex(name,10);deb::out(" (");deb::hex((void*)&name);deb::out(")\t"#name"\n")
  void SYSCTRL::regs()const volatile
  {
   REG(INTENCLR);    // 0x00 Interrupt Enable Clear 
   REG(INTENSET);    // 0x04 Interrupt Enable Set 
   REG(INTFLAG);     // 0x08 Interrupt Flag Status and Clear 
   REG(PCLKSR);      // 0x0C Power and Clocks Status 
   REG(XOSC);        // 0x10 External Multipurpose Crystal Oscillator // XOSC Control 
   REG(XOSC32K);     // 0x14 32kHz External Crystal Oscillator // XOSC32K Control 
   REG(OSC32K);      // 0x18 32kHz Internal Oscillator // OSC32K Control 
   REG(OSCULP32K);   // 0x1C 32kHz Ultra Low Power Internal Oscillator // OSCULP32K Control 
   REG(OSC8M);       // 0x20 8MHz Internal Oscillator // OSC8M Control 
   REG(DFLLCTRL);    // 0x24 DFLL48M Control 
   REG(DFLLVAL);     // 0x28 DFLL48M Value 
   REG(DFLLMUL);     // 0x2C DFLL48M Multiplier 
   REG(DFLLSYNC);    // 0x30 DFLL48M Synchronization 
   REG(BOD33);       // 0x34 3.3V Brown-Out Detector // BOD33 Control 
   REG(VREG);        // 0x3C Voltage Regulator System // VREG Control 
   REG(VREF);        // 0x40 Voltage References System // VREF Control 
   REG(DPLLCTRLA);   // 0x44 DPLL Control A 
   REG(DPLLRATIO);   // 0x48 DPLL Ratio Control 
   REG(DPLLCTRLB);   // 0x4C DPLL Control B 
   REG(DPLLSTATUS);  // 0x50 DPLL Status 
  }
 }
}

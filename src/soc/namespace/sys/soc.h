#pragma once
//---------------------------
//soc
//(c) H.Buchmann FHNW 2016
//[1] Atmel | SMART SAM D21 Datasheet
//    Atmel-42181-SAM-D21_Datasheet.pdf
//---------------------------
INTERFACE(sys_soc,$Id$)
#include "sys/armv6-m.h"
#include "sys/reg/sercom.h"
#include "sys/reg/gclk.h"
#include "sys/reg/dmac.h"
namespace sys
{
 class SOC:public ARMv6_M  //singleton
 {
  public: //[1] 11. Peripherals Configuration Summary
   enum PID  //TODO add more and more devices
   { 
    AHB_APB_BRIDGE_A,
    PAC0,
    PM,
    SYSCTRL,
    GCLK,
    WDT,
    RTC,
    EIC,
    AHB_APB_BRIDGE_B,
    PAC1,
    DSU,
    NVMCTRL,
    PORT,
    DMAC,
    USB,
    MTB,
    AHB_APB_BRIDGE_C,
    PAC2,
    EVSYS,
    SERCOM0,
    SERCOM1,
    SERCOM2,
    SERCOM3,
    SERCOM4,
    SERCOM5,
    TCC0,
    TCC1,
    TCC2,
    TC3,
    TC4,
    TC5,
    TC6,
    TC7,
    ADC,
    AC0,
    DAC,
    PTC,
    I2S,
    AC1,
   };

//interrupts  
   static void arm(PID pid);
   static void disarm(PID pid);

//clocks
   static void clkOn(PID pid){clk(pid,true);}
   static void clkOff(PID pid){clk(pid,false);}

   static const struct SERCOM
   {
    enum ID {COM0,COM1,COM2,COM3,COM4,COM5};
    PID                pid;
    volatile reg::SER& com;
    reg::GCLK::DEVICE  clk;
    reg::DMAC::SRC     rx;
    reg::DMAC::SRC     tx;
   } SERCOM[6];  

  protected:
   SOC(const VTable& vt):ARMv6_M(vt){}
   SOC():SOC(Default){}

  private:
   static const int PID2IRQ[];
   static void clk(PID pid,bool v);
   static const VTable Default;
 };
}

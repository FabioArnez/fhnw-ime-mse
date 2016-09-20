//---------------------------
//soc
//(c) H.Buchmann FHNW 2016
//---------------------------
IMPLEMENTATION(sys_soc,$Id$)
#include "sys/soc.h"
#include "sys/reg/pm.h"
namespace sys
{
 const typename SOC::SERCOM SOC::SERCOM[]=
 {
  {SERCOM0,reg::SER::COM0,reg::GCLK::SERCOM0_CORE,reg::DMAC::SERCOM0_RX,reg::DMAC::SERCOM0_TX},
  {SERCOM1,reg::SER::COM1,reg::GCLK::SERCOM1_CORE,reg::DMAC::SERCOM1_RX,reg::DMAC::SERCOM1_TX},
  {SERCOM2,reg::SER::COM2,reg::GCLK::SERCOM2_CORE,reg::DMAC::SERCOM2_RX,reg::DMAC::SERCOM2_TX},
  {SERCOM3,reg::SER::COM3,reg::GCLK::SERCOM3_CORE,reg::DMAC::SERCOM3_RX,reg::DMAC::SERCOM3_TX},
  {SERCOM4,reg::SER::COM4,reg::GCLK::SERCOM4_CORE,reg::DMAC::SERCOM4_RX,reg::DMAC::SERCOM4_TX}, 
  {SERCOM5,reg::SER::COM5,reg::GCLK::SERCOM5_CORE,reg::DMAC::SERCOM5_RX,reg::DMAC::SERCOM5_TX}, 
 };

 const SOC::VTable SOC::Default=
 {
  StackTop,                                              //unsigned* sp;
  &defaultTrap,       //Entry*   reset;
  &defaultTrap,       //Entry*   nmi;
  &hardFault,         //Entry*   hardFault;
  {                   //Entry*   reserved0[7];
   &defaultTrap,
   &defaultTrap,
   &defaultTrap,
   &defaultTrap,
   &defaultTrap,
   &defaultTrap,
   &defaultTrap
  },        
  
  &defaultTrap,       //Entry*    svCall;
  {                   //Entry*    reserved1[2];
   &defaultTrap,
   &defaultTrap
  },                 
  &defaultTrap,       //Entry*   pendSV;
  &defaultTrap,       //Entry*   sysTick;
  {                   //Entry*   external[N];
   &defaultTrap,      //0x00    <---------- index 0x10
   &defaultTrap,      //0x01
   &defaultTrap,      //0x02
   &defaultTrap,      //0x03
   &defaultTrap,      //0x04
   &defaultTrap,      //0x05
   &defaultTrap,      //0x06
   &defaultTrap,      //0x07
   &defaultTrap,      //0x08
   &defaultTrap,      //0x09
   &defaultTrap,      //0x0a
   &defaultTrap,      //0x0b
   &defaultTrap,      //0x0c
   &defaultTrap,      //0x0d
   &defaultTrap,      //0x0e
   &defaultTrap,      //0x0f
   &defaultTrap,      //0x10
   &defaultTrap,      //0x11
   &defaultTrap,      //0x12
   &defaultTrap,      //0x13
   &defaultTrap,      //0x14
   &defaultTrap,      //0x15
   &defaultTrap,      //0x16
   &defaultTrap,      //0x17
   &defaultTrap,      //0x18
   &defaultTrap,      //0x19
   &defaultTrap,      //0x1a
   &defaultTrap,      //0x1b
   &defaultTrap,      //0x1c
   &defaultTrap,      //0x1d
   &defaultTrap,      //0x1e
   &defaultTrap,      //0x1f
  }
 };
 
 const int SOC::PID2IRQ[]=
 {
  -1,// AHB_APB_BRIDGE_A,
  -1,// PAC0,
   0,// PM,
   1,// SYSCTRL,
  -1,// GCLK,
   2,// WDT,
   3,// RTC,
   4,// EIC,
  -1,// AHB_APB_BRIDGE_B,
  -1,// PAC1,
  -1,// DSU,
   5,// NVMCTRL,
  -1,// PORT,
   6,// DMAC,
   7,// USB,
  -1,// MTB,
  -1,// AHB_APB_BRIDGE_C,
  -1,// PAC2,
   8,// EVSYS,
   9,// SERCOM0,
  10,// SERCOM1,
  11,// SERCOM2,
  12,// SERCOM3,
  13,// SERCOM4,
  14,// SERCOM5,
  15,// TCC0,
  16,// TCC1,
  17,// TCC2,
  18,// TC3,
  19,// TC4,
  20,// TC5,
  21,// TC6,
  22,// TC7,
  23,// ADC,
  24,// AC0,
  25,// DAC,
  26,// PTC,
  27,// I2S,
  24,// AC1 //the same as AC0
 };
 
 void SOC::arm(PID pid)
 {
  int irq=PID2IRQ[pid];
  if (irq<0) return;
  ARMv6_M::arm(irq);
 }
 
 void SOC::disarm(PID pid)
 {
  int irq=PID2IRQ[pid];
  if (irq<0) return;
  ARMv6_M::disarm(irq);
 }
 
 void SOC::clk(PID pid,bool v)
 {
  static const unsigned APBAMASK[]=
  {
  (1<<0),  //PAC0,
  (1<<1),  //PM,
  (1<<2),  //SYSCTRL,
  (1<<3),  //GCLK,
  (1<<4),  //WDT,
  (1<<5),  //RTC,
  (1<<6),  // EIC,
  };
  
  static const unsigned APBCMASK[]=
  {
   1<< 1,  // EVSYS,
   1<< 2,  // SERCOM0,
   1<< 3,  // SERCOM1,
   1<< 4,  // SERCOM2,
   1<< 5,  // SERCOM3,
   1<< 6,  // SERCOM4,
   1<< 7,  // SERCOM5,
   1<< 8,  // TCC0,
   1<< 9,  // TCC1,
   1<<10,  // TCC2,
   1<<11,  // TC3,
   1<<12,  // TC4,
   1<<13,  // TC5,
   1<<14,  // TC6,
   1<<15,  // TC7,
   1<<16,  // ADC,
   1<<17,  // AC0,
   1<<18,  // DAC,
   1<<19,  // PTC,
   1<<20,  // I2S,
   1<<21,  // AC1
  };
  if (pid<PAC0) return;
  if (pid<=EIC)
     {
      if (v)  reg::PM.APBAMASK|= APBAMASK[pid-PAC0];
         else reg::PM.APBAMASK&=~APBAMASK[pid-PAC0];
      return;
     }
  if (pid<EVSYS) return;
  if (v)  reg::PM.APBCMASK|= APBCMASK[pid-EVSYS];
     else reg::PM.APBCMASK&=~APBCMASK[pid-EVSYS];
 }
 
}


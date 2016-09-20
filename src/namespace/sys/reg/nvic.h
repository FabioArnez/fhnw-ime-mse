#pragma once
//---------------------------
//nvic nested vectored interrupt controller
//(c) H.Buchmann FHNW 2014
// [1] ARMv6-M Architecture Reference Manual
//     DDI0419C_arm_architecture_v6m_reference_manual.pdf
// TODO check if valid for other architectures too
//---------------------------
INTERFACE(sys_reg_nvic,$Id$)
#include "sys/hwreg.h"
namespace sys
{
 namespace reg
 {
  template<unsigned N>
  struct NVIC
  {
   unsigned ISER[0x20];
   unsigned ICER[0x20];
   unsigned ISPR[0x20];
   unsigned ICPR[0x20];
   ResW<0x300,0x400> RES0;
   unsigned IPR[0];
   void arm(unsigned id) volatile//0<=id<N 
   {
    if (id>=N) return;
    unsigned idx=id/32;
	unsigned bit=id%32;
	ISER[idx]=(1<<bit);
   }

   void disarm(unsigned id) volatile
   {
    if (id>=N) return;
    unsigned idx=id/32;
	unsigned bit=id%32;
	ICER[idx]=(1<<bit);
   }
  };
  
#if 0
//TODO make it works
  template<unsigned N> //N the number of interrups
  struct NVIC
  {
   static const unsigned SIZ=(N-1)/32 +1;
   unsigned ISER[SIZ];          // 0x000
   ResW<0x000+sizeof(ISER),0x180>  RES0;
   unsigned ICER[SIZ];          // 0x180
   ResW<0x180+sizeof(ICER),0x200>  RES1;
   unsigned ISPR[SIZ];          // 0x200
   ResW<0x200+sizeof(ISPR),0x280>  RES2;
   unsigned ICPR[SIZ];          // 0x280
   ResW<0x280+sizeof(ICPR),0x400>  RES3;
   unsigned IPR[(N-1)/4 +1];    // 0x400
  };
#endif
 }
}

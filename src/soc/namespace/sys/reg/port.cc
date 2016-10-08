//------------------------------
//port
// Atmel | SMART SAM D21 Datasheet
// [1] Atmel-42181-SAM-D21_Datasheet.pdf
//(c) H.Buchmann FHNW 2016
//------------------------------
IMPLEMENTATION(sys_reg_port,$Id$)
#include "sys/reg/port.h"
//#include "sys/deb/deb.h"
namespace sys
{
 namespace reg
 {
#if 1
  void PORT::cfg(PIN p,unsigned val) volatile
  {
   static const unsigned  MASK=0xff;
   unsigned idx=p/4;
   unsigned shift=(8*(p%4));
   unsigned cfg=PINCFG[idx];
   unsigned mask=MASK<<shift;
   cfg&=~mask;
   cfg|=((0xff&val)<<shift);
   PINCFG[idx]=cfg;
  }
  
  void PORT::mux(PIN p,FUNC f) volatile
  {
   cfg(p,0x1);
   static const unsigned  MASK=0xf;
   unsigned idx=p/8;
   unsigned shift=(4*(p%8));
   unsigned pmux=PMUX[idx];
   unsigned mask=(MASK<<shift);
   pmux&=~mask;
   pmux|=(f<<shift);
   PMUX[idx]=pmux;
  }

  void PORT::mux(MUX_PIN mp,FUNC f)
  {
   if (mp<PA_END)
      {
       A.mux((PIN)mp,f); //call appropriate mux *not* this one
       return;
      }
   B.mux((PIN)((unsigned)mp-(unsigned)PA_END),f);    
  } 
#endif  
 }
}

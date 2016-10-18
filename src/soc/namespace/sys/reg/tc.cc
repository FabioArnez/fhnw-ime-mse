//---------------------------
//tc timer counter
//(c) H.Buchmann 2016
// [1] Atmel | SMART SAM D21 Datasheet
//   Atmel-42181-SAM-D21_Datasheet.pdf
// 29.TC - Timer/Counter
//---------------------------
IMPLEMENTATION(sys_reg_tc,$Id$)
#include "sys/reg/tc.h"

//uncomment for debugging
#define TC_DEBUG
#include "sys/deb/deb.h"

namespace sys
{
 namespace reg
 {
#define REG(name) \
deb::hex(name,8);\
deb::out(" (");deb::out((void*)&name);\
deb::out(") "#name);sys::deb::newln()

  void TC::regs() const volatile
  {
   REG(CTRLA);	    // 0x00
   REG(READREQ);    // 0x02
   REG(CTRLBCLR);   // 0x04
   REG(CTRLBSET);   // 0x05
   REG(CTRLC);	    // 0x06
   REG(DBGCTRL);    // 0x08
   REG(EVCTRL);	    // 0x0a
   REG(INTENCLR);   // 0x0c
   REG(INTENSET);   // 0x0d
   REG(INTFLAG);    // 0x0e
   REG(STATUS);	    // 0x0f
   REG(COUNT16);    // 0x10
   REG(COUNT32);    // 0x10
   REG(CC16[0]);    // 0x18 
   REG(CC16[1]);    // 0x1a   
   REG(CC32[0]);    // 0x18 
   REG(CC32[1]);    // 0x1c   
  }
  
  void TC::reset() volatile
  {
   CTRLA=0x1; //reset
   while((CTRLA&1) && (STATUS&(1<<31)))
   {
   }
  }

  void TC::enable() volatile
  {
   CTRLA|=(1<<1);             //enable
  }
 }
}

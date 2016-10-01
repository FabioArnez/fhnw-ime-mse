//--------------------------
//wdt watch dog
//(c) H.Buchmann FHNW 2016
//--------------------------
IMPLEMENTATION(sys_reg_wdt,$Id$)
//#define SYS_WDT_DEBUG
#include "sys/reg/wdt.h"
#include "sys/deb/deb.h"
namespace sys
{
 namespace reg
 {
#define REG(name) \
deb::hex(name,10);deb::out("\t(");deb::hex((void*)&name);deb::out(")\t"#name"\n")
  void WDT::regs() volatile const
  {
   REG(CTRL);     //0x00
   REG(CONFIG);   //0x01
   REG(EWCTRL);   //0x02
   REG(res);      //0x03
   REG(INTENCLR); //0x04
   REG(INTENSET); //0x05
   REG(INTFLAG);  //0x06
   REG(STATUS);   //0x07
   REG(CLEAR);    //0x08
  }

#ifdef SYS_WDT_DEBUG
   class Debug
   {
    static Debug debug;
    Debug();
   };

   Debug Debug::debug;

   Debug::Debug()
   {
    deb::out("-------------------------------------------\n");
    WDT.CLEAR=0xa5;
    WDT.regs();
   }
#endif
 }
}

//-----------------------------
//nvmctrl
//(c) H.Buchmann FHNW 2016
//-----------------------------
IMPLEMENTATION(sys_reg_nvmctrl,$Id$)
#include "sys/reg/nvmctrl.h"
#include "sys/deb/deb.h"
//#define SYS_REG_NVMCTRL_DEBUG
namespace sys
{
 namespace reg
 {
#define REG(name) \
deb::hex(name,10);deb::out("\t(");deb::hex((void*)&name);deb::out(")\t"#name"\n")
  void NVMCTRL::regs() const volatile
  {
   REG(CTRLA);   //0x00
   REG(CTRLB);   //0x04
   REG(PARAM);   //0x08
   REG(INTENCLR);//0x0c
   REG(INTENSET);//0x10
   REG(INTFLAG); //0x14
   REG(STATUS);  //0x18
   REG(ADDR);    //0x1c
   REG(LOCK);    //0x20)
  }
 }
}

#ifdef SYS_REG_NVMCTRL_DEBUG
class Debug
{
 static Debug debug;
 Debug();
};

Debug Debug::debug;

Debug::Debug()
{
 sys::reg::NVMCTRL.regs();
}
#endif

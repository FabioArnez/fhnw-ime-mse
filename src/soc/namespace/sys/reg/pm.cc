//--------------------------
//pm power manager
//(c) H.Buchmann FHNW 2016
//--------------------------
IMPLEMENTATION(sys_reg_pm,$Id$)
#include "sys/reg/pm.h"
#include "sys/deb/deb.h"

//#define SYS_REG_PM_DEBUG
#define REG(name) \
deb::hex(name,10);deb::out(" (");deb::hex((void*)&name);deb::out(") "#name"\n")
namespace sys
{
 namespace reg
 {
  void PM::regs() const volatile
  {
   REG(CTRL);
   REG(SLEEP);
   REG(CPUSEL);
   REG(APBASEL);
   REG(APBBSEL);
   REG(ALBCSEL);
   REG(AHBMASK); 
   REG(APBAMASK);
   REG(APBBMASK);
   REG(APBCMASK);
   REG(INTENCLR);
   REG(INTENSET);
   REG(INTFLAG); 
   REG(RCAUSE);
  } 
 }
}

#ifdef SYS_REG_PM_DEBUG
class Debug
{
 static Debug debug;
 Debug();
};

Debug Debug::debug;

Debug::Debug()
{
 sys::reg::PM.regs();
}

#endif


//-----------------------------
//dmac
//(c) H.Buchmann FHNW 2016
//-----------------------------
IMPLEMENTATION(sys_reg_dmac,$Id$)
#include "sys/reg/dmac.h"
#define DMAC_DEBUG
#include "sys/deb/deb.h"
namespace sys
{
 namespace reg
 {
#ifdef DMAC_DEBUG 
#define DMAC_REG(name) \
deb::hex((unsigned)name,10);deb::out(" (");deb::hex((void*)&name);deb::out(") "#name"\n")
  void DMAC::regs() const volatile
  {
   DMAC_REG(CTRL);      
   DMAC_REG(CRCCTRL);   
   DMAC_REG(CRCDATAIN); 
   DMAC_REG(CRCCHKSUM); 
   DMAC_REG(CRCSTATUS); 
   DMAC_REG(DBGCTRL);   
   DMAC_REG(SWTRIGCTRL);
   DMAC_REG(PRICTRL0);  
   DMAC_REG(INTPEND);   
   DMAC_REG(INTSTATUS); 
   DMAC_REG(BUSYCH);    
   DMAC_REG(PENDCH);    
   DMAC_REG(ACTIVE);    
   DMAC_REG(BASEADDR);  
   DMAC_REG(WRBADDR);   
  }

  void DMAC::regs(unsigned chid) volatile
  {
   CHID=chid;
   DMAC_REG(CHID);      
   DMAC_REG(CHCTRLA);   
   DMAC_REG(CHCTRLB);   
   DMAC_REG(CHINTENCLR);
   DMAC_REG(CHINTENSET);
   DMAC_REG(CHINTFLAG); 
   DMAC_REG(CHSTATUS);  
  }
  
#define TREG(name) \
deb::hex((unsigned)name,10);deb::out(" (");deb::hex((void*)&name);deb::out(") "#name"\n")  
  void DMAC::Transfer::regs() const volatile
  {
   TREG(BTCTRL);
   TREG(BTCNT);
   TREG(SRC);
   TREG(DST);
   TREG(next);
  }
#endif
 }//namespace reg
}//namespace sys

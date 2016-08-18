//--------------------------
//sercom
//(c) H.Buchmann FHNW 2016
//--------------------------
IMPLEMENTATION(sys_reg_sercom,$Id$)
#include "sys/reg/sercom.h"
#define SERCOM_DEBUG
#include "sys/deb/deb.h"

namespace sys
{
 namespace reg
 {
  void SER::mux(const SER::PAD& p)
  {
   PORT::mux(p.pad);
  }
  
#ifdef SERCOM_DEBUG

#define REG(name) \
deb::hex(name,10);deb::out(" (");deb::hex((void*)&name);deb::out(") "#name"\n") 
  void SER::SPI::regs() const volatile
  {
   REG(CTRLA);     // 0x00 Control A
   REG(CTRLB);     // 0x04 Control B
   REG(BAUD);      // 0x0C Baud Rate
   REG(INTENCLR);  // 0x14 Interrupt Enable Clear
   REG(INTENSET);  // 0x16 Interrupt Enable Set
   REG(INTFLAG);   // 0x18 Interrupt Flag Status and Clear
   REG(STATUS);    // 0x1A Status
   REG(SYNCBUSY);  // 0x1C Syncbusy
   REG(ADDR);   // 0x24 Address
   REG(DATA);   // 0x28 Data
   REG(DBGCTRL);   // 0x30 Debug Control
  }
  
  void SER::I2CM::regs() const volatile
  {
   REG(CTRLA);        // 0x00 Control A 
   REG(CTRLB);        // 0x04 Control B
   REG(BAUD);         // 0x0c Baud Rate
   REG(INTENCLR);     // 0x14 Interrupt Enable Clear 
   REG(INTENSET);     // 0x16 Interrupt Enable Set 
   REG(INTFLAG);      // 0x18 Interrupt Flag Status and Clear
   REG(STATUS);       // 0x1a Status 
   REG(SYNCBUSY);     // 0x1c Syncbusy 
   REG(ADDR);         // 0x24 Address 
   REG(DATA);         // 0x28 Data
   REG(DBGCTRL);      // 0x30 Debug Control 
  }


  void SER::USART::regs() const volatile
  {
   REG(CTRLA);         // 0x00 Control A 
   REG(CTRLB);         // 0x04 Control B
   REG(BAUD);          // 0x0c Baud Rate
   REG(RXPL);
   REG(INTENCLR);
   REG(INTENSET);      // 0x16 Interrupt Enable Set
   REG(INTFLAG);       // 0x18 Interrupt Flag Status and Clear
   REG(STATUS);        // 0x1a Status 
   REG(SYNCBUSY);      // 0x1c Syncbusy
   REG(DATA);          // 0x28 Data
   REG(DBGCTRL);       // 0x30 Debug Control 
  }
#endif
 }
}

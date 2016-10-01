//---------------------------
//nvm
//(c) H.Buchmann FHNW 2016
//---------------------------
IMPLEMENTATION(sys_nvm,$Id$)
#include "sys/nvm.h"
#include "sys/reg/nvmctrl.h"

#define SYS_NVM_DEBUG

#include "sys/deb/deb.h"
#include "sys/msg.h"
#include "sys/reg/wdt.h"

namespace sys
{
#define REG0(name) \
deb::hex(name,10);deb::out("\t"#name"\n")

void NVM::Calib::regs() const
{
deb::out("sizeof(Calib)=",sizeof(*this));
REG0(res0              );
REG0(res1              );
REG0(res2              );
REG0(ADC_LINEARITY     );
REG0(ADC_BIASCAL       );
REG0(OSC32K_CAL        );
REG0(USB_TRANSN        );
REG0(USB_TRANSP        ); 
REG0(USB_TRIM          );
REG0(DFLL48M_COARSE_CAL);
REG0(DFLL48M_FINE_CAL  );
sys::msg.dump((const unsigned char*const)this,sizeof(*this));
}

void NVM::UserRow::regs() const
{
REG0(BOOTPROT        );
REG0(res0            );
REG0(EEPROM          );
REG0(res1            );
REG0(BOD33_Level     );
REG0(BOD33_Enable    );
REG0(BOD33_Action    );
REG0(res2            );
REG0(WDT_Enable      );
REG0(WDT_Always_On   );
REG0(WDT_Period      );
REG0(WDT_Window      );
REG0(WDT_EWOFFSET    );
REG0(WDT_WEN         );
REG0(BOD33_Hysteresis);
REG0(res3            );
REG0(res4            );
REG0(LOCK            );
}


#ifdef SYS_NVM_DEBUG
class Demo
{
 static Demo demo;
 Demo();
};

Demo Demo::demo;

Demo::Demo()
{
// NVM::Calib.regs();
 NVM::UserRow.regs();
// reg::NVMCTRL.regs();
}
#endif
}

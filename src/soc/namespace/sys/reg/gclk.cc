//----------------------
//gclk
//(c) H.Buchmann FHNW 2016
//----------------------
IMPLEMENTATION(sys_reg_gclk,$Id$)
#include "sys/reg/gclk.h"
#include "sys/deb/deb.h"
namespace sys
{
 namespace reg
 {
  void GCLK::info()
  {
   static const char* G[]={"G0","G1","G2","G3","G4","G5","G6","G7","G8"};
   static const char* SRC[]=
   {
     "     XOSC",
     "   GCLKIN",
     " GCLKGEN1",
     "OSCULP32K",
     "   OSC32K",
     "  XOSC32K",
     "    OSC8M",
     "  DFLL48M",
     " FDPLL96M"   
   };
   deb::out("Gi           SRC  DIV\n"
            "---------------------\n");
   for(unsigned g=G0;g<=G8;++g)
   {
    deb::out(G[g]);deb::out("     ");
    reg::GCLK.GENCTRL.id=g;
    unsigned genctrl=0b11111&(reg::GCLK.GENCTRL.val>>8);
    deb::out( (genctrl<=FDPLL96M)?SRC[genctrl]:"  ---------");
    reg::GCLK.GENDIV.id=(unsigned char)g;
    unsigned gendiv=0xffff&(reg::GCLK.GENDIV.val>>8);
    deb::out(gendiv,5);deb::newln(); 
   }

   static const char* DEVICE[]=
		      {
		      "     DFLL48M_REF",
		      "            DPLL",
		      "        DPLL_32K",
		      "             WDT",
		      "             RTC",
		      "             EIC",
		      "             USB",
		      " EVSYS_CHANNEL_0",
		      " EVSYS_CHANNEL_1",
		      " EVSYS_CHANNEL_2",
		      " EVSYS_CHANNEL_3",
		      " EVSYS_CHANNEL_4",
		      " EVSYS_CHANNEL_5",
		      " EVSYS_CHANNEL_6",
		      " EVSYS_CHANNEL_7",
		      " EVSYS_CHANNEL_8",
		      " EVSYS_CHANNEL_9",
		      "EVSYS_CHANNEL_10",
		      "EVSYS_CHANNEL_11",
		      "    SERCOMx_SLOW",
		      "    SERCOM0_CORE",
		      "    SERCOM1_CORE",
		      "    SERCOM2_CORE",
		      "    SERCOM3_CORE",
		      "    SERCOM4_CORE",
		      "    SERCOM5_CORE",
		      "            TCC0",
		      "            TCC1",
		      "            TCC2",
		      "             TC3",
		      "             TC4",
		      "             TC5",
		      "             TC6",
		      "             TC7",
		      "             ADC",
		      "          AC_DIG",
		      "          AC_ANA",
		      "             DAC",
		      "             PTC",
		      "           I2S_0",
		      "           I2S_1"
		      };
   
   deb::out("\n"
            "          DEVICE   Gi\n"
            "---------------------\n");
   for(unsigned d=DFLL48M_REF;d<=I2S_1;++d)
   {
    reg::GCLK.CLKCTRL.id=d;
    unsigned clkctrl=reg::GCLK.CLKCTRL.val>>8;
    if ((1<<6)&clkctrl)
       { //enabled
        unsigned g=0b1111&clkctrl;
        deb::out(DEVICE[d]);deb::out("   ");
	deb::out((g<=G8)?G[g]:"--");
	deb::newln();
       }
   }
  }
 }
}

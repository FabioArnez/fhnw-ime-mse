//----------------------------
//adc
//(c) H.Buchmann FHNW 2016
//----------------------------
IMPLEMENTATION(sys_reg_adc,$Id$)
#include "sys/reg/adc.h"
#include "sys/reg/port.h"
#define ADC_DEBUG
#include "sys/deb/deb.h"

namespace sys
{
 namespace reg
 {
  void ADC::mux(Pin p)
  {
   static const sys::reg::PORT::MUX_PIN MPin[]
   {
    reg::PORT::PA02, //0
    reg::PORT::PA03, //1
    reg::PORT::PB08, //2
    reg::PORT::PB09, //3
    reg::PORT::PA04, //4
    reg::PORT::PA05, //5
    reg::PORT::PA06, //6
    reg::PORT::PA07, //7
    reg::PORT::PB00, //8
    reg::PORT::PB01, //9
    reg::PORT::PB02, //10
    reg::PORT::PB03, //11
    reg::PORT::PB04, //12
    reg::PORT::PB05, //13
    reg::PORT::PB06, //14
    reg::PORT::PB07, //15
    reg::PORT::PA08, //16
    reg::PORT::PA09, //17
    reg::PORT::PA10, //18
    reg::PORT::PA11  //19
   };
   if (p<=A19) reg::PORT::mux(MPin[p],reg::PORT::F_B);
  }

const char*const ADC::pinName(Pin p)
{
 static const char* PinName[]= //(arduino pin)
 {
  "A00(A0)",       //0
  "A01",           //1
  "A02(A1)",       //2
  "A03(A2)",       //3
  "A04(A3)",       //4
  "A05(A4)",       //5
  "A06",           //6
  "A07",           //7
  "A08",           //8
  "A09",           //9
  "A10(A5)",       //10
  "A11",           //11
  "A12",           //12
  "A13",           //13
  "A14",           //14
  "A15",           //15
  "A16",           //16
  "A17",           //17
  "A18",           //18
  "A19",           //19
  "TEMP" ,         //0x18
  "BANDGAP" ,      //0x19
  "SCALEDCOREVCC", //0x1a
  "SCALEDIOVCC" ,  //0x1b
  "DAC"            //0x1c
 };
 if (p<=A19) return PinName[p];
 if ((TEMP<=p) && (p<=DAC)) return PinName[20+p-TEMP];
 return "---"; 
}
#ifdef ADC_DEBUG
#define REG(name) \
deb::hex(name,8);\
deb::out(" (");deb::hex((void*)&name);\
deb::out(") "#name"\n")
  void ADC::regs() const volatile
  {
   REG(CTRLA);     
   REG(REFCTRL);    
   REG(AVGCTRL);    
   REG(SAMPCTRL);   
   REG(CTRLB);      
   REG(WINCTRL);    
   REG(SWTRIG);     
   REG(INPUTCTRL);  
   REG(EVCTRL);     
   REG(INTENCLR);   
   REG(INTENSET);   
   REG(INTFLAG);    
   REG(STATUS);     
   REG(RESULT);     
   REG(WINLT);      
   REG(WINUT);      
   REG(GAINCORR);   
   REG(OFFSETCORR); 
   REG(CALIB);      
   REG(DBGCTRL);
  }
#endif 
 }
}

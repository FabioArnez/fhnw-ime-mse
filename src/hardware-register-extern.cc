//----------------------------
//hardware-register accessing hardware registers
//(c) H.Buchmann FHNW 2016
// [1] Atmel | SMART  SAM D21J, SAM D21G, SAM D21E, 
//     ARM Cortex-M0+ based Embedded Flash Microcontroller
//       Atmel-42181-SAM-D21_Datasheet-1.pdf
//----------------------------
IMPLEMENTATION(hardware_register,$Id$)
#include "sys/soc.h"
#include "sys/msg.h"
/*
 Arduino Pins:
  0: RX
  1: TX
  
 Cable Pins https://www.adafruit.com/product/70
  1: BLACK   GND
  2: BROWN   CTS
  3: RED     3.3 V
  4: ORANGE  TXD
  5: YELLOW  RXD
  6: GREEN   RTS
  
 Cable Pins https://www.adafruit.com/products/954
    BLACK    GND
    RED      3.3 V
    GREEN    TXD
    WHITE    RXD
    
*/
//------------------------------------------ reserved space
 template<typename T,unsigned FROM,unsigned TO>
 struct Res
 {
  static_assert(FROM<=TO,"FROM>TO");
  T r[(TO-FROM)/sizeof(T)];
 }; 

 template<unsigned FROM,unsigned TO> using ResW=Res<unsigned,FROM,TO>; 

//------------------------------------------ [1] 26.7 the hardware register
struct USART
{
 unsigned        CTRLA;        // 0x00 Control A 
 unsigned        CTRLB;        // 0x04 Control B
 ResW<0x08,0x0c> RES0;
 unsigned short  BAUD;          // 0x0c Baud Rate
 union                          // 0x0e
 {
  unsigned char  RXPL;
  unsigned short RES1;
 }; 
 ResW<0x10,0x14> RES2;
 union                           // 0x14 Interrupt Enable Clear
 {
  unsigned char  INTENCLR;
  unsigned short RES3; 
 };
 union
 {
  unsigned char  INTENSET;       // 0x16 Interrupt Enable Set
  unsigned short RES4;
 };
 union
 {
  unsigned char  INTFLAG;        // 0x18 Interrupt Flag Status and Clear
  unsigned short RES5;
 };
 unsigned short  STATUS;         // 0x1a Status 
 unsigned        SYNCBUSY;       // 0x1c Syncbusy
 ResW<0x20,0x28> RES6;
 union
 {
  unsigned short DATA;           // 0x28 Data
  unsigned RES7;
 };
 ResW<0x2c,0x30> RES8;
 unsigned char   DBGCTRL;        // 0x30 Debug Control 

//TODO implement regs()
// list the registers:
//  address value name 
 void regs() const volatile; 
};


/*------------------------------------------ the pins and their function
see [1] section 7
Arduino SAMD    Function 
  ------------------------------------------ 
Pin 0   PA11    C		RX SERCOM0/PAD[3]
Pin 1   PA10    C		TX SERCOM0/PAD[2]
*/

//------------------------------------------ the app
class App
{
 static App app;
 static volatile USART usart;          //declaration
/* TODO
 remove volatile
 and compile with optimize O0,O1,O2
*/
 void init(); 
 App();
 void out(unsigned char ch);
 unsigned char in();
};


#pragma GCC optimize ("O2")
void App::out(unsigned char ch)
{
 while((usart.INTFLAG & (1<<0))==0)
 {
 }
 usart.DATA=ch;
}

#pragma GCC optimize ("O2")
unsigned char App::in()
{
 while((usart.INTFLAG & (1<<2))==0)
 {
 }
 return usart.DATA;
}

App App::app;

void App::init()
{
 sys::reg::PORT::mux(sys::reg::PORT::PA11,sys::reg::PORT::F_C);
 sys::reg::PORT::mux(sys::reg::PORT::PA10,sys::reg::PORT::F_C);
 sys::SOC::clkOn(sys::SOC::SERCOM0); 
 sys::reg::GCLK.gen2dev(sys::reg::GCLK::G0,sys::reg::GCLK::SERCOM0_CORE);

//usage
 usart.CTRLA|=1; 
 while( (usart.CTRLA&1) || (usart.SYNCBUSY&1))
 {
 } 
 usart.BAUD =0x0000ff2d;
 usart.CTRLA=0x40310006;
 usart.CTRLB=0x00030000;
 while(usart.SYNCBUSY&(1<<1)){}
}

App::App()
{
 sys::msg<<"---------------- "<<__FILE__<<"\n";
 init();
 while(true)
 {
  out(in());
 }
}

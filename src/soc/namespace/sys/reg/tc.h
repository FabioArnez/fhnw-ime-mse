#pragma once
//---------------------------
//tc timer counter
//(c) H.Buchmann 2016
// [1] Atmel | SMART SAM D21 Datasheet
//   Atmel-42181-SAM-D21_Datasheet.pdf
// 29.TC - Timer/Counter
//---------------------------
INTERFACE(sys_reg_tc,$Id$)
namespace sys
{
 namespace reg
 {
  struct TC
  {
   enum PRESCALE {DIV1,DIV2,DIV4,DIV8,DIV16,
                  DIV64,
		  DIV256,
		  DIV1024};
   unsigned short CTRLA;      // 0x00
   unsigned short READREQ;    // 0x02
   unsigned char  CTRLBCLR;   // 0x04
   unsigned char  CTRLBSET;   // 0x05
   unsigned char  CTRLC;      // 0x06
   unsigned char  RES0;       // 0x07
   unsigned char  DBGCTRL;    // 0x08
   unsigned char  RES1;       // 0x09
   unsigned short EVCTRL;     // 0x0a
   unsigned char  INTENCLR;   // 0x0c
   unsigned char  INTENSET;   // 0x0d
   unsigned char  INTFLAG;    // 0x0e
   unsigned char  STATUS;     // 0x0f
   union                      // 0x10
   {
    unsigned short COUNT16;
    unsigned       COUNT32;
   };
   unsigned short RES2[2];    // 0x14
   union
   {
    unsigned short CC16[2];   // 0x18
    unsigned       CC32[2];
   }; 
   void regs() const volatile;               //for debugging   
  };// __attribute__((packed));

  extern volatile TC TC3;
  extern volatile TC TC4;
  extern volatile TC TC5;
  extern volatile TC TC6;
  extern volatile TC TC7;  
 }
}

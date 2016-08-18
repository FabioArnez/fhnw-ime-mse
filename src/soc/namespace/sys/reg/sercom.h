#pragma once
//--------------------------
//sercom
//(c) H.Buchmann FHNW 2016
//[1] pinmux.ods
//--------------------------
INTERFACE(sys_reg_sercom,$Id$)
#include "sys/hwreg.h"
#include "sys/reg/port.h"
namespace sys
{
 namespace reg
 {
  union SER
  {
   struct PAD //see pinmux.ods
   {
    enum ID {P0=0,P1=1,P2=2,P3=3};
    ID             id;
    PORT::PAD      pad;
   };
   
   struct I2CM  //Master
   {
    unsigned CTRLA;               // 0x00 Control A 
    unsigned CTRLB;               // 0x04 Control B
    ResW<0x08,0x0c> RES0;
    unsigned BAUD;                // 0x0c Baud Rate
    ResW<0x10,0x14> RES1;
    union
    {
     unsigned char INTENCLR;      // 0x14 Interrupt Enable Clear 
     unsigned short RES2;
    };
    union
    {
     unsigned char INTENSET;      // 0x16 Interrupt Enable Set 
     unsigned short RES3;
    };
    union
    {
     unsigned char INTFLAG;       // 0x18 Interrupt Flag Status and Clear
     unsigned short RES4;
    };
    unsigned short  STATUS;       // 0x1a Status 
    unsigned        SYNCBUSY;     // 0x1c Syncbusy 
    ResW<0x20,0x24> RES5;
    unsigned ADDR;                // 0x24 Address 
    union
    {
     unsigned short DATA;         // 0x28 Data
     unsigned       RES6;
    };        
    ResW<0x2c,0x30> RES7;
    unsigned char   DBGCTRL;      // 0x30 Debug Control 
    void regs() const volatile;
   } I2CM;  //master
 
   struct I2CS
   {
    unsigned CTRLA;               // 0x00 Control A 
    unsigned CTRLB;               // 0x04 Control B
    ResW<0x08,0x14> RES0;
    unsigned INTENCLR;            // 0x14 Interrupt Enable Clear 
     // INTENSET                     0x16 Interrupt Enable Set 
    unsigned INTFLAG;             // 0x18 Interrupt Flag Status and Clear 
     // STATUS                       0x1a Status 
    unsigned SYNCBUSY;            // 0x1c Syncbusy 
    ResW<0x20,0x24> RES1;
    unsigned ADDR;                // 0x24 Address 
    unsigned DATA;                // 0x28 Data 
   } I2CS;  //slave

   struct SPI
   {
      unsigned       CTRLA;     // 0x00 Control A
      unsigned       CTRLB;     // 0x04 Control B
      ResW<0x08,0x0c> RES0;
      union
      {
       unsigned char  BAUD;      // 0x0C Baud Rate
       ResW<0xC,0x14> RES1;
      };
      union
      {
       unsigned char  INTENCLR;  // 0x14 Interrupt Enable Clear
       unsigned short RES2;
      };
      union
      {
       unsigned char  INTENSET;  // 0x16 Interrupt Enable Set
       unsigned short RES3;
      };
      unsigned char  INTFLAG;   // 0x18 Interrupt Flag Status and Clear
      unsigned short STATUS;    // 0x1A Status
const unsigned       SYNCBUSY;  // 0x1C Syncbusy
      ResW<0x20,0x24> RES4;
      unsigned       ADDR;      // 0x24 Address
      union
      {
       unsigned short DATA;     // 0x28 Data
       unsigned RES5;
      };
      ResW<0x2c,0x30> RES6;
      unsigned char  DBGCTRL;   // 0x30 Debug Control
      void regs() const volatile;
   } SPI;

   struct USART
   {
    unsigned CTRLA;               // 0x00 Control A 
    unsigned CTRLB;               // 0x04 Control B
    ResW<0x08,0x0c> RES0;
    unsigned short BAUD;          // 0x0c Baud Rate
    union                         // 0x0e
    {
     unsigned char  RXPL;
     unsigned short RES1;
    }; 
    ResW<0x10,0x14> RES2;
    union                          // 0x14 Interrupt Enable Clear
    {
     unsigned char INTENCLR;
     unsigned short RES3; 
    };
    union
    {
     unsigned char INTENSET;      // 0x16 Interrupt Enable Set
     unsigned short RES4;
    };
    union
    {
     unsigned char INTFLAG;       // 0x18 Interrupt Flag Status and Clear
     unsigned short RES5;
    };
    unsigned short STATUS;        // 0x1a Status 
    unsigned SYNCBUSY;            // 0x1c Syncbusy
    ResW<0x20,0x28> RES6;
    union
    {
     unsigned short DATA;         // 0x28 Data
     unsigned RES7;
    };
    ResW<0x2c,0x30> RES8;
    unsigned char DBGCTRL;        // 0x30 Debug Control 
    void regs() const volatile;
   } USART;

   static volatile SER COM0;
   static volatile SER COM1;
   static volatile SER COM2;
   static volatile SER COM3;
   static volatile SER COM4;
   static volatile SER COM5;

   static void mux(const PAD& p);
  }; //union SER
 }
}





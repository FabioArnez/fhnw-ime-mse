#pragma once
//----------------------
//gclk
//(c) H.Buchmann FHNW 2016
//----------------------
INTERFACE(sys_reg_gclk,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct GCLK
  {
   enum GEN    {G0,G1,G2,G3,G4,G5,G6,G7,G8};
   enum SRC    {XOSC,
                GCLKIN,
                GCLKGEN1,
                OSCULP32K,
                OSC32K,
                XOSC32K,
                OSC8M,
                DFLL48M,
                FDPLL96M
               };
   enum DEVICE {DFLL48M_REF      = 0x00,//  DFLL48M Reference
                DPLL             = 0x01,//  FDPLL96M input clock source for reference
                DPLL_32K         = 0x02,//  FDPLL96M 32kHz clock for FDPLL96M internal lock timer
                WDT              = 0x03,
                RTC              = 0x04,
                EIC              = 0x05,
                USB              = 0x06,
                EVSYS_CHANNEL_0  = 0x07,
                EVSYS_CHANNEL_1  = 0x08,
                EVSYS_CHANNEL_2  = 0x09,
                EVSYS_CHANNEL_3  = 0x0a,
                EVSYS_CHANNEL_4  = 0x0b,
                EVSYS_CHANNEL_5  = 0x0c,
                EVSYS_CHANNEL_6  = 0x0d,
                EVSYS_CHANNEL_7  = 0x0e,
                EVSYS_CHANNEL_8  = 0x0f,
                EVSYS_CHANNEL_9  = 0x10,
                EVSYS_CHANNEL_10 = 0x11,
                EVSYS_CHANNEL_11 = 0x12,
                SERCOMx_SLOW     = 0x13,
                SERCOM0_CORE     = 0x14,
                SERCOM1_CORE     = 0x15,
                SERCOM2_CORE     = 0x16,
                SERCOM3_CORE     = 0x17,
                SERCOM4_CORE     = 0x18,
                SERCOM5_CORE     = 0x19,
                TCC0             = 0x1a,
                TCC1             = 0x1a,
                TCC2             = 0x1b,
                TC3              = 0x1b,
                TC4              = 0x1c,
                TC5              = 0x1c,
                TC6              = 0x1d,
                TC7              = 0x1d,
                ADC              = 0x1e,
                AC_DIG           = 0x1f,
                AC_ANA           = 0x20,
                DAC              = 0x21,
                PTC              = 0x22,  //PTCReserved
                I2S_0            = 0x23,
                I2S_1            = 0x24
               };

   unsigned char CTRL;          //0x00  Control
   unsigned char STATUS;
   union 
   {
    unsigned short val;
    unsigned char id;
   } CLKCTRL;
   union
   {
    unsigned val;            //32 bit access dont work
    unsigned char id;
   } GENCTRL;                //0x04  Generic Clock Generator Control
   union
   {
    unsigned val;
    unsigned char id;        //0x08  Generic Clock Generator Division
   } GENDIV; 


   void src2gen(SRC src,GEN g,unsigned flags=(1<<0),bool sync=true) volatile //bits 16 .. 21
   {
    GENCTRL.val=(g<< 0)|
              (src<< 8)|
            (flags<<16);
    if (sync) while(STATUS&(1<<7)){}
   }
   
   void gendiv(GEN g,unsigned short div) volatile 
   {
    GENDIV.val=(g<<0)|
             (div<<8);
   }
   
   void gen2dev(GEN g,DEVICE dev,bool clken=true,
                                 bool wrlock=false,
                                 bool sync=true) volatile
   {
    CLKCTRL.val=(dev<< 0)|
                  (g<< 8)|
              (clken<<14)|
             (wrlock<<15);
    if (sync)while(STATUS&(1<<7)){}
   }

   void sync() volatile
   {
    while(STATUS&(1<<7)){}
   }
   
   void reset() volatile //wait until reset done
   {
    CTRL=1;
        while(CTRL&1){}
   }
   
   static void info();
  } /* __attribute__((packed)) */ GCLK;
 }
}




#pragma once
//------------------------------
//port
// Atmel | SMART SAM D21 Datasheet
// [1] Atmel-42181-SAM-D21_Datasheet.pdf
//(c) H.Buchmann FHNW 2016
//------------------------------
INTERFACE(sys_reg_port,$Id$)
#include "sys/hwreg.h"
namespace sys
{
 namespace reg
 {
  struct PORT
  {
   enum PIN  {
              P_00,P_01,P_02,P_03,
              P_04,P_05,P_06,P_07,
              P_08,P_09,P_10,P_11,
              P_12,P_13,P_14,P_15,

              P_16,P_17,P_18,P_19,
              P_20,P_21,P_22,P_23,
              P_24,P_25,P_26,P_27,
              P_28,P_29,P_30,P_31
             };
   enum FUNC {
              F_A,F_B,F_C,F_D,
              F_E,F_F,F_G,F_H
             };
    
   unsigned DIR;             //0x00
   unsigned DIRCLR;          //0x04
   unsigned DIRSET;          //0x08
   unsigned DIRTGL;          //0x0c
   unsigned OUT;             //0x10
   unsigned OUTCLR;          //0x14
   unsigned OUTSET;          //0x18
   unsigned OUTTGL;          //0x1c
   unsigned IN;              //0x20
   unsigned CTRL;            //0x24
   unsigned WRCONFIG;        //0x28
   unsigned RES;             //0x2c
   static const unsigned PMUXN=32/(2*4);
   unsigned PMUX[PMUXN];     //0x30
   static const unsigned PINCFGN=32/4;
   unsigned PINCFG[PINCFGN]; //0x40
   ResW<0x60,0x80> RES1;     //0x60
                             //0x80
   void cfg(PIN p,unsigned val) volatile;
   void mux(PIN p,FUNC f) volatile;
   static volatile PORT A;
   static volatile PORT B;
   static volatile PORT C;

   enum MUX_PIN {
    PA00= 0,PA01= 1,PA02= 2,PA03= 3,PA04= 4,PA05= 5,PA06= 6,PA07= 7,PA08= 8,PA09= 9, 
    PA10=10,PA11=11,PA12=12,PA13=13,PA14=14,PA15=15,PA16=16,PA17=17,PA18=18,PA19=19, 
    PA20=20,PA21=21,PA22=22,PA23=23,PA24=24,PA25=25,        PA27=27,PA28=28, 
    PA30=30,PA31=31,
    PA_END=32,
    
    PB00=32,PB01=33,PB02=34,PB03=35,PB04=36,PB05=37,PB06=38,PB07=39,PB08=40,PB09=41,
    PB10=42,PB11=43,PB12=44,PB13=45,PB14=46,PB15=47,PB16=48,PB17=49, 
                    PB22=52,PB23=53, 
    PB30=62,PB31=63,
    PB_END=64
                };
    struct PAD
    {
     MUX_PIN pin;
     FUNC   func;
    };          
   static void mux(MUX_PIN,FUNC);
   static void mux(const PAD& p){mux(p.pin,p.func);}
  };
 }
}

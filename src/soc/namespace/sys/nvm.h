#pragma once
//---------------------------
//nvm non volatile memory
//(c) H.Buchmann FHNW 2016
//---------------------------
INTERFACE(sys_nvm,$Id$)
namespace sys
{
 struct NVM
 {
#define BIT(name,last,first) name:last-first+1
  static const struct Calib 
  {
   unsigned 
   BIT(res0              , 2, 0),
   BIT(res1              ,14, 3),
   BIT(res2              ,26,15),
   BIT(ADC_LINEARITY     ,34,27),
   BIT(ADC_BIASCAL       ,37,35),
   BIT(OSC32K_CAL        ,44,38),
   BIT(USB_TRANSN        ,49,45),
   BIT(USB_TRANSP        ,54,50), 
   BIT(USB_TRIM          ,57,55),
   BIT(DFLL48M_COARSE_CAL,63,58),
   BIT(DFLL48M_FINE_CAL  ,73,64);
   void regs() const;
  } __attribute__((packed)) Calib;
  
  static const unsigned SerialNumber0;
  static const unsigned SerialNumber[3];
  
  static const struct UserRow
  {
   unsigned
   BIT(BOOTPROT        , 2, 0),
   BIT(res0            , 3, 3),
   BIT(EEPROM          , 6, 4),
   BIT(res1            , 7, 7),
   BIT(BOD33_Level     ,13, 8),
   BIT(BOD33_Enable    ,14,14),
   BIT(BOD33_Action    ,16,15),
   BIT(res2            ,24,17),
   BIT(WDT_Enable      ,25,25),
   BIT(WDT_Always_On   ,26,26),
   BIT(WDT_Period      ,30,27),
   BIT(WDT_Window      ,34,31),
   BIT(WDT_EWOFFSET    ,38,35),
   BIT(WDT_WEN         ,39,39),
   BIT(BOD33_Hysteresis,40,40),
   BIT(res3            ,41,41),
   BIT(res4            ,47,42),
   BIT(LOCK            ,63,48);
   void regs() const;
  } __attribute__((packed)) UserRow;
  
 };
}

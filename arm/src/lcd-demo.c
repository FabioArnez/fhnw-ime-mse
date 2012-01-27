/*----------------------------
  lcd-demo
  (c) H.Buchmann FHNW 2012
  $Id$
------------------------------*/ 
#include <stdio.h>
#include <sys/sys.h>
#include <sys/def-register.h>

extern volatile struct
{
VAR(Timing0     ,0x000      ,RW,0x00000000);/* Horizontal Axis Panel Control Register on page 3-5); */
VAR(Timing1     ,0x004      ,RW,0x00000000);/* Vertical Axis Panel Control Register on page 3-6); */
VAR(Timing2     ,0x008      ,RW,0x00000000);/* Clock and Signal Polarity Control Register on page 3-8); */
VAR(Timing3     ,0x00C      ,RW,0x00000   );/* Line End Control Register on page 3-10); */
VAR(UPBASE      ,0x010      ,RW,0x00000000);/* Upper and Lower Panel Frame Base Address Registers on page 3-10); */
VAR(LPBASE      ,0x014      ,RW,0x00000000);/* Upper and Lower Panel Frame Base Address Registers on page 3-10); */
VAR(Control     ,0x018      ,RW,0x0000    );/* LCD Control Register on page 3-12); */
VAR(IMSC        ,0x01C      ,RW,0x0       );/* Interrupt Mask Set/Clear Register on page 3-14); */
VAR(RIS         ,0x020      ,RO,0x0       );/* Raw Interrupt Status Register on page 3-15); */
VAR(MIS         ,0x024      ,RO,0x0       );/* Masked Interrupt Status Register on page 3-16); */
VAR(ICR         ,0x028      ,WO,0x0       );/* LCD Interrupt Clear Register on page 3-17); */
VAR(UPCURR      ,0x02C      ,RO,0x00000000);/* LCD Upper and Lower Panel Current Address Value Registers on page 3-18); */
VAR(LPCURR      ,0x030      ,RO,0x00000000);/* LCD Upper and Lower Panel Current Address Value Registers on page 3-18); */
ARR(RES1        ,0x034,0x1FC,RO,0x0       );/* Reserved); */
ARR(Palette     ,0x200,0x3FC,RW,0x00000000);/* 256x16-bit Color Palette Registers on page 3-19); */
ARR(RES2        ,0x400,0x7FC,RO,0x0       );/* Reserved); */
ARR(CursorImage ,0x800,0xBFC,RW,0x00000000);/* Cursor Image RAM Register on page 3-20); */
VAR(CrsrCtrl    ,0xC00      ,RW,0x00      );/* Cursor Control Register on page 3-20); */
VAR(CrsrConfig  ,0xC04      ,RW,0x0       );/* Cursor Configuration Register on page 3-21); */
VAR(CrsrPalette0,0xC08      ,RW,0x000000  );/* Cursor Palette Registers on page 3-22); */
VAR(CrsrPalette1,0xC0C      ,RW,0x000000  );/* Cursor Palette Registers on page 3-22); */
VAR(CrsrXY      ,0xC10      ,RW,0x00000000);/* Cursor XY Position Register on page 3-23); */
VAR(CrsrClip    ,0xC14      ,RW,0x0000    );/* Cursor Clip Position Register on page 3-24); */
ARR(RES3        ,0xC18,0xC1C,RO,- -       );/* Reserved); */
VAR(CrsrIMSC    ,0xC20      ,RW,0x0       );/* Cursor Interrupt Mask Set/Clear Register on page 3-25); */
VAR(CrsrICR     ,0xC24      ,WO,0x0       );/* Cursor Interrupt Clear Register on page 3-25); */
VAR(CrsrRIS     ,0xC28      ,RO,0x0       );/* Cursor Raw Interrupt Status Register on page 3-26); */
VAR(CrsrMIS     ,0xC2C      ,RO,0x0       );/* Cursor Masked Interrupt Status Register on page 3-26); */
ARR(RES4        ,0xC30,0xEFC,RO,0         );/* Reserved); */
ARR(RES5        ,0xF00,0xF08,RO,0         );/* Chapter 4 Programmers Model for Test); */
ARR(RES6        ,0xF0C,0xFDC,RO,0         );/* Reserved); */
VAR(PeriphID0   ,0xFE0      ,RO,0x11      );/* Peripheral Identification Register 0 on page 3-28); */
VAR(PeriphID1   ,0xFE4      ,RO,0x11      );/* Peripheral Identification Register 1 on page 3-28); */
VAR(PeriphID2   ,0xFE8      ,RO,0x-4      );/* Peripheral Identification Register 2 on page 3-29); */
VAR(PeriphID3   ,0xFEC      ,RO,0x00      );/* Peripheral Identification Register 3 on page 3-30); */
VAR(PCellID0    ,0xFF0      ,RO,0x0D      );/* PrimeCell Identification Register 0 on page 3-31); */
VAR(PCellID1    ,0xFF4      ,RO,0xF0      );/* PrimeCell Identification Register 1 on page 3-31); */
VAR(PCellID2    ,0xFF8      ,RO,0x05      );/* PrimeCell Identification Register 2 on page 3-32); */
VAR(PCellID3    ,0xFFC      ,RO,0xB1      );/* PrimeCell Identification Register 3 on page 3-32); */
} CLCDC;

int main()
{
 SYS.OSC4=0x2cac;
 CLCDC.Timing0=0x1313A4C4,
 CLCDC.Timing1=0x0505F657,
 CLCDC.Timing2=0x071F1800;

 printf("PCellID3 = %p\n",&CLCDC.PCellID3);
 return 0;
}

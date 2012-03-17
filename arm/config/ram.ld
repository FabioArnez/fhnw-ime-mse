/*
  -------------------------
  ram.ld linker script
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/versatile_application_baseboard_arm926ej_s_ug.pdf
  -------------------------
*/
   
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
	      "elf32-littlearm")
OUTPUT_ARCH(arm)
  
SECTIONS
{
 /*--------------------------
   the periphery
 ----------------------------*/
 SYS    = 0x10000000;
 UART0  = 0x101f1000;
 
 CLCDC  = 0x10120000; /* Color LCD Controller */    

 TIMER0 = 0x101e2000; 
 TIMER1 = 0x101e2020; 
 TIMER2 = 0x101e3000; 
 TIMER3 = 0x101e3020;

 . = 0 ;                      /* start of memory */
 .text :
   /* ^----------------- this space is relevant */
 {
  *(.boot)                     /* must be first */
  *(.exception_table)
  *(.text)
  *(.rodata)
  *(.glue*)
 }

 .data ALIGN (4):
 {
  *(.data)
 }

  bss_start= . ;
 .bss ALIGN (4) : 
 {
  *(.bss)
 }
  bss_end= . ;
 .stack ALIGN (4) :
 { 
  *(.stack)
 }
}

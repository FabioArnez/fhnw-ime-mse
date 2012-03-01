/*
  -------------------------
  ram.ld linker script
  (c) H.Buchmann FHNW 2011
  $Id$
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
 UART0  = 0x10009000;
 CLCDC  = 0x10020000; /* Color LCD Controller */    
 TIMER0 = 0x10011000; 
 TIMER1 = 0x10011020; 
 TIMER2 = 0x10012000; 
 TIMER3 = 0x10012020;
  
 . = 0;                      /* start of memory */
 .text :
   /* ^----------------- this space is relevant */
 {
  *(.boot)                     /* must be first */
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

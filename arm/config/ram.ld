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
 MEGA = (1<<20);
 /*--------------------------
   the memory
 ----------------------------*/
 MEM_BEG  = 0xc0000000;
 MEM_SIZE = 64*MEGA;
 
 /*--------------------------
   the periphery for realview
 ----------------------------*/
 SYS    = 0x10000000;
 UART0  = 0x101f1000;
 
 CLCDC  = 0x10120000; /* Color LCD Controller */    

 TIMER0 = 0x101e2000; 
 TIMER1 = 0x101e2020; 
 TIMER2 = 0x101e3000; 
 TIMER3 = 0x101e3020;

 /*------------------------------ start of virtual memory */
 . = MEM_BEG + 0x10000 ;             /* start of memory */
 .text :
   /* ^----------------- this space is relevant */
 {
  *(.boot)                     /* must be first */
  *(.exception_table)
  *(.text)
  *(.rodata)
  *(.glue*)
 }
 
 .data ALIGN (4) :
 {
  *(.data)
 }

 .ttb ALIGN (0x4000) :
 {
  *(.ttb)
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

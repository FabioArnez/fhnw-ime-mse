/*
  -------------------------
  ram.ld linker script
  (c) H.Buchmann FHNW 2011
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
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

 GIC1_IFC = 0x10040000;  /* see [1] 4.12 */
 GIC2_IFC = 0x10050000;
 GIC3_IFC = 0x10060000;
 GIC4_IFC = 0x10070000;
 GIC1_DIS = GIC1_IFC + 0x1000; 
 GIC2_DIS = GIC2_IFC + 0x1000; 
 GIC3_DIS = GIC3_IFC + 0x1000;
 GIC4_DIS = GIC4_IFC + 0x1000;
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

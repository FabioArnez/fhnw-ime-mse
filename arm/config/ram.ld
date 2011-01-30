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

  bss_start=.;
 .bss ALIGN (4) : 
 {
  *(.bss)
 }
  bss_end=.;

 .stack ALIGN (4) :
 { 
  *(.stack)
 }
}

/*---------------------
linker script for boot.iso
(c) H.Buchmann FHNW 2010
$Id$
---------------------*/
/* OUTPUT_FORMAT(binary)  dont works on cygwin obj files PE format */

SECTIONS
{
 . = (1<<20); 
 .text :
 {
  *(.big_bang)
  *(.text) 
  *(.rodata*)                /* dont forget this */
 } = 0x90                  /* fill gap with nops */
 . = ALIGN(8);   
 .data :
 {
  *(.data)
 }
 . = ALIGN(8);   
 load_end_addr = .;            /* see sys/start.c */
_load_end_addr = .;
 .bss :
 {
  *(.bss)
 }
 bss_end_addr = .;             /* see sys/start.c */
_bss_end_addr = .;
 . = ALIGN(0x100);
stack = . + (1<<20);
}

/*---------------------
linker script
(c) H.Buchmann FHNW 2006
$Id$
see multiboot specs:
http://www.gnu.org/software/grub/manual/multiboot/html_node/index.html
---------------------*/

/* OUTPUT_FORMAT(binary)  dont works on cygwin obj files PE format */
MAGIC = 0x1BADB002;
FLAGS = (1<<16);

SECTIONS
{
 . = (1<<20);  /* 1MByte */
 .text :
 {
/*----------------------------*/
 header_addr = .;
_load_addr   = .; 
/*----------------------------*/
                         /* the multiboot header */
  LONG(MAGIC)                           /* magic */
  LONG(FLAGS)	                        /* flags */
  LONG( - ( MAGIC + FLAGS ) )        /* checksum */
  LONG(header_addr)	
  LONG(_load_addr)
  LONG(_load_end_addr)
  LONG(_bss_end_addr)
  LONG(entry_addr)
entry_addr = .;
  BYTE(0xbc)                   /* mov stack %esp */ 
  LONG(stack)
  *(.start)                   /* see sys/start.c */
  *(.text) 
  *(.rodata*)                /* dont forget this */
 } = 0x90                  /* fill gap with nops */
 .data :
 {
  *(.data)
 }
 load_end_addr = .;
_load_end_addr = .;
 .bss :
 {
  *(.bss)
 }
 bss_end_addr = .;
_bss_end_addr = .;
stack = . + 0x10000;
}

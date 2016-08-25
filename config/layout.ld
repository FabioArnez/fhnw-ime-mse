/*
---------------------------
layout no memory map
(c) H.Buchmann FHNW 2016
---------------------------
*/

SECTIONS
{
/*---------------------------------------- text */ 
 .text 0x4000 : { /*<-------------------- for bootloader */
 	  *(.boot) /* must be first */
	  *(.glue_7)
	  *(.glue_7t)
          *(.text.startup .text .text.*)
	  *(.rodata)
	  *(.rodata.*)
	  *(.module)
	  *(.gnu.linkonce.*)
 . = ALIGN(4);
__GLOBAL__CONSTRUCTORS = .;
__GLOBAL__CONSTRUCTORS_BEG = . ;
          *(.init_array)
__GLOBAL__CONSTRUCTORS_END = . ;
	  LONG(0)    /* terminates global constructor list */
__GLOBAL__DESTRUCTORS = .;
__GLOBAL__DESTRUCTORS_BEG = . ;
	  *(.fini_array)
__GLOBAL__DESTRUCTORS_END = . ;
	  LONG(0)    /* terminates global constructor list */

 . = ALIGN(4);
 
__BUILD_ID = . ;
	*(.note.gnu.build-id)

_text_end = .;
	     }
 .ARM.extab :
 {
 	*(.ARM.extab*)
 }
 .ARM.exidx :
 {
 __exidx_start = . ;
	  *(.ARM.exidx*)
 __exidx_end = . ;
 }

/*---------------------------------------- data */ 
 .data 0x20000000: AT(ADDR(.text)+SIZEOF(.text)+SIZEOF(.ARM.exidx)+SIZEOF(.ARM.extab))
 {
_data_beg = .;
          *(.data)
. = ALIGN(4);
_data_end   = .;
 }




/*---------------------------------------- bss */ 
 .bss : {
. = ALIGN(4);
_bss_beg = .; 
          *(.bss)
	  *(.bss.*)
. = ALIGN(4);
_bss_end   = .;
 	}

STACK_TOP=0x20008000;

/DISCARD/ : {
  *(.v4_bx)
  *(.vfp11_veneer)
}

StackTop                    = 0x20008000;
_ZN3sys7ARMv6_M8StackTopE   =0x20008000;
_ZN3sys3reg4PORT1AE         = 0x41004400;
_ZN3sys3reg4PORT1BE         = 0x41004480;
_ZN3sys3reg7SYSCTRLE        = 0x40000800;
_ZN3sys3reg4GCLKE           = 0x40000c00;
_ZN3sys3reg5GCLK0E          = 0x40000c00;
_ZN3sys3reg7NVMCTRLE        = 0x41004000;
_ZN3sys3reg2PME             = 0x40000400;
_ZN3sys3reg3SER4COM0E       = 0x42000800;
_ZN3sys3reg3SER4COM1E       = 0x42000C00;
_ZN3sys3reg3SER4COM2E       = 0x42001000;
_ZN3sys3reg3SER4COM3E       = 0x42001400;
_ZN3sys3reg3SER4COM4E       = 0x42001800;
_ZN3sys3reg3SER4COM5E       = 0x42001c00; 
_ZN3sys3reg3SCSE            = 0xe000e000;
_ZN3sys7ARMv6_M4VTORE       = 0xe000ed08;
_ZN3sys3reg4SYSTE           = 0xe000e010;

_ZN3sys7ARMv6_M5NVIC_E      = 0xe000e100;

_ZN3sys3reg2TC3TC3E         = 0x42002C00;
_ZN3sys3reg4TC163TC3E       = 0x42002C00;
_ZN3sys3reg4TC163TC4E       = 0x42003000;
_ZN3sys3reg4TC163TC5E       = 0x42003400;
_ZN3sys3reg4TC163TC6E       = 0x42003800;
_ZN3sys3reg4TC163TC7E       = 0x42003C00;

_ZN3sys3reg3TC3E            = 0x42002C00;
_ZN3sys3reg3TC4E            = 0x42003000;
_ZN3sys3reg3TC5E            = 0x42003400;
_ZN3sys3reg3TC6E            = 0x42003800;
_ZN3sys3reg3TC7E            = 0x42003C00;
_ZN3sys3reg3SCBE            = 0xe000ed00;
_ZN3sys3reg3ADCE            = 0x42004000;

 _ZN3sys3reg4DMACE          = 0x41004800; 

_ZN3sys3reg5EVSYSE          = 0x42000400;
_ZN3sys3reg3RTCE            = 0x40001400;
_ZN3sys3reg3DACE            = 0x42004800;
_ZN3sys3NVM5CalibE          = 0x00806020;
_ZN3sys3NVM7UserRowE        = 0x00804000;
_ZN3sys3NVM4CTRLE           = 0x41004000;
_ZN3sys3reg3WDTE            = 0x40001000;
_ZN3sys3NVM13SerialNumber0E = 0x0080a00c;
_ZN3sys3NVM12SerialNumberE  = 0x0080a040;

_ZN3App3rowE = (128<<10);

}


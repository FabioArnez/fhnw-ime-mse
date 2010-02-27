/*----------------
 big-bang a
 (c) H.Buchmann FHNW 2010
 $Id$
 literature:
 [1] Intel 64 and IA-32 Architectures
     Software Developer's Manual
     Volume 3A:
 [2] http://www.ctyme.com/ 
 ----------------*/
#define SCREEN 0xb8000 
#define SCREEN_DIM (25*80)

#define ERR_CDROM_SPEC 0x1111
#define ERR_SECTOR     0x2222

#define ADR(val) (val-(1<<20)+0x7c00)

//#define DEBUG_16
#define DEBUG_32 

.section .big_bang
.code16
/*--------------------------------------------------- entry */
                                           /* 0x0000:0x7c00 */
big_bang:	
	cli                    /* clear interrupts for sure */
	jmp .start	                    /* relative jmp */ 
	. = big_bang+0x08
.bi_pvd:	.long 0
.bi_file:	.long 0
.bi_length:	.long 0
.bi_csum:	.long 0
	
	. = big_bang+0x40            /* space for mkisofs  */
.start:	xor %ax,%ax
	mov %ax,%ds                    /* zero data segment */
/*-------------------------------------------------- screen 
    es:di current pos
*/
	mov $(SCREEN>>4),%ax
	mov %ax,%es
	xor %di,%di

/*---------------------------------- write 'R' to the screen */
	mov $0x07,%ah	
	mov $'R',%al
	mov %ax,%es:(%di)
	add $2,%di

/*----------------------------------------- read .CDROM_SPEC */
	mov $0x4b01,%ax
	mov $0x80,  %dl
	mov $ADR(.CDROM_SPEC),%esi
	int $0x13
	jnc .copy
	mov $ERR_CDROM_SPEC,%ax   /* error */
	jmp hex

.copy:
/*------------------------------------ copy .bi_file to .DAP */
	mov $ADR(.bi_file),%esi
	mov (%esi),%eax
	mov $ADR(.DAP),%esi
	mov %eax,8(%esi)

.read_sector:
/*--------------------------------------------- read sector */
	mov $0x42,%ah
	mov $ADR(.CDROM_SPEC),%esi
	mov 2(%si),%dl
	mov $ADR(.DAP),%esi
	int $0x13
	jnc 0f
	mov $ERR_SECTOR,%ax
	jmp hex

/*-------------------------------------------- copy sector */
0:	mov $ADR(sector),%esi  /* src */
	mov $ADR(.dst),%edi   
	mov (%edi),%edi
	mov $0x800,%cx	       /* size of block */

1:	mov %ds:(%esi),%eax
	mov %eax,%ds:(%edi)

	add $4,%esi
	add $4,%edi
	sub $4,%cx
	jnz 1b

	mov $ADR(.dst),%esi
	mov %edi,(%esi)             /* save .dst */
	
        mov $ADR(.DAP),%esi
	add $1,8(%esi)               /* next LBA */

	mov $ADR(.bi_length),%esi
	mov (%esi),%eax
	sub $0x800,%eax      /* .bi_length-0x800 */
	mov %eax,(%esi)	              /* save it */	
	jg .read_sector	
	jmp .protected

	.align 4
.CDROM_SPEC:	 /*  [2] Int 13/AH=4Ah */
	.byte 0	 /* 0: size of packet in bytes 0x13*/
	.byte 0	 /* 1: boot media type */
	.byte 0	 /* 2: drive number */
	.byte 0	 /* 3: CD-ROM controller number */
 	.long 0	 /* 4: Logical Block Address of disk image to emulate */
	.word 0  /* 8: device specification */
	.fill 16 /* seems to be longer than written in [2] */

	.align 4
.DAP:	/* disk ddress packet */
	.byte 0x10         /*  0: size .DAP */
	.byte 0            /*  1: unused */
	.word 1            /*  2: number of sectors */
	.long ADR(sector)  /*  4: offset:segment */
	.long 0            /*  8: LBA  see .copy */
	.long 0	           /* 12:       */

.dst:	.long big_bang    
	

/*----------------------------------------- debug real mode */
#ifdef DEBUG_16
.code16
ip:	pop %ax                             /* where we are */
	push %ax
	ret

hex:   /* %ax value */
       /* never leaves */
	mov $2,%di
	mov %ax,%dx	                      /* save in dx */
	mov $16,%cx	                /* count: 4 nibbles */
0:	sub $4,%cx	                     /* next nibble */
	jc 3f		                       /*  all done */
	mov %dx,%ax	                        /*  restore */ 
	shr %cl,%ax
	and $0xf,%ax    /*  bits 0..3 digit value 0..9 a..f */
	cmp $10,%ax	                     /*  %ax-10 < 0 */
	jc 1f
	add $('a'-10),%ax                /*  digit 'a'..'f' */
	jmp 2f

1:	add $'0',%ax	

2:	mov $0x07,%ah                     /*  char out attr */
	mov %ax,%es:(%di)
	add $2,%di
	jmp 0b		                    /*  next nibble */
		
3:	jmp 3b	                            /* loop forever */
#endif

/*------------------------------------ debug protected mode */
#ifdef DEBUG_32
.code32
ip:	pop %eax                             /* where we are */
	push %eax
	ret


hex:   /* %ax value */
       /* never leaves */
	mov $SCREEN+2,%edi /* setup 32 bit screen for debug */
	mov %eax,%edx	                      /* save in dx */
	mov $32,%ecx	                /* count: 4 nibbles */
0:	sub $4,%ecx	                     /* next nibble */
	jc 3f		                       /*  all done */
	mov %edx,%eax	                        /*  restore */ 
	shr %cl,%eax
	and $0xf,%eax    /*  bits 0..3 digit value 0..9 a..f */
	cmp $10,%eax	                     /*  %ax-10 < 0 */
	jc 1f
	add $('a'-10),%eax                /*  digit 'a'..'f' */
	jmp 2f

1:	add $'0',%eax	

2:	mov $0x07,%ah                     /*  char out attr */
	mov %ax,(%edi)
	add $2,%edi
	jmp 0b		                    /*  next nibble */
		
3:	jmp 3b	                            /* loop forever */
#endif

/*------------------------------------ enter protected mode */
                                    /* [1] Fig 2.6 CR0 bits */
#define PE_BIT (1<<0)
#define CS 0x08
#define DS 0x10
.code16
.protected:
	cli	                                /* for sure */
	xorw	%ax, %ax
	movw	%ax, %ds
	DATA32 ADDR32 lgdt gdt
	movl %cr0, %eax	               /* set PE bit of CR0 */
	orl  $PE_BIT, %eax
	movl %eax, %cr0
	DATA32 ljmp $CS,$0f
.code32	 
0:	mov $DS,%ax                 /* we are in 32 bit mode */
	mov %ax,%ds
	mov %ax,%es
	mov %ax,%fs
	mov %ax,%gs
	mov %ax,%ss
		

/*---------------------------------- write 'P' to the screen */
	mov $SCREEN,%edi
	mov $0x7,%ah
	mov $'P',%al
	mov %ax,(%edi)
	
/*---------------------setup stack see iso.ld linker script */
	mov $stack,%esp
	call start 
	mov last,%eax
	jmp hex
	
/*--------------------------------- global descriptor table */
/* [1] Fig.4.1 */
/* flat memory */

#define CS_TYPE  (0x9a<<8)|(0xcf<<16) 
#define DS_TYPE  (0x92<<8)|(0xcf<<16)
	.align 8	/* GDT descriptors  8 byte boundary */
0:	.long 0,0                            /* nil segment */
	                           
	.long 0x0000ffff	         /* 8: code segment */
	.long CS_TYPE 

	.long 0x0000ffff	         /*10: data segment */
	.long DS_TYPE 

gdt:	.word 3*8-1
	.long 0b

/*--------------------------------------------------- data */
	.align 4
sector:	.fill 0x800

last:
	.word 0xabcd

#ifndef SYS_IO_H
#define SYS_IO_H
/*-------------------
 basic input/output
 (c) H.Buchmann FHNW 2009
 $Id$
---------------------*/
/*all inline volatile keyword important */
static inline unsigned char sys_inb(unsigned short port)
{
 unsigned char v;
 asm volatile(
  "#------------- inb\n\t"
//  "inb %w1"
  "inb %[port]"         /* works too */
  :[v] "=a" (v)
  :[port]"Nd" (port)
 );
 return v;
}

/* TODO robust programming 
        sys_outb(value,port) ok
	sys_outb(port,value) ok too but semantically wrong */
static inline void sys_outb(unsigned char v,
                            unsigned short port)
{
 asm volatile
 (
  "#------------- outb\n\t"
  "outb %w1"
  :
  :[v] "a" (v)
  ,[port]"Nd" (port)
 );
}
/*TODO inb/outb for unsigned short fastcall: parameter in ecx*/
typedef long long unsigned MSR;
__attribute__((fastcall)) static inline MSR sys_read_msr(unsigned id)
{
 asm volatile
 (
  "#------------------ sys_read_msr\n\t"
  "rdmsr\n"
  :   /* output */
  :[id]"c" (id)   /* input */
 );
}

static inline unsigned sys_getFlags()
{
 unsigned f;
 asm volatile
 (
  "#------------------getFlags\n\t"
  "pushf\n\t"
  "pop %[f]\n\t"
  :[f] "=a" (f)   /* output */
  :
 );
 return f;
}

static inline void sys_sti()
{
 asm volatile
 (
  "#------------------sti\n\t"
  "sti\n\t"
  : /* output */
  : /* input  */
 );
}

#endif

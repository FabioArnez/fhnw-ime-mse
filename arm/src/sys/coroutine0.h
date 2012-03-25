#pragma once
/*-----------------------
 coroutine0 
 (c) H.Buchmann FHNW 2012
 $Id$
-------------------------*/
#if __ASSEMBLER__ == 1
.global coroutine_transfer
#else

typedef struct 
{
  unsigned r[16];
} Register;

typedef union 
{
 unsigned* stack;
 Register* regs;
}Coroutine;

typedef struct
{
 unsigned r[16]; //the register list r0..r15
}Status;

#endif

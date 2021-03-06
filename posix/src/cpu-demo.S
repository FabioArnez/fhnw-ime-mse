/*--------------------
 cpu-demo-ops.S 
 (c) H.Bchmann FHNW 2010
 --------------------*/

/*assembler format:
  mnem src,dst  mnem: mnemonic 
                data flow left to right

  important instructions
  
  mov src,dst
  -----------
      reg->reg
       mov %reg,%reg

      reg->memory
       mov %reg,(%reg)

      memory->reg
       mov (%reg),&reg
 
  op src,dst
  ----------
  
     src=src op dst
    		
  calling conventions:
   see [1] System V Application Binary Interface
           AMD64 Architecture Processor Supplement
           abi.pdf
	   Figure 3.4: Register Usage
       [2] manual pags man syscall
   use 
     objdump -d file 
   for disassembly
*/

/*
unsigned op(unsigned x,unsigned y);
            arg1       arg2
eax         edi        esi

*/
.global _ZN3Ops2opEjj
_ZN3Ops2opEjj:
	mov %edi,%eax
	add %esi,%eax  //eax=eax+esi
	ret
   /* your work */

/*
TODO 
  - try other ops: 
    multiplication division 	
  - other return strategy
    void op(unsigned x,unsigned y,unsigned* res);
*/
/*
void copy(unsigned* dst,unsigned src)
          arg1          arg2
	  rdi           esi

              +--------+
rdi---------->|        |
              +--------+

esi=src        
*/
.global _ZN3Ops4copyEPjj
_ZN3Ops4copyEPjj:
	mov %esi,(%rdi)
	ret
/* your work */
        
/*
void swap(unsigned* x,unsigned* y)
          arg1          arg2
	  edi           esi

              +--------+
rdi---------->|        |
              +--------+

              +--------+
rsi---------->|        |  
              +--------+
*/

.global _ZN3Ops4swapEPjS0_

_ZN3Ops4swapEPjS0_: 
/* your work */
	ret

/*--------------------
 cpu-demo-ops.S 
 (c) H.Bchmann FHNW 2010
 --------------------*/

/*assembler format:
  mnem src,dst  mnem: mnemonic 
                data flow left to right
		
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
rax         edi        esi

*/
.global op
op:
        mov %edi,%eax
	add %esi,%eax 
	ret

/*
TODO 
  - try other ops: 
    multiplication division 	
  - other return strategy
    void op(unsigned x,unsigned y,unsigned* res);
*/

/*
void copy(unsigned* dst,unsigned* src)
          arg1          arg2
	  edi           esi

              +--------+
edi---------->|        |
              +--------+

              +--------+
esi---------->|        |  
              +--------+
*/
.global copy
copy:
	mov (%esi),%eax
	mov %eax, (%edi)
        ret
        
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

.global swap
swap:   mov (%esi),%eax
	mov (%edi),%edx
	mov %edx,(%esi)
	mov %eax,(%edi)
	ret

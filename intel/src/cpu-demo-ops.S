/*--------------------
 cpu-demo-ops.S 
 (c) H.Bchmann FHNW 2010
 $Id$
 --------------------*/

/*assembler format:
  mnem src,dst  mnem: mnemonic 
                data flow left to right
*/

/*
unsigned op(unsigned x,unsigned y);

----------------- stack  layout
addr
       |--------|
 esp+8 |       y|
       |--------|
 esp+4 |       x|
       |--------|
 esp   |     ret|
       |--------|
*/
.global op
op:
	movl 8(%esp),%eax       /* eax<- y      read     */
	mull 4(%esp)        /* edx:eax<- eax*x  read/add */
	ret

/*
TODO 
  - multiplication division 	
  - void op(unsigned x,unsigned y,unsigned* res);
*/

/*
void copy(unsigned* dst,unsigned* src)
----------------- stack layout

                           unsigned
                          +--------+
addr	             /--->|    val1|
       |--------|    |    +--------+
 esp+8 |     src|----/
       |--------|       
 esp+4 |     dst|----\     unsigned
       |--------|    |    +--------+ 
 esp   |     ret|    \--->|    val1|
       |--------|         +--------+ 
*/
.global copy
copy:
#if 0
        movl 8(%esp),%eax  /* read: value of src */
	movl 4(%esp),%ebx  /* read: value of dst */
	movl (%eax),(%ebx) /* error Error: too many memory references for `mov' */
#endif
        movl 8(%esp),%eax   /* read: value of src */
	movl (%eax), %ebx   /* ebx: val1
	movl (4%esp),%eax   /* read: value of dst */
	movl %ebx,(%eax)    /* write */
        ret
        

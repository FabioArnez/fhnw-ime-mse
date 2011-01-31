/*--------------------
 intel-assembler.S 
 (c) H.Bchmann FHNW 2010
 $Id$
 --------------------*/

/*assembler format:
  xxx src,dst
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
  multiplication division 	
  void op(unsigned x,unsigned y,unsigned* res);
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
        movl 8(%esp),%eax  /* read  */
        movl (%eax) ,%ebx  /* read  */
        movl 4(%esp),%eax  /* read  */
        mov %ebx,(%eax)    /* write */
        ret
        

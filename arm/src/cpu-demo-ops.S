/*----------------------
  cpu-demo-ops
  (c) H.Buchmann FHNW 2011
  $Id$
  see [ARMABI]
------------------------*/

/*assembler format:
  mnem dst,src  mnem: mnemonic 
                data flow right to left
  mnem z,x,y    z<-x mnem y		
*/

/*--------------------------------- 
  unsigned op(unsigned x,unsigned y)
  x:r0
  y:r1
  return r0<-r0 op r1
-----------------------------------*/  
.global op
op:	add r0,r0,r1
	mov pc,lr


/*--------------------------------- 
  void copy(unsigned* dst,unsigned* src)
  dst:r0  
  src:r1
  register r2 used as scratch

         unsigned 
	 +---------+
  r0---->|         |
         +---------+

         unsigned 
	 +---------+
  r1---->|         |
         +---------+
  	 
-----------------------------------*/  
.global copy
copy:	ldr r2,[r1]            /* r2<-[r1] */  
	str r2,[r0]            /*r2-> [r0] */
	mov pc,lr
 

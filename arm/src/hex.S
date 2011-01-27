//-----------------------
//hex print hex number
//(c) H.Buchmann FHNW 2011
//demonstrates  .addressing 
//              .numeric labels
//              .shifting
//              .conditional execution speciality of ARM 
//see UART 
//$Id$
//-----------------------
	ldr r0,.number
	bl hex

//reset
	ldr r1,CM_CTRL
	ldr r2,[r1]
	orr r2,r2,#(1<<3) //reset bit
	str r2,[r1]

.number: .word 0x89abcdef	
CM_CTRL: .word 0x1000000c //for resetting

//-------------------------------------------- hex
//r0 number to be printed
//PIC: position independent code
hex:	ldr r1,UART0 
	mov r2,#8 //nibble cnt
  0:	mov r0,r0,ROR #28
	and r3,r0,#0xf          //mask bits 0..3 0<=r1<16
	cmp r3,#10 
	addlt r3,r3,#'0'        //0<=r1<9
	addge r3,r3,#('a'-10)   //10<=r1<16 r1<-r1-10+'a'=r1+('a'-10)

  1:	ldr r4,[r1,#0x18]      //UARTFR
  	tst r4,#(1<<3)         //busy r4 and (1<<3)
	bne 1b		       //wait until busy clear	

	str r3,[r1]             //print it
	subs r2,r2,#1		//next nibble
	bne 0b
	mov pc,lr  

UART0:	.word 0x16000000

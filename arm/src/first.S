//--------------------------
//first
// testing and configuring qemu
// setting up the Makefile 
// see [IntegratorCM]
//(c) H.Buchmann FHNW 2011 
//$Id$
//--------------------------
//at reset
	ldr r0,CM_CTRL //addressing relative to pc
	ldr r1,[r0]
	orr r1,r1,#1<<0 //set bit 0 for LED on
	str r1,[r0]     //write to address
	orr r1,r1,#1<<3 //set bit 3 for resetting  
	mov r2,pc       
	str r1,[r0]     //do the reset 
	                //r2 pc at reset
	
CM_CTRL: .word 0x1000000c

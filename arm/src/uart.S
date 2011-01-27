//--------------------------
//uart
//test the communication
// see [IntegratorCM] [UART]
//(c) H.Buchmann FHNW 2011 
//demonstrates  .accessing hardware
//              .numeric labels 
//              .conditional execution speciality of ARM 
//$Id: first.S 232 2011-01-17 11:19:58Z hans.buchmann $
//--------------------------
	ldr r0,UART0
	mov r1,#'0'
0:	ldr r2,[r0,#0x18]  //UARTFR
	tst r2,#(1<<3)     //busy bit 
	streq r1,[r0]      //conditional
	b 0b
	
UART0:	.word 0x16000000

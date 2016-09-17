#pragma once
//-----------------------------
//cpu-demo-ops the public part
// implemented two times:
//  for posix
//  for arduino
//(c) H.Buchmann FHNW 2016
//-----------------------------
extern unsigned op(unsigned x,unsigned y); //an operation
extern void copy(unsigned*const dst,const unsigned*const src);
	//*dst=*src
extern void swap(unsigned*const x,unsigned*const y);
	//v=*y
	//*y=*x
	//*x=v

#pragma once
//----------------------------
//adc
//(c) H.Buchmann FHNW 2016
//----------------------------
INTERFACE(sys_reg_adc,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct ADC
  {
   enum Pin {A00= 0,A01= 1,A02= 2,A03= 3,A04= 4,A05= 5,A06= 6,A07= 7,A08= 8,A09= 9,
             A10=10,A11=11,A12=12,A13=13,A14=14,A15=15,A16=16,A17=17,A18=18,A19=19,
	    TEMP         =0x18,
	    BANDGAP      =0x19,
	    SCALEDCOREVCC=0x1a,
	    SCALEDIOVCC  =0x1b,
	    DAC          =0x1c};
  static void mux(Pin p);
	 unsigned char  CTRLA;      // 0x00 Control A
	 unsigned char  REFCTRL;    // 0x01 Reference Control
	 unsigned char  AVGCTRL;    // 0x02 Average Control
	 unsigned char  SAMPCTRL;   // 0x03 Sampling Time Control
	 unsigned short CTRLB;      // 0x04 Control B
	 unsigned short RES0;
	 unsigned       WINCTRL;    // 0x08 Window Monitor Control
	 unsigned       SWTRIG;     // 0x0C Software Trigger
	 unsigned       INPUTCTRL;  // 0x10 Input Control
	 unsigned short EVCTRL;     // 0x14 Event Control
	 unsigned char  INTENCLR;   // 0x16 Interrupt Enable Clear
	 unsigned char  INTENSET;   // 0x17 Interrupt Enable Set
	 unsigned char  INTFLAG;    // 0x18 Interrupt Flag Status and Clear
   const unsigned char  STATUS;     // 0x19 Status
   const unsigned short RESULT;     // 0x1A Result
	 unsigned       WINLT;      // 0x1C Window Monitor Lower Threshold
	 unsigned       WINUT;      // 0x20 Window Monitor Upper Threshold
	 unsigned short GAINCORR;   // 0x24 Gain Correction
	 unsigned short OFFSETCORR; // 0x26 Offset Correction
	 unsigned short CALIB;      // 0x28 Calibration
	 unsigned char  DBGCTRL;    // 0x2A Debug Control
   void regs() const volatile;
   static const char*const pinName(Pin p);
  } ADC;
 }
}



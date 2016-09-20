#pragma once
//-----------------------------
//dmac
//(c) H.Buchmann FHNW 2016
//-----------------------------
INTERFACE(sys_reg_dmac,$Id$)
namespace sys
{
 namespace reg
 {
  extern volatile struct DMAC
  {
   enum CHANNEL
   {
    CH00,CH01,CH02,CH03,CH04,CH05,CH06,CH07,CH08,CH09,CH10,CH11
   };
   
   enum SRC 
   {
    DISABLE    = 0x00, // Only software/event triggers
    SERCOM0_RX = 0x01, // SERCOM0 RX Trigger
    SERCOM0_TX = 0x02, // SERCOM0 TX Trigger
    SERCOM1_RX = 0x03, // SERCOM1 RX Trigger
    SERCOM1_TX = 0x04, // SERCOM1 TX Trigger
    SERCOM2_RX = 0x05, // SERCOM2 RX Trigger
    SERCOM2_TX = 0x06, // SERCOM2 TX Trigger
    SERCOM3_RX = 0x07, // SERCOM3 RX Trigger
    SERCOM3_TX = 0x08, // SERCOM3 TX Trigger
    SERCOM4_RX = 0x09, // SERCOM4 RX Trigger
    SERCOM4_TX = 0x0A, // SERCOM4 TX Trigger
    SERCOM5_RX = 0x0B, // SERCOM5 RX Trigger
    SERCOM5_TX = 0x0C, // SERCOM5 TX Trigger
    TCC0_OVF   = 0x0D, // TCC0 Overflow Trigger
    TCC0_MC0   = 0x0E, // TCC0 Match/Compare 0 Trigger
    TCC0_MC1   = 0x0F, // TCC0 Match/Compare 1 Trigger
    TCC0_MC2   = 0x10, // TCC0 Match/Compare 2 Trigger
    TCC0_MC3   = 0x11, // TCC0 Match/Compare 3 Trigger
    TCC1_OVF   = 0x12, // TCC1 Overflow Trigger
    TCC1_MC0   = 0x13, // TCC1 Match/Compare 0 Trigger
    TCC1_MC1   = 0x14, // TCC1 Match/Compare 1 Trigger
    TCC2_OVF   = 0x15, // TCC2 Overflow Trigger
    TCC2_MC0   = 0x16, // TCC2 Match/Compare 0 Trigger
    TCC2_MC1   = 0x17, // TCC2 Match/Compare 1 Trigger
    TC3_OVF    = 0x18, // TC3 Overflow Trigger
    TC3_MC0    = 0x19, // TC3 Match/Compare 0 Trigger
    TC3_MC1    = 0x1A, // TC3 Match/Compare 1 Trigger
    TC4_OVF    = 0x1B, // TC4 Overflow Trigger
    TC4_MC0    = 0x1C, // TC4 Match/Compare 0 Trigger
    TC4_MC1    = 0x1D, // TC4 Match/Compare 1 Trigger
    TC5_OVF    = 0x1E, // TC5 Overflow Trigger
    TC5_MC0    = 0x1F, // TC5 Match/Compare 0 Trigger
    TC5_MC1    = 0x20, // TC5 Match/Compare 1 Trigger
    TC6_OVF    = 0x21, // TC6 Overflow Trigger
    TC6_MC0    = 0x22, // TC6 Match/Compare 0 Trigger
    TC6_MC1    = 0x23, // TC6 Match/Compare 1 Trigger
    TC7_OVF    = 0x24, // TC7 Overflow Trigger
    TC7_MC0    = 0x25, // TC7 Match/Compare 0 Trigger
    TC7_MC1    = 0x26, // TC7 Match/Compare 1 Trigger
    ADC_RESRDY = 0x27, // ADC Result Ready Trigger
    DAC_EMPTY  = 0x28, // DAC Empty Trigger
    I2S_RX_0   = 0x29, // I2S RX 0 Trigger
    I2S_RX_1   = 0x2A, // I2S RX 1 Trigger
    I2S_TX_0   = 0x2B, // I2S TX 0 Trigger
    I2S_TX_1   = 0x2C, // I2S TX 1 Trigger
   };
   struct Transfer;
         unsigned short   CTRL;        // 0x00 Control
         unsigned short   CRCCTRL;     // 0x02 CRC Control
         unsigned         CRCDATAIN;   // 0x04 CRC Data Input
         unsigned         CRCCHKSUM;   // 0x08 CRC Checksum
         unsigned char    CRCSTATUS;   // 0x0C CRC Status
         unsigned char    DBGCTRL;     // 0x0D Debug Control
         unsigned         SWTRIGCTRL;  // 0x10 Software Trigger Control
         unsigned         PRICTRL0;    // 0x14 Priority Control 0
         unsigned         RES0[2];     // 0x18
         unsigned         INTPEND;     // 0x20 Interrupt Pending
   const unsigned         INTSTATUS;   // 0x24 Interrupt Status
   const unsigned         BUSYCH;      // 0x28 Busy Channels
   const unsigned         PENDCH;      // 0x2C Pending Channels
   const unsigned         ACTIVE;      // 0x30 Active Channel and Levels
volatile Transfer*        BASEADDR;    // 0x34 Descriptor Memory Section Base Address
volatile Transfer*        WRBADDR;     // 0x38 Write-Back Memory Section Base Address
         unsigned char    RES1[3];     // 0x3c
         unsigned char    CHID;        // 0x3F Channel ID
         unsigned         CHCTRLA;     // 0x40 Channel Control A
         unsigned         CHCTRLB;     // 0x44 Channel Control B
         unsigned         RES2;        // 0x48
         unsigned char    CHINTENCLR;  // 0x4C Channel Interrupt Enable Clear
         unsigned char    CHINTENSET;  // 0x4D Channel Interrupt Enable Set
         unsigned char    CHINTFLAG;   // 0x4E Channel Interrupt Flag Status and Clear
   const unsigned char    CHSTATUS;    // 0x4F Channel Status

   void regs() const volatile; 
   void regs(unsigned chid) volatile;
   struct alignas(16) Transfer
   {
    unsigned short BTCTRL;
    unsigned short BTCNT;
    volatile const unsigned char* SRC;
    volatile       unsigned char* DST;
    volatile Transfer*      next;
    void regs() const volatile;
   };
  } DMAC;
 }//namespace reg
}//namespace sys



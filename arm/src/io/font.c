/*------------------------------------
  font.c
  (c) H.Buchmann FHNW 2012
  $Id$
  generated with font/Font.java
--------------------------------------*/
#include "io/font.h"
#include <stdio.h>

/*
 pixel  0 1 2 3 4 5 
 bit    0 1 2 3 4 5 
*/
static const unsigned Data[]=
{
0x00000020,0x00000080,/* start end */ 
0x00000000,0x00000004,0x00000008,0x0000000c,
0x00000010,0x00000014,0x00000018,0x0000001c,
0x00000020,0x00000024,0x00000028,0x0000002c,
0x00000030,0x00000034,0x00000038,0x0000003c,
0x00000040,0x00000044,0x00000048,0x0000004c,
0x00000050,0x00000054,0x00000058,0x0000005c,
0x00000060,0x00000064,0x00000068,0x0000006c,
0x00000070,0x00000074,0x00000078,0x0000007c,
0x00000080,0x00000084,0x00000088,0x0000008c,
0x00000090,0x00000094,0x00000098,0x0000009c,
0x000000a0,0x000000a4,0x000000a8,0x000000ac,
0x000000b0,0x000000b4,0x000000b8,0x000000bc,
0x000000c0,0x000000c4,0x000000c8,0x000000cc,
0x000000d0,0x000000d4,0x000000d8,0x000000dc,
0x000000e0,0x000000e4,0x000000e8,0x000000ec,
0x000000f0,0x000000f4,0x000000f8,0x000000fc,
0x00000100,0x00000104,0x00000108,0x0000010c,
0x00000110,0x00000114,0x00000118,0x0000011c,
0x00000120,0x00000124,0x00000128,0x0000012c,
0x00000130,0x00000134,0x00000138,0x0000013c,
0x00000140,0x00000144,0x00000148,0x0000014c,
0x00000150,0x00000154,0x00000158,0x0000015c,
0x00000160,0x00000164,0x00000168,0x0000016c,
0x00000170,0x00000174,0x00000178,0x0000017c,
0x00000184,
/* pixel */
0x00000000,0x00000000,0x00000000,0x00000000,
0x00000000,0x10101010,0x00101010,0x00001010,
0x44440000,0x00004444,0x00000000,0x00000000,
0x00000000,0x7e484848,0x127e2424,0x00001212,
0x00000000,0x12927c10,0x9290701c,0x0000107c,
0x00000000,0x2c52528c,0x94681010,0x00006294,
0x00000000,0x44444438,0x42a29c38,0x00009c62,
0x10100000,0x00001010,0x00000000,0x00000000,
0x20000000,0x08081010,0x08080808,0x00201010,
0x04000000,0x10100808,0x10101010,0x00040808,
0x00000000,0x92100000,0x92543854,0x00000010,
0x00000000,0x10100000,0x1010fe10,0x00000010,
0x00000000,0x00000000,0x00000000,0x08101018,
0x00000000,0x00000000,0x00007e00,0x00000000,
0x00000000,0x00000000,0x00000000,0x00001818,
0x00000000,0x10204040,0x04080810,0x00000202,
0x00000000,0x42422418,0x42424242,0x00001824,
0x00000000,0x10141810,0x10101010,0x00007c10,
0x00000000,0x4042423c,0x02040830,0x00007e02,
0x00000000,0x4042423c,0x42404038,0x00003c42,
0x00000000,0x24283020,0x207e2222,0x00002020,
0x00000000,0x0202027e,0x4040403e,0x00003c42,
0x00000000,0x02020438,0x4242423e,0x00003c42,
0x00000000,0x2040407e,0x10102020,0x00001010,
0x00000000,0x4242423c,0x4242423c,0x00003c42,
0x00000000,0x4242423c,0x4040407c,0x00001c20,
0x00000000,0x18180000,0x18000000,0x00000018,
0x00000000,0x18180000,0x18000000,0x00081010,
0x00000000,0x10204000,0x10080408,0x00004020,
0x00000000,0x7e000000,0x7e000000,0x00000000,
0x00000000,0x08040200,0x08102010,0x00000204,
0x00000000,0x4042423c,0x00101020,0x00001010,
0x00000000,0x6a524438,0x724a4a4a,0x00007804,
0x00000000,0x42242418,0x42427e42,0x00004242,
0x00000000,0x4242423e,0x4242423e,0x00003e42,
0x00000000,0x0242423c,0x42020202,0x00003c42,
0x00000000,0x4242221e,0x42424242,0x00001e22,
0x00000000,0x0202027e,0x0202023e,0x00007e02,
0x00000000,0x0202027e,0x0202023e,0x00000202,
0x00000000,0x0242423c,0x42427202,0x00005c62,
0x00000000,0x42424242,0x4242427e,0x00004242,
0x00000000,0x1010107c,0x10101010,0x00007c10,
0x00000000,0x202020f8,0x22202020,0x00001c22,
0x00000000,0x0a122242,0x120a0606,0x00004222,
0x00000000,0x02020202,0x02020202,0x00007e02,
0x00000000,0x66664242,0x42425a5a,0x00004242,
0x00000000,0x4a464642,0x6252524a,0x00004262,
0x00000000,0x4242423c,0x42424242,0x00003c42,
0x00000000,0x4242423e,0x0202023e,0x00000202,
0x00000000,0x4242423c,0x5a424242,0x00c03c66,
0x00000000,0x4242423e,0x2222123e,0x00004242,
0x00000000,0x0242423c,0x4240300c,0x00003c42,
0x00000000,0x101010fe,0x10101010,0x00001010,
0x00000000,0x42424242,0x42424242,0x00003c42,
0x00000000,0x44828282,0x28284444,0x00001010,
0x00000000,0x42424242,0x66665a5a,0x00004242,
0x00000000,0x24244242,0x24241818,0x00004242,
0x00000000,0x44448282,0x10101028,0x00001010,
0x00000000,0x2040407e,0x02040810,0x00007e02,
0x70000000,0x10101010,0x10101010,0x00701010,
0x00000000,0x08040202,0x20101008,0x00004040,
0x0e000000,0x08080808,0x08080808,0x000e0808,
0x24180000,0x00000042,0x00000000,0x00000000,
0x00000000,0x00000000,0x00000000,0x00fe0000,
0x10080400,0x00000000,0x00000000,0x00000000,
0x00000000,0x423c0000,0x42427c40,0x00005c62,
0x02000000,0x463a0202,0x42424242,0x00003a46,
0x00000000,0x423c0000,0x02020202,0x00003c42,
0x40000000,0x625c4040,0x42424242,0x00005c62,
0x00000000,0x423c0000,0x02027e42,0x00003c42,
0x30000000,0x3e080808,0x08080808,0x00000808,
0x00000000,0x225c4000,0x041c2222,0x3c42423c,
0x02000000,0x463a0202,0x42424242,0x00004242,
0x10000000,0x10180010,0x10101010,0x00007c10,
0x20000000,0x20300020,0x20202020,0x0c122020,
0x00000000,0x12220202,0x120a060a,0x00004222,
0x00000000,0x10101018,0x10101010,0x00007c10,
0x00000000,0x926e0000,0x92929292,0x00009292,
0x00000000,0x463a0000,0x42424242,0x00004242,
0x00000000,0x423c0000,0x42424242,0x00003c42,
0x00000000,0x463a0000,0x42424242,0x02023a46,
0x00000000,0x625c0000,0x42424242,0x40405c62,
0x00000000,0x463a0000,0x02020242,0x00000202,
0x00000000,0x423c0000,0x40300c02,0x00003c42,
0x00000000,0x083e0808,0x08080808,0x00003008,
0x00000000,0x42420000,0x42424242,0x00005c62,
0x00000000,0x42420000,0x24242442,0x00001818,
0x00000000,0x92820000,0x92929292,0x00006c92,
0x00000000,0x42420000,0x24181824,0x00004242,
0x00000000,0x42420000,0x64424242,0x3c404058,
0x00000000,0x407e0000,0x04081020,0x00007e02,
0x30000000,0x10100808,0x10100808,0x00300808,
0x10100000,0x10101010,0x10101010,0x10101010,
0x0c000000,0x08081010,0x08081010,0x000c1010,
0x8c000000,0x00006292,0x00000000,0x00000000,
0x00000000,0x00000000,0x0bce0000,0x0bd20852,0x7bce0852,0x00000000,0x00000000,0x00000000
};

static struct 
{
 unsigned start;
 unsigned end;
 const unsigned* idx;
 const unsigned* pix;
} Font;

void font_init()
{
 static unsigned initialized=0;
 if (initialized) return;
 ++initialized;

 Font.start=Data[0];
 Font.end  =Data[1];
 Font.idx  =Data+2;
 Font.pix  =Data+2+Font.end-Font.start+1;
}

void font_glyph(char ch,Glyph* g) /* 0x20<=ch<0x80 */
{ /* TODO range control */
 unsigned i=ch-Data[0];
 unsigned idx=Font.idx[i];
 *g=(Glyph){2*(Font.idx[i+1]-idx), /* 32*(Font.idx[i+1]-idx)/16 */
            16,
            Font.pix+idx};
}

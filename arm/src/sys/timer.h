#pragma once
/*-------------------------
  timer
  (c) H.Buchmann FHNE 2012
  $Id$
  [1] literature/realview_emulation_basebord_ug.pdf
  [2] literature/sp-804-timer-DDI0271.pdf
---------------------------*/
typedef struct /* see [2] 3.1 */
{
       unsigned Load;
 const unsigned Value;
       unsigned Control;
       unsigned IntClr;
 const unsigned RIS;
 const unsigned MIS;
       unsigned BGLoad;
} Timer;

extern volatile Timer TIMER0;

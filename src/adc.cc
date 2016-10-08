//----------------------------
//adc.h the driver event driven
//(c) H.Buchmann FHNW 2016
//[1] Atmel | SMART  SAM D21J, SAM D21G, SAM D21E, 
//    ARM Cortex-M0+ based Embedded Flash Microcontroller
//    Atmel-42181-SAM-D21_Datasheet.pdf
//----------------------------
IMPLEMENTATION(adc,$Id$)
#include "adc.h"
#include "sys/reg/pm.h"
#include "sys/reg/port.h"
#include "sys/reg/gclk.h"
#include "sys/soc.h"

ADC ADC::adc;  //call constructor

ADC::ADC()
{
//see adc-demo.cc
//enable interrupt on ADC
//enable interrupt on SOC
}



#pragma once
//-------------------------
//samples.h
//(c) H.Buchmann FHNW 2015
//-------------------------
#include <cmath>
namespace sound
{
//----------------------------------------------------------
// a Player plays samples
 class Player                         //superclass of the Player 
 {
  public:
   Player(unsigned fs);               //fs sampling frequency
   const unsigned fs;
   virtual void sample(double v)=0; //-1<=v<=v 
 };


//----------------------------------------------------------
//creates samples for a Player
 class Generator
 {
  public:
   Generator(Player& p);
  protected:
   Player& p;
   const double dt;  
 };

}//namespace sound

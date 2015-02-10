#pragma once
//-------------------------
//samples.h
//(c) H.Buchmann FHNW 2015
//-------------------------
#include <cmath>
#include <iostream>
namespace sound
{
 class Player
 {
  public:
   Player(unsigned fs);               //fs sampling frequency
   const unsigned fs;
   virtual void sample(double v)=0; //-1<=v<=v 
 };

 class Stream:public Player  
 {
  public:
   Stream(unsigned fs,std::ostream& out);
   void sample(double v);

  private:
   typedef short int Sample;  
   std::ostream& out;
 };

 class Generator
 {
  public:
   Generator(Player& p);
  protected:
   Player& p;
   const double dt;  
 };

 class Sine:Generator //a very simple Player
 {
  public:
   Sine(Player&,double f_Hz,double dur_Sec);
  private:
   static constexpr double PI=4*std::atan(1.0);
 };

 class Noise:Generator
 {
  public:
   Noise(Player&,double dur_Sec);
 };
}//namespace sound

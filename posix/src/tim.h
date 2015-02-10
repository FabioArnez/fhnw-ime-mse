#pragma once
//----------------------------
//time
//(c) H.Buchmann FHNW 2015
//----------------------------
#include <time.h>
class Time
{
 public:
   Time();
  ~Time();
 private:
  timespec cpu;
  timespec tim;
  static double diff(const timespec& from,const timespec& to);
};

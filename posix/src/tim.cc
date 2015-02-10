//----------------------------
//time
//(c) H.Buchmann FHNW 2015
//----------------------------
#include "tim.h"
#include <iostream>

//uncomment for test
//#define TIM_TEST

Time::Time()
{
 clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&cpu);
 clock_gettime(CLOCK_MONOTONIC,         &tim);
}

Time::~Time()
{
 timespec cpu1;
 timespec tim1;
 clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&cpu1);
 clock_gettime(CLOCK_MONOTONIC,         &tim1);
 std::cerr<<"cpu="<<diff(cpu,cpu1)<<"\n"
            "tim="<<diff(tim,tim1)<<"\n";
}


double Time::diff(const timespec& from,const timespec& to)
{
 static const long TONANO=1000000000lu;
 
 return ((double)((to.tv_sec -from.tv_sec)*TONANO+
                  (to.tv_nsec-from.tv_nsec)))/TONANO;
}

#ifdef TIM_TEST
int main(int argc,char** args)
{
 Time t0;
 char ch;
 std::cin>>ch;
 return 0;
}
#endif

#pragma once
//------------------------
//fifo as template
//(c) H.Buchmann FHNW 2015
//------------------------
INTERFACE(util_fifo,$Id$)
namespace util
{
 template<typename T,unsigned N>
 class Fifo
 {
  public:
   void put(T v)
   {
    pool[putI++]=v;
    if (putI==N) putI=0;
    if (size<N) ++size;
   }

   T get()
   {
    if (size==0) return 0; //type T should have a zero
    T v=pool[getI++];
    if (putI==N) putI=0;
    --size;
    return v;
   }
   bool empty(){return size==0;}
   bool full(){return size==N;}
  private:
   T pool[N];
   unsigned putI=0;
   unsigned getI=0;
   unsigned size=0;
 };
}

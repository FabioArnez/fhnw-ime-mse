#pragma once
//----------------------------
//board
//(c) H.Buchmann FHNW 2016
//----------------------------
INTERFACE(sys_board,$Id$)
namespace sys
{
 class Board
 {
  public:
  private:
   [[noreturn]] static void  bigBang();
   static void clock();
   static void data(); //copy data from flash into RAM
 };
}

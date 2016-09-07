//---------------------
// samples.cc
// (c) H.Buchmann FHNW 2015
//--------------------- 
#include "samples.h"
namespace sound
{
 Player::Player(unsigned  fs)
 :fs(fs) //init list
 {
 }

 Generator::Generator(Player& p)
 :p(p)
 ,dt(1.0/p.fs)
 //  |---------------.0 essential because fs unsigned 
 {
 }

}//namespace sound

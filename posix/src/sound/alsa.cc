//-----------------------
//alsa
//(c) H.Buchmann FHNW 2015
//-----------------------
/* 
 
*/
#include "alsa.h"
#include <iostream>
namespace sound
{
 Alsa::Alsa(unsigned fs,unsigned bufferSize)
 :Player(fs)
 ,bS(bufferSize)
 ,buffer(new Sample[bS])
 {
  static const unsigned LATENCY=10;//250000;//TODO try other values 
  snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
  snd_pcm_set_params(pcm,
	             SND_PCM_FORMAT_S16_LE,
		     SND_PCM_ACCESS_RW_INTERLEAVED,
	             1,
	             fs,
	             0,
		     LATENCY); //latency
 }

 Alsa::~Alsa()
 {
  std::cerr<<"~Alsa\n";
  play(); //the rest of the buffer
  snd_pcm_close(pcm);
  delete [] buffer;
 }

 void Alsa::sample(double v)
 {
  buffer[sI++]=(Sample)(0x7fff*v); //scale
  if (sI==bS) play();
 }

 void Alsa::play()
 {
//  snd_pcm_state_t state=snd_pcm_state(pcm);
//  std::cerr<<state<<"\n";
  snd_pcm_sframes_t f=snd_pcm_writei(pcm,buffer,sI);
  while(f<0)
  {
   f=snd_pcm_recover(pcm,f,1);
  }
#if 0
  if (f<0)
     {
      std::cerr<<"err="<<snd_strerror(f)<<"\n";
     }
     else
     {
      std::cerr<<"f="<<f<<"\n";
     }
#endif
  sI=0;
 }
}

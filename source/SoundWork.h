// Original Author: Sean Long @ Hailstone Software
// Contact: 		sean@hailstonesoftware.com
// Last Modified:   02/14/2000
#ifndef SOUNDWORK_H
#define SOUNDWORK_H

#include <Sound.h>
#include <string.h>
#include <SoundPlayer.h>
#include <Path.h>
#include <Entry.h>
#include <MediaDefs.h>


bool playsound(char *path,float VolumeLevel);
void RemovePuncFromWord(char *string,int length);
void ProcessNum(char *totalpath,long num,int length,float VolumeLevel);

#endif
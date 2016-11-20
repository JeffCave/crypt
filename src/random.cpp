#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "enigma.h"

//const unsigned char Random::NODUP = 0;
//const unsigned char Random::DUP = 1;
bool Random::randomized = false;

Random::Random()
{
	if(!randomized){
		srand(time(NULL));
		randomized = true;
	}
}

/*** ch *************************************************************/
void Random::ch(unsigned char *list, unsigned char rep, unsigned long size)
{
	unsigned int i,r;
	unsigned char temp;

	if(rep==NODUP){
		for(i=0; i<size; i++){
			list[i] = (unsigned char)i;
		}
			for(i=size-1; i>0; i--){
			r=random()%i;
			temp=list[i];
			list[i]=list[r];
			list[r]=temp;
		}
	}
	else{
		for(i=0; i<size; i++){
			list[i]=(unsigned char)random()%Wheel::WHEELSIZE;
		}
	}
}
/*** ch *************************************************************/

/****
	Class: wheel
****/

#include <stdlib.h>
#include <string.h>

#include "enigma.h"

const int Wheel::WHEELSIZE = 256;


Wheel::Wheel()
{
	list.resize(WHEELSIZE);
}

Wheel::~Wheel()
{
}


/**
 * 
 */
void Wheel::GenWheel()
{
	Random rand;
	rand.ch(&list[0],rand.NODUP,WHEELSIZE);
	timesused = 0;
}


/**
 * 
 */
void Wheel::setWheel(vector<byte> newwheel)
{
	list = newwheel;
	timesused = 0;
	
	listOut.resize(list.size());
	for(auto i=0; i<list.size(); i++){
		listOut[list[i]] = i;
	}
}


/**
 * 
 */
void Wheel::getWheel(byte* outwheel)
{
	memcpy(outwheel,&list[0],WHEELSIZE);
}


/**
 * 
 */
byte Wheel::goingIn(byte val)
{
	return(list[val]);
}


/**
 * 
 */
byte Wheel::goingOut(byte val)
{
	return listOut[val];
}


/**
 * 
 */
int Wheel::Turn()
{
	// store first value in array
	byte temp = list[0];
	// bubble everything one space down
	for(int i=0; i<WHEELSIZE-1 ;i++){
		list[i] = list[i+1];
	}
	//put the stored value at the end
	list[WHEELSIZE-1] = temp;
	
	// once recalculate the reverse
	listOut.resize(list.size());
	for(auto i=0; i<list.size(); i++){
		listOut[list[i]] = (byte)i;
	}
	
	// whether wheel has been through one revolution
	++timesused %= WHEELSIZE;
	return(timesused==0);
}


/**
 * 
 */
void Wheel::SetStart(int pos)
{
	startpos=list[pos];
	while(list[0]!=startpos){
		Turn();
	}
	timesused=0;
}


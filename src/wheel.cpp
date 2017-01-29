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
unsigned char Wheel::goingIn(byte val)
{
	return(list[val]);
}


/**
 * 
 */
unsigned char Wheel::goingOut(byte val)
{
	int i;
	for(i=0; list[i]!=val; i++);
	return((unsigned char) i);
}


/*** Turn ***********************************************************/
int Wheel::Turn()
{
	byte temp;  //temp holding space for first value in array
	int i;      //index for array

	//store first value in array
	temp = list[0];
	//bubble everything one space down
	for(i=0; i<WHEELSIZE-1 ;i++){
		list[i] = list[i+1];
	}
	//put the stored value at the end
	list[WHEELSIZE-1] = temp;
	//adjust counter to reflect the new position
	timesused ++;
	//adjust for WHEELSIZE
	timesused = (timesused>=WHEELSIZE)?0:timesused;
	//whether wheel has been through one revolution
	return(timesused==0);
}
/*** Turn ***********************************************************/

/*** StartPos *******************************************************/
void Wheel::SetStart(int pos)
{
	startpos=list[pos];
	while(list[0]!=startpos){
		Turn();
	}
	timesused=0;
}
/*** StartPos *******************************************************/

/****
	Class: wheel
****/

#include "enigma.h"
#include <stdlib.h>
#include <mem.h>

const int Wheel::WHEELSIZE = 256;

/*** Constructor ****************************************************/
Wheel::Wheel()
{
	list = new unsigned char[WHEELSIZE];
}
/*** Constructor ****************************************************/

/*** GenWheel *******************************************************/
void Wheel::GenWheel()
{
	Random rand;
	rand.ch(list,rand.NODUP,WHEELSIZE);
	timesused=0;
}
/*** GenWheel *******************************************************/

/*** LoadWheel ******************************************************/
void Wheel::LoadWheel(unsigned char newwheel[])
{
	//validate that array is valid wheel
	//move new wheel values in
	memcpy(list, newwheel, WHEELSIZE);
	timesused = 0;
}
/*** LoadWheel ******************************************************/

/*** GetWheel *******************************************************/
void Wheel::GetWheel(unsigned char *outwheel)
{
	memcpy(outwheel,list,WHEELSIZE);
}
/*** GetWheel *******************************************************/

/*** goingIn ********************************************************/
unsigned char Wheel::goingIn(unsigned char val)
{
	return(list[val]);
}
/*** goingIn ********************************************************/

/*** goingOut *******************************************************/
unsigned char Wheel::goingOut(unsigned char val)
{
   int i;
   for(i=0; list[i]!=val; i++);
   return((unsigned char) i);
}
/*** goingOut *******************************************************/

/*** Turn ***********************************************************/
int Wheel::Turn()
{
   unsigned char temp;  //temp holding space for first value in array
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

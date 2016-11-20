/***
	Class: WheelSet
***/

#include "enigma.h"
#include <stdio.h>
#include <stdlib.h>

const int WheelSet::TOTWHEELS = 128;

/*** WheelSet *******************************************************/
WheelSet::WheelSet()
{
	wheels = new Wheel[TOTWHEELS];
	wheelorder = new unsigned char[TOTWHEELS];
	backboard = new Wheel;
}
WheelSet::~WheelSet()
{
	delete wheels;
}
/*** WheelSet *******************************************************/

/*** LoadWheels *****************************************************/
void WheelSet::LoadWheels(unsigned char *path)
{
	unsigned char temp[256];
	FILE *file;
	file = fopen(path,"rb");
	if(file==NULL){
		printf("ERROR: file '%s' could not be opened.",path);
		exit(1);
	}
	for(int i=0; i<TOTWHEELS; i++){
		fread(temp, Wheel::WHEELSIZE, 1, file);
		wheels[i].LoadWheel(temp);
		printf("\rWheel %i of %i imported (%f)",i+1,TOTWHEELS,1.0*i/TOTWHEELS);
	}
	fread(temp, Wheel::WHEELSIZE, 1, file);
	backboard->LoadWheel(temp);
	fclose(file);
}
/*** LoadWheels *****************************************************/

/*** LoadKey ********************************************************/
void WheelSet::LoadKey(unsigned char *path)
{
	FILE *src;
	unsigned char* key = new char[TOTWHEELS];
	int i;
	Random rand;
	
	src = fopen(path,"rb");
	fread(key,TOTWHEELS,1,src);
	printf("\nSetting Wheel Order...\n");
	fread(wheelorder,TOTWHEELS,1,src);
	fclose(src);
	for(i=0; i<TOTWHEELS; i++){
		wheels[i].SetStart(key[i]);
      printf("\rWheel %i of %i initialized (%.2f)...",i,TOTWHEELS,100.0*i/TOTWHEELS);
	}
}
/*** LoadKey ********************************************************/

/*** GenWheels ******************************************************/
void WheelSet::GenWheels(unsigned char *path)
{
	unsigned char temp[256];
	int i;
	Wheel buildwheel;
	FILE *file;
	file = fopen(path,"wb");
	printf("\n");
	for(i=0; i<TOTWHEELS; i++){
		printf("\rGenerating Wheel %i of %i (%.2f)",i,TOTWHEELS,100.0*i/TOTWHEELS);
		buildwheel.GenWheel();
		buildwheel.GetWheel(temp);
		fwrite(temp, Wheel::WHEELSIZE, 1, file);
	}
	printf("\r%.2f",100.0*i/TOTWHEELS);
	backboard->GenWheel();
	backboard->GetWheel(temp);
	fwrite(temp, Wheel::WHEELSIZE, 1, file);
	fclose(file);
}
/*** GenWheels ******************************************************/

/*** GenKey *********************************************************/
void WheelSet::GenKey(unsigned char *path)
{
	FILE *dest;
	unsigned char key[256];
	Random rand;

	printf("Generating key...");
	rand.ch(key,rand.DUP,TOTWHEELS);
	rand.ch(wheelorder,rand.NODUP,TOTWHEELS);
	printf("Writing key to file...");
	dest = fopen(path,"wb");
	fwrite(key,TOTWHEELS,1,dest);
	fwrite(wheelorder,TOTWHEELS,1,dest);
	fclose(dest);
	printf("Key Written.");
}
/*** GenKey *********************************************************/

/*** crypt **********************************************************/
unsigned char WheelSet::Crypt(unsigned char value,int decrypt)
{
	int i;	//index counter

	//sends value in through the wheels
	for(i=0; i<TOTWHEELS; i++){
		value = wheels[wheelorder[i]].goingIn(value);
	}
	//bounces it off the backboard
	if(decrypt){
		value = backboard->goingOut(value);
	}
	else{
		value = backboard->goingIn(value);
	}
	//brings the value back through the wheels
	for(i=TOTWHEELS-1; i>=0; i--){
		value=wheels[wheelorder[i]].goingOut(value);
	}
	//turns all the wheels that need turning
	int turnnext=true;
	for(i=TOTWHEELS-1; i>=0 && turnnext; i--){
		turnnext=wheels[wheelorder[i]].Turn();
	}
	//sends back the new value
	return(value);
}
/*** crypt **********************************************************/


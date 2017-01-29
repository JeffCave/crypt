/***
	Class: WheelSet
***/

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "enigma.h"

const int WheelSet::TOTWHEELS = 128;

WheelSet::WheelSet()
{
	wheels = new Wheel[TOTWHEELS];
	wheelorder = new unsigned char[TOTWHEELS];
	backboard = new Wheel;
}
WheelSet::~WheelSet()
{
	delete wheels;
	delete wheelorder;
	delete backboard;
}

/*** LoadWheels *****************************************************/
void WheelSet::LoadWheels(string& path)
{
	vector<byte> temp;
	temp.resize(256);
	temp.reserve(256);


	std::ifstream file(path.c_str(), std::ifstream::binary);
	if(!file){
		printf("ERROR: file '%s' could not be opened.",path.c_str());
		exit(1);
	}
	for(int i=0; i<TOTWHEELS; i++){
		file.read((char *)&temp[0], Wheel::WHEELSIZE);
		wheels[i].setWheel(temp);
		printf("\rWheel %i of %i imported (%f)",i+1,TOTWHEELS,1.0*i/TOTWHEELS);
	}
	
	file.read((char *)&temp[0], Wheel::WHEELSIZE);
	backboard->setWheel(temp);
	
	file.close();

}


/**
 * 
 */
void WheelSet::LoadKey(string& path)
{
	unsigned char* key = new unsigned char[TOTWHEELS];
	int i;
	Random rand;

	ifstream src(path.c_str(), ifstream::binary);
	src.read((char *)key,TOTWHEELS);
	cout << "\nSetting Wheel Order...\n";
	src.read((char *)wheelorder,TOTWHEELS);
	src.close();
	
	
	for(i=0; i<TOTWHEELS; i++){
		wheels[i].SetStart(key[i]);
		printf("\rWheel %i of %i initialized (%.2f)...",i,TOTWHEELS,100.0*i/TOTWHEELS);
	}
}



/**
 * 
 */
void WheelSet::GenWheels(string path)
{
	unsigned char temp[256];
	int i;
	Wheel buildwheel;
	FILE *file;
	file = fopen(path.c_str(),"wb");
	printf("\n");
	for(i=0; i<TOTWHEELS; i++){
		printf("\rGenerating Wheel %i of %i (%.2f)",i,TOTWHEELS,100.0*i/TOTWHEELS);
		buildwheel.GenWheel();
		buildwheel.getWheel(temp);
		fwrite(temp, Wheel::WHEELSIZE, 1, file);
	}
	printf("\r%.2f",100.0*i/TOTWHEELS);
	backboard->GenWheel();
	backboard->getWheel(temp);
	fwrite(temp, Wheel::WHEELSIZE, 1, file);
	fclose(file);
}



/*** GenKey *********************************************************/
void WheelSet::GenKey(string path)
{
	std::ofstream file;
	Random rand;
	unsigned char key[256];

	printf("Generating key...\n");
	rand.ch(key,rand.DUP,TOTWHEELS);
	rand.ch(wheelorder,rand.NODUP,TOTWHEELS);

	printf("Writing key to file...\n");
	file.open(path.c_str(),std::ios::out | std::ios::binary);
	file.write((char *)key,TOTWHEELS);
	file.write((char *)wheelorder,TOTWHEELS);
	file.close();

	printf("Key Written.\n");
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



#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "enigma.h"

const int WheelSet::TOTWHEELS = 128;

WheelSet::WheelSet()
{
	wheels.resize(TOTWHEELS);
	wheelorder.assign(TOTWHEELS,0);
}


WheelSet::~WheelSet()
{
}


/**
 * 
 */
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
	backboard.setWheel(temp);
	
	file.close();

}


/**
 * 
 */
void WheelSet::LoadKey(string& path)
{
	byte key[TOTWHEELS];
	byte buffer[TOTWHEELS];
	int i;
	Random rand;

	ifstream src(path.c_str(), ifstream::binary);
	src.read((char *)key,TOTWHEELS);
	cout << "\nSetting Wheel Order...\r";
	src.read((char *)&wheelorder[0],TOTWHEELS);
	src.close();
	
	
	cout << "\nSetting Start position...\r";
	for(i=0; i<TOTWHEELS; i++){
		wheels[i].SetStart(key[i]);
		printf("Wheel %i of %i rotated (%.2f)...\r",i+1,TOTWHEELS,100.0*i/TOTWHEELS);
	}
	printf("\n");
}



/**
 * 
 */
void WheelSet::GenWheels(string path)
{
	byte temp[256];
	Wheel buildwheel;
	ofstream file(path.c_str(),ofstream::binary);
	printf("\n");
	for(int i=0; i<TOTWHEELS; i++){
		printf("\rGenerating Wheel %i of %i (%.2f) \r",i,TOTWHEELS,100.0*i/TOTWHEELS);
		buildwheel.GenWheel();
		buildwheel.getWheel(temp);
		file.write((char*)temp, Wheel::WHEELSIZE);
	}
	printf("\rGenerating Wheel %i of %i (%.2f) \r",TOTWHEELS,TOTWHEELS,100.0);
	
	backboard.GenWheel();
	backboard.getWheel(temp);
	file.write((char*)temp, Wheel::WHEELSIZE);
	printf("\rGenerating Wheel %i of %i (%.2f) complete. \n",TOTWHEELS,TOTWHEELS,100.0);
}



/*** GenKey *********************************************************/
void WheelSet::GenKey(string path)
{
	std::ofstream file;
	Random rand;
	vector<byte> key;

	cout << "Generating key...\r";
	for(auto i = TOTWHEELS-1; i >= 0; i--)	{
		wheelorder.push_back((byte)i);
		key.push_back((byte)random()%TOTWHEELS);
	}
	std::random_shuffle(wheelorder.begin(), wheelorder.end());

	cout << "Writing key to file...\r";
	file.open(path.c_str(),std::ios::out | std::ios::binary);
	file.write((char *)&key[0],TOTWHEELS);
	file.write((char *)&wheelorder[0],TOTWHEELS);
	file.close();

	cout << "Key Written: "<<path<<" \n";
}


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
		value = backboard.goingOut(value);
	}
	else{
		value = backboard.goingIn(value);
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



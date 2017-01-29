#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <fstream> 

#include "enigma.h"



/**
 * Constructor - basically a main application
 */
Enigma::Enigma()
{
}


/**
 * 
 */
Enigma::~Enigma()
{
}


/**
 * 
 */
void Enigma::GenerateKey()
{
	box.GenKey(filekey);
}

/**
 * 
 */
void Enigma::GenerateWheelSet()
{
	box.GenWheels(filewheelset);
}


/**
 *
 */
bool Enigma::Crypt(Action crypt)
{
	box.LoadWheels(filewheelset);
	box.LoadKey(filekey);
	
	std::ifstream src(filesrc.c_str(), std::ifstream::in);
	std::ofstream dest(filedest.c_str(), std::ofstream::out);
	while(!src.eof()){
		char data = (char)src.get();
		data = box.Crypt(data,crypt);
		dest.put(data);
	}
	src.close();
	dest.close();
	
	return true;
}


/**
 * 
 */
bool Enigma::Decrypt()
{
	return this->Crypt(actDecrypt);
}


/**
 * 
 */
bool Enigma::Encrypt()
{
	return this->Crypt(actEncrypt);
}



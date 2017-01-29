#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <fstream> 
#include <chrono>
#include <ctime>

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
	
	unsigned long long pos = 0;
	printf("Encrypting stream @ %llu ... \r", pos);
	std::ifstream src(filesrc.c_str(), std::ifstream::in);
	std::ofstream dest(filedest.c_str(), std::ofstream::out);
	
	
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::duration<double> elapsed;
	start = std::chrono::system_clock::now();
	while(!src.eof()){
		char data = (byte)src.get();
		data = box.Crypt(data,crypt);
		dest.put(data);
		if(pos++%10240 == 0){
			dest.flush();
			elapsed = std::chrono::system_clock::now() - start;
			printf("Encrypting stream @ %llu (%f sec/kb)... \r", pos, elapsed.count()/(pos/1024));
		}
	}
	src.close();
	dest.close();
	
	elapsed = std::chrono::system_clock::now() - start;
	printf("Encrypting stream @ %llu (%f sec/kb).       \n", pos, elapsed.count()/(pos/1024));
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



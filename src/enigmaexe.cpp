#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "enigma.h"

string EnigmaExe::getStr(){
	char buffer[250];
	getnstr(buffer, 250);
	// memory leak here?
	string rtn(buffer);
	return rtn;
}

/**
 * Constructor - basically a main application
 */
EnigmaExe::EnigmaExe(int argcount, char* arguments[])
{
	if(argcount<2){
		DisplayMenu();
	}
	else{
		GetTask(arguments);
	}
}

/**
 * Constructor - basically a main application
 */
EnigmaExe::~EnigmaExe()
{
	/* End curses mode		  */
	endwin();
}

/**
 * parses the command line for the task to be performed
 * 
 */
void EnigmaExe::GetTask(char* args[])
{
	if(strcmp(args[1],"/e")==0) task=ENCRYPT;
	if(strcmp(args[1],"/d")==0) task=DECRYPT;
	if(strcmp(args[1],"/k")==0) task=GENKEY;
	if(strcmp(args[1],"/s")==0) task=GENSET;
	switch(task){
		case ENCRYPT:
			enigma.filekey = args[2];
			enigma.filewheelset = args[3];
			enigma.filesrc = args[4];
			enigma.filedest = args[5];
			enigma.Encrypt();
			break;
		case DECRYPT:
			enigma.filekey = args[2];
			enigma.filewheelset = args[3];
			enigma.filesrc = args[4];
			enigma.filedest = args[5];
			enigma.Decrypt();
			break;
		case GENKEY:
			enigma.filekey = args[2];
			enigma.GenerateKey();
			break;
		case GENSET:
			enigma.filekey = args[2];
			enigma.GenerateWheelSet();
			break;
		default:
			string exe(args[0]);
			cout 
				<< "ERROR: improper usage\n"
				<< "Usage: " << exe << " /[task] filename [filename ...]\n"
				;
			exit(1);
			break;
	}
}


/*** GetFiles *******************************************************/
void EnigmaExe::GetFiles()
{
	erase();
	printw("Enter source file......: ");
	enigma.filesrc = getStr();
	printw("Enter destination file.: ");
	enigma.filedest = getStr();
}

/*** GetKey *********************************************************/
void EnigmaExe::GetKey()
{
	erase();
	printw("Enter 'Key' file: ");
	enigma.filekey = getStr();
}

/*** GetWheelSet ****************************************************/
void EnigmaExe::GetWheelSet()
{
	erase();
	printw("\nEnter 'Wheelset' file: ");
	enigma.filewheelset = getStr();
}


/*** DisplayMenu ****************************************************/
void EnigmaExe::DisplayMenu()
{
	
	// Start curses mode
	initscr();


	
	Task choice=ENCRYPT;
	while (choice!=QUIT){
		erase();
		
		printw("Please Select Task:\n");
		printw("  1. Encrypt File\n");
		printw("  2. Decrypt File\n");
		printw("  3. Generate a Key \n");
		printw("  4. Generate a Wheelset\n");
		printw("  5. Quit\n");
		move(21,1);
		noecho();
		choice = (Task)(getch()-'0');
		erase();
		switch(choice){
			case ENCRYPT:	// this will be option '\e'
				GetKey();
				GetWheelSet();
				GetFiles();
				enigma.Encrypt();
				break;
			case DECRYPT:	// this will be option '\d'
				GetKey();
				GetWheelSet();
				GetFiles();
				enigma.Decrypt();
				getch();
				break;
			case GENKEY:	// this will be option '\k'
				GetKey();
				enigma.GenerateKey();
				printw("\nKey '%s' Generated", enigma.filekey.c_str());
				printw("\nPress any key to continue");
				getch();
				break;
			case GENSET:	// this will be option '\s'
				GetWheelSet();
				enigma.GenerateWheelSet();
				printw("\nWheelset '%s' Generated",enigma.filewheelset.c_str());
				printw("\nPress any key to continue: ");
				getch();
				break;
			case QUIT:
				cout << "Terminating Application at user request.";
				break;
		}
	}
}


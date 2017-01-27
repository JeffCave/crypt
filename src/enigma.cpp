#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#include "enigma.h"



/**
 * Constructor - basically a main application
 */
Enigma::Enigma(int argcount, char* arguments[])
{
	if(argcount<2){
		DisplayMenu();
	}
	else{
		GetTask(arguments);
	}
}

/**
 * parses the command line for the task to be performed
 * 
 */
void Enigma::GetTask(char* args[])
{
	if(strcmp(args[1],"/e")==0) task=ENCRYPT;
	if(strcmp(args[1],"/d")==0) task=DECRYPT;
	if(strcmp(args[1],"/k")==0) task=GENKEY;
	if(strcmp(args[1],"/s")==0) task=GENSET;
	switch(task){
		case ENCRYPT:
			strcpy(filekey,args[2]);
			strcpy(filewheelset,args[3]);
			strcpy(filesrc,args[4]);
			strcpy(filedest,args[5]);
			Encrypt();
			break;
		case DECRYPT:
			strcpy(filekey,args[2]);
			strcpy(filewheelset,args[3]);
			strcpy(filesrc,args[4]);
			strcpy(filedest,args[5]);
			Decrypt();
			break;
		case GENKEY:
			strcpy(filekey,args[2]);
			box.GenKey(filekey);
			break;
		case GENSET:
			strcpy(filewheelset,args[2]);
			box.GenWheels(filewheelset);
			break;
		default:
			printf("ERROR: improper usage\n");
			printf("Usage: %s /[task] filename [filename ...]",args[0]);
			exit(1);
			break;
	}
}


/*** GetFiles *******************************************************/
void Enigma::GetFiles()
{
	erase();
	printw("Enter source file: ");
	getstr(filesrc);
	printw("Enter destination file: ");
	getstr(filedest);
}
/*** GetFiles *******************************************************/

/*** GetKey *********************************************************/
void Enigma::GetKey()
{
	erase();
	printw("Enter 'Key' file: ");
	getstr(filekey);
}
/*** GetKey *********************************************************/

/*** GetWheelSet ****************************************************/
void Enigma::GetWheelSet()
{
	erase();
	printw("\nEnter 'Wheelset' file: ");
	getstr(filewheelset);
}


/*** DisplayMenu ****************************************************/
void Enigma::DisplayMenu()
{
	
	
	initscr();			/* Start curses mode 		*/
	
	int choice=0;
	while (choice!=5){
		erase();
		
		printw("Please Select Task:\n");
		printw("  1. Encrypt File\n");
		printw("  2. Decrypt File\n");
		printw("  3. Generate a Key \n");
		printw("  4. Generate a Wheelset\n");
		printw("  5. Quit\n");
		move(21,1);
		noecho();
		choice = getch()-'0';
		echo();
		erase();
		switch(choice){
			case 1:	// this will be option '\e'
				GetKey();
				GetWheelSet();
				GetFiles();
				Encrypt();
			break;
			case 2:	// this will be option '\d'
				GetKey();
				GetWheelSet();
				GetFiles();
				Decrypt();
				getch();
			break;
			case 3:	// this will be option '\k'
				GetKey();
				box.GenKey(filekey);
				printw("\nKey '%s' Generated",filekey);
				printw("\nPress any key to continue");
				getch();
			break;
			case 4:	// this will be option '\s'
				GetWheelSet();
				box.GenWheels(filewheelset);
				printw("\nWheelset '%s' Generated",filewheelset);
				printw("\nPress any key to continue: ");
				getch();
			break;
			case 5:
				printf("Terminating Application at user request.");
			break;
      }
   }
	endwin();			/* End curses mode		  */
}
/*** doTask *******************************************************************/

/*** Crypt **********************************************************/
void Enigma::Crypt(int decrypt)
{
	FILE *src;
	FILE *dest;
	char data;
	int i;

	box.LoadWheels(filewheelset);
	box.LoadKey(filekey);
	src = fopen(filesrc,"rb");
	dest = fopen(filedest,"wb");
	i=0;
	printf("\n");
	while(1==fread(&data,1,1,src)){
		i++;
		data = box.Crypt(data,decrypt);
		fwrite(&data,1,1,dest);
		printf("\r%i bytes %scrypted",i,(decrypt?"de":"en"));
	}
	printf("\rFile %scrypted.                      ",(decrypt?"de":"en"));
	fclose(src);
	fclose(dest);
}
/*** Crypt **********************************************************/

/*** Encrypt ********************************************************/
void Enigma::Decrypt()
{
	Crypt(1);
}
/*** Encrypt ********************************************************/

/*** Decrypt ********************************************************/
void Enigma::Encrypt()
{
	Crypt(0);
}
/*** Decrypt ********************************************************/


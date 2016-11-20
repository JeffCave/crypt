/********************************************************************
/********************************************************************/

#include "enigma.h"
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

/*** Constants ******************************************************/
const int Enigma::ENCRYPT = 1;
const int Enigma::DECRYPT = 2;
const int Enigma::GENKEY  = 3;
const int Enigma::GENSET  = 4;
/*** Constants ******************************************************/

Enigma::Enigma(int argcount, char* arguments[])
{
	if(argcount<2){
		DisplayMenu();
   }
   else{
   	GetTask(arguments);
   }
}

/*** GetTask ******************************************************************/
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
/*** GetTask ********************************************************/

/*** GetFiles *******************************************************/
void Enigma::GetFiles()
{
	printf("Enter source file: ");
	scanf("%s", filesrc);
	fflush(stdin);
	printf("Enter destination file: ");
	scanf("%s",filedest);
	fflush(stdin);
}
/*** GetFiles *******************************************************/

/*** GetKey *********************************************************/
void Enigma::GetKey()
{
	printf("Enter 'Key' file: ");
	scanf("%s", filekey);
	fflush(stdin);
}
/*** GetKey *********************************************************/

/*** GetWheelSet ****************************************************/
void Enigma::GetWheelSet()
{
	printf("\nEnter 'Wheelset' file: ");
	scanf("%s", filewheelset);
	fflush(stdin);
}
/*** GetWheelSet ****************************************************/

/*** DisplayMenu ****************************************************/
void Enigma::DisplayMenu()
{
	int choice=0;
	while (choice!=5){
		clrscr();
		printf("Please Select Task:\n");
		printf("  1. Encrypt File\n");
		printf("  2. Decrypt File\n");
		printf("  3. Generate a Key \n");
		printf("  4. Generate a Wheelset\n");
		printf("  5. Quit\n");
		gotoxy(21,1);
		choice = getche()-'0';
		clrscr();
		switch(choice){
			case 1:	// this will be option '\e'
				GetKey();
				GetWheelSet();
				GetFiles();
				Encrypt();
				getch();
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
				printf("\nKey '%s' Generated",filekey);
				printf("\nPress any key to continue");
				getch();
			break;
			case 4:	// this will be option '\s'
				GetWheelSet();
				box.GenWheels(filewheelset);
				printf("\nWheelset '%s' Generated",filewheelset);
				printf("\nPress any key to continue: ");
				getch();
			break;
			case 5:
				printf("Terminating Application at user request.");
			break;
      }
   }
}
/*** doTask *******************************************************************/

/*** Crypt **********************************************************/
void Enigma::Crypt(int decrypt)
{
	FILE *src,
        *dest;
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



/**
 * 
 * 
 */
class Random{
	private:
		static bool randomized;
	public:
		static const unsigned char NODUP = 0;
		static const unsigned char DUP = 1;
		Random();
		void ch(unsigned char *, unsigned char rep=1, unsigned long arraysize=1);
};


/*** Wheel **********************************************************/
class Wheel{
	private:
		unsigned char* list;
		int timesused;
		unsigned char startpos;
	public:
		static const int WHEELSIZE;
		Wheel();
		void GenWheel();
		void LoadWheel(unsigned char *);
		void GetWheel(unsigned char *);
		unsigned char goingIn(unsigned char);
		unsigned char goingOut(unsigned char);
		int Turn();
		void SetStart(int pos);
};
/*** Wheel **********************************************************/

/*** WheelSet *******************************************************/
class WheelSet{
	private:
		Wheel* wheels;
		unsigned char * wheelorder;
		Wheel *backboard;
	public:
		static const int TOTWHEELS;
		WheelSet();
		~WheelSet();
		void GenWheels(char *path);
		void LoadWheels(char *path);
		void SaveWheels(char *path);
		unsigned char Crypt(unsigned char, int);
		void LoadKey(char *path);
		void GenKey (char *path);
		void GenWheelOrder(unsigned char *);
		void SetWheelOrder(unsigned char *);
};
/*** WheelSet *******************************************************/

/*** Enigma *********************************************************/
class Enigma{
	private:
		unsigned char task;
		WheelSet box;
		char filesrc[256];
		char filedest[256];
		char filekey[256];
		char filewheelset[256];
	public:
		static const int ENCRYPT;
		static const int DECRYPT;
		static const int GENKEY;
		static const int GENSET;
		Enigma(int, char**);
		void doTask();
		void DisplayMenu();
		void GetTask(char**);
		void GetFiles();
		void GetKey();
		void GetWheelSet();
		void Crypt(int);
		void Encrypt();
		void Decrypt();
};
/*** Enigma *********************************************************/

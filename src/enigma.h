

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
		Wheel *wheels;
		unsigned char *wheelorder;
		Wheel *backboard;
	public:
		static const int TOTWHEELS;
		WheelSet();
		~WheelSet();
		void GenWheels(unsigned char *path);
		void LoadWheels(unsigned char *path);
		void SaveWheels(unsigned char *path);
		unsigned char Crypt(unsigned char, int);
		void LoadKey(unsigned char *path);
		void GenKey (unsigned char *path);
		void GenWheelOrder(unsigned char *);
		void SetWheelOrder(unsigned char *);
};
/*** WheelSet *******************************************************/

/*** Enigma *********************************************************/
class Enigma{
	private:
		unsigned char task;
		WheelSet box;
		unsigned char filesrc[256];
		unsigned char filedest[256];
		unsigned char filekey[256];
		unsigned char filewheelset[256];
	public:
		static const int ENCRYPT;
		static const int DECRYPT;
		static const int GENKEY;
		static const int GENSET;
		Enigma(int,unsigned char**);
		void doTask();
		void DisplayMenu();
		void GetTask(unsigned char**);
		void GetFiles();
		void GetKey();
		void GetWheelSet();
		void Crypt(int);
		void Encrypt();
		void Decrypt();
};
/*** Enigma *********************************************************/

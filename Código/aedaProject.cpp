#include "menus.h"

using namespace std;

/** @defgroup aedaProject aedaProject
 * @{
 * Initial function - Reads and Writes
 */

/**
 * @brief Reads the info from the files in the begining of the program
 *
 * @param apps Appstore
 */
void readAll(AppStore &apps) {
	try {
		apps.AllTimeApps = readApps(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at read.";
	}
	try {
		apps.clients = readClients(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at read.";
	}
	try {
		apps.developers = readDevs(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at read.";
	}
	try {
		apps.companies = readComp(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at read.";
	}
	try {
		apps.codes = readCodes(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at read.";
	}
	try {
		apps.sales = readSales(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at read.";
	}
	try {
		readVals(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at read.";
	}
	try {
		readAppstoBst(apps);
		} catch (fileNotOpened &f) {
			cout << "ERROR: File " << f.retname() << " not opened at read.";
		}
}

/**
 * @brief Wrights the info from the files in the begining of the program
 *
 * @param apps Appstore
 */
void writeAll(AppStore &apps) {
	try {
		writeApps(apps.AllTimeApps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at write.";
	}

	try {
		writeClients(apps.clients);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at write.";
	}
	try {
		writeDevs(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at write.";
	}
	try {
		writeComp(apps.companies);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at write.";
	}
	try {
		writeSales(apps.sales);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at write.";
	}
	try {
		writeVals(apps);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at write.";
	}
	try {
		writeAppsToBst(apps.appsBst);
	} catch (fileNotOpened &f) {
		cout << "ERROR: File " << f.retname() << " not opened at write.";
	}
	//other writes remaining
}

/**
 * @brief loads the hashtable
 *
 * @param apps AppStore
 */
void loadHash(AppStore & apps){
	for(int i = 0; i < apps.AllTimeApps.size(); i++){
		if(!apps.AllTimeApps[i].getForSale()){
			cout << apps.AllTimeApps[i].getName() << " was inserted on hash table\n";
			apps.hash.insert(&apps.AllTimeApps[i]);
			pause();
		}
	}
}

/**
 * @brief Creates AppStore and initializes the program
 *
 * @return 0 upon success
 */
int main() {
	AppStore appstore = AppStore();
	readAll(appstore);
	loadHash(appstore);
	int choice = -1;
	int menuNum;
	bool exit = false;
	while(!exit){
		choice=-1;
	while(choice<=0 || choice>=5){
		choice = firstScreen();
	}
	switch(choice){
	case 1:
		menuNum = loginMenu(appstore);
		if(menuNum!=0){
			Menu(menuNum,appstore);
		}
		break;
	case 2:
		try{
		signUpMenu(appstore);
		exit = false;
		}catch (OutOfBoolRange &f) {
			cout << "ERROR: " << f.retintro() << " is not an answer to this question";
		}
		break;
	case 3:
		Exit();
		writeAll(appstore);
		return 0;
		break;
	}
	}

	return 0;
}

/**@}*/

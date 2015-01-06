#include "appStore.h"
#include <iostream>
#include <fstream>
#include <vector>

void cs();

void pause();

void Exit();

int firstScreen();

int signUpMenu(AppStore &apps);

bool checkusername(string u, AppStore &app);

int Menu(int a,AppStore &appstore);

int loginMenu(AppStore &apps);

int checkUser(string username, string password, AppStore &apps);

vector<App> readApps(AppStore & apps);

vector<Client> readClients(AppStore &apps);

vector<Developer> readDevs(AppStore &apps);

vector<Company> readComp(AppStore &apps);

void readAppstoBst(AppStore & apps);

void writeAppsToBst(BST<AppToBst> app);

void writeApps(vector<App> &v);

void writeClients(vector<Client> c);

void writeDevs(AppStore & apps);

void writeComp(vector<Company> vd);

int buyApps(AppStore &apps);

vector <string> readCodes(AppStore &apps);

vector<Sale> readSales(AppStore &apps);

void writeSales(vector<Sale> vd);

float average(App*a, vector<Client> clients);

void top10menu(AppStore apps);

void writeVals(AppStore & apps);

void readVals(AppStore & apps);

void AdminBST(AppStore &apps);

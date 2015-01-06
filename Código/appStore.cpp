#include "menus.h"
#include <ctime>
#include "BST.h"

unsigned int APPID = 0;
unsigned int SALEID = 0;


void setAppId(int id){
	APPID = id;
}
//Client

Client::Client() {
	vector<App*> a;
	vector<classification> b;
	name = "";
	username = "";
	password = "";
	money = 0;
	apps = a;
	classif = b;
}

Client::Client(string u,string p,string n){
	vector<App*> a;
	vector<classification> b;
	username = u;
	password = p;
	name = n;
	money = 0;
	apps = a;
	classif = b;
}

Client::Client(string n) {
	vector<App*> a;
	vector<classification> b;
	username = "";
	password = "";
	name = n;
	apps = a;
	money = 0;
	classif = b;
}

Client::Client(string u,string pw,string n,float m, vector<App*> v,vector<classification> vc) {
	vector<App*> vec;
	username = u;
	password = pw;
	name = n;
	apps = v;
	money = m;
	classif = vc;
	cart = vec;
}

string Client::getName() const {
	return name;
}

void Client::setName(string n) {
	name = n;
}

void Client::setUsername(string n) {
	username = n;
}

void Client::plusMoney(float l){
	money = money + l;
}

float Client::getMoney() const{
	return money;
}

void Client::setMoney(float m){
	money = m;
}

vector<App*> Client::getApps() const {
	return apps;
}

void Client::setApps(vector<App*> v) {
	apps = v;
}

vector<classification> Client::getClass() const {
	return classif;
}

void Client::setClass(vector<classification> c) {
	classif = c;
}

string Client::getUser() const{
	return username;
}

string Client::getPw() const{
	return password;
}

void Client::pushBackApp(App*a){
	apps.push_back(a);
}

int Client::pushBackDescription(int id,int stars ,string description){
	for(int i = 0; i < classif.size();i++){
		if(classif[i].getId()==id){
			classif[i].setCla(description);
			return 1;
		}
	}
	classification classifi = classification(id,stars,description);
	classif.push_back(classifi);
	return 1;
}
void Client::eraseCartApp(int a){
	cart.erase(cart.begin() + a);
}
void Client::setPw(string pw){
	password = pw;
}

void Client::addToCart(App*a){
	cart.push_back(a);
}
vector<App*> Client::getCart(){
	return cart;
}
//App

App::App() {
	name = "";
	cost = -1;
	id = 0;
	category = "";
	description = "";
	classification = 0;
}

App::App(string n, float co, string ca, string di, bool b, float a) {
	name = n;
	cost = co;
	id = APPID;
	APPID++;
	category = ca;
	description = di;
	forSale = b;
	classification = a;
}

string App::getName() const {
	return name;
}

void App::setName(string n) {
	name = n;
}

float App::getCost() const {
	return cost;
}

void App::setCost(float c) {
	cost = c;
}

string App::getCategory() const {
	return category;
}

void App::setCategory(string cat) {
	category = cat;
}

string App::getDescription() const {
	return description;
}

void App::setDescription(string desc) {
	description = desc;
}

int App::getId() const {
	return id;
}

bool App::getForSale() const {
	return forSale;
}

void App::setForSale(bool b) {
	forSale = b;
}

//AppForSubmission

AppForSubmission::AppForSubmission(App a, Date sd, string uName):app(a), SubDate(sd), username(uName){}

bool AppForSubmission::operator<(AppForSubmission const &b) const{
	if(SubDate < b.SubDate)
		return true;
	else if(SubDate > b.SubDate)
		return false;
	else if(app.getCost() > b.app.getCost())
		return true;
	else if(app.getCost() < b.app.getCost())
		return false;
	else if(app.getName() > b.app.getName())
		return true;
	else if(app.getName() < b.app.getName())
		return false;
}


//Developer

Developer::Developer() {
	username = "";
	password = "";
	name = "";
	address = "";
	money = 0;
	vector<App*> a;
	apps = a;
}

void Developer::setMoney(float m){
	money = m;
}
Developer::Developer(string n, string a) {
	username = "";
	password = "";
	name = n;
	address = a;
	money = 0;
	vector<App*> b;
	apps = b;
}

Developer::Developer(string u, string p,string n, string a, float m,vector<App*> v) {
	username = u;
	password = p;
	name = n;
	address = a;
	apps = v;
	money = m;
}

Developer::Developer(string u, string p,string n, string a) {
	username = u;
	password = p;
	name = n;
	address = a;
	vector<App*> b;
	apps = b;
	money = 0;
}

float Developer::getMoney() const{
	return money;
}

string Developer::getName() const {
	return name;
}

void Developer::setName(string n){
	name=n;
}

string Developer::getAddress() const{
	return address;
}

void Developer::setAddress(string ad){
	address = ad;
}

vector<App*> Developer::getApps() const{
	return apps;
}

void Developer::setApps(vector<App*> v){
	apps = v;
}

string Developer::getUser() const{
	return username;
}

void Developer::setUsername(string n) {
	username = n;
}

string Developer::getPw() const{
	return password;
}

void Developer::setPw(string pw){
	password = pw;
}

//Company

Company::Company(){
}

Company::Company(string u,string p,string n, string a,float m,int ni, vector<App*> v)
: Developer(u, p, n, a, m , v){
	nif = ni;
}

Company::Company(string username,string password,string name,string address,int ni)
:Developer(username, password, name, address){
	nif=ni;
}

int Company::getNif() const{
	return nif;
}

void Company::setNif(int n){
	nif=n;
}

//Date

Date::Date(){
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );
	day = now->tm_mday;
	month = (now->tm_mon + 1);
	year = (now->tm_year + 1900);
	hour = now->tm_hour;
	minutes = now->tm_min;
}

Date::Date(int h, int mi, int d, int m, int y){
	day = d;
	month = m;
	year = y;
	minutes = mi;
	hour = h;
}

bool Date::operator <(Date const& b) const{
	if(year < b.year)
		return false;
	else if(year > b.year)
		return true;
	else if(month < b.month)
		return false;
	else if(month > b.month)
		return true;
	else if(day < b.day)
		return false;
	else if(day > b.day)
		return true;
	else if(hour < b.hour)
		return false;
	else if(hour > b.hour)
		return true;
	else if(minutes < b.minutes)
		return false;
	else if(minutes > b.minutes)
		return true;
}

bool Date::operator >(Date const& b) const{
	if(year < b.year)
		return true;
	else if(year > b.year)
		return false;
	else if(month < b.month)
		return true;
	else if(month > b.month)
		return false;
	else if(day < b.day)
		return true;
	else if(day > b.day)
		return false;
	else if(hour < b.hour)
		return true;
	else if(hour > b.hour)
		return false;
	else if(minutes < b.minutes)
		return true;
	else if(minutes > b.minutes)
		return false;
}


bool Date::operator ==(Date const& b) const{
	return ((year == b.year) && (month == b.month) && (day == b.day) && (hour == b.hour) && (minutes == b.minutes));
}

//Sale
string Sale::getUser(){
	return buyer->getUser();
}

Sale::Sale() {
	Date a = Date();
	date = a;
	id = SALEID;
	SALEID++;
	App*b = new App();
	sold = b;
	Client* c = new Client();
	buyer = c;
}
void Sale::setApp(App*b){
	sold = b;
}

Sale::Sale(App * s, Client* b) {
	date = Date();
	id = SALEID;
	sold = s;
	buyer = b;
}

Date Sale::getDate() const {
	return date;
}

void Sale::setDate(Date d) {
	date = d;
}

int Sale::getID() const {
	return id;
}

void Sale::setID(int i) {
	id = i;
}

int Sale::getStaticID() const {
	return SALEID;
}

void Sale::setStaticID(int i) {
	SALEID = i;
}

App*Sale::getAppSold() const {
	return sold;
}

Client* Sale::getBuyer() const {
	return buyer;
}

void Sale::setBuyer(Client* b) {
	buyer = b;
}


//AppStore

AppToBst initial;

AppStore::AppStore() : appsBst(initial) {
	vector<App> a;
	AllTimeApps = a;
}

int AppStore::findIndexDeveloper(string n) {
	for(unsigned int i = 0; i < developers.size(); i++)
		if(developers[i].getName() == n)
			return i;
	return -1;
}

int AppStore::findIndexDevUser(string n){
	for(unsigned int i = 0; i < developers.size(); i++)
		if(developers[i].getUser() == n)
			return i;
	return -1;
}

int AppStore::findIndexCompany(string n) {
	for(unsigned int i = 0; i < companies.size(); i++)
		if(companies[i].getName() == n)
			return i;
	return -1;
}

int AppStore::findIndexCompUser(string n) {
	for(unsigned int i = 0; i < companies.size(); i++)
		if(companies[i].getUser() == n)
			return i;
	return -1;
}

int AppStore::findIndexApp(string n) {
	for (unsigned int i = 0; i < AllTimeApps.size(); i++)
		if (AllTimeApps[i].getName() == n)
			return i;
	return -1;
}

int AppStore::findIndexClient(string n) {
	for (unsigned int i = 0; i < clients.size(); i++)
		if (clients[i].getName() == n)
			return i;
	return -1;
}

void AppStore::eraseAppDeveloper(int id) {
	for(unsigned int i = 0; i < developers.size(); i++)
		for(unsigned int j = 0; j < developers[i].apps.size(); j++)
			if (developers[i].apps[j]->getId() == id) {
				developers[i].apps.erase(developers[i].apps.begin() + j);
				return;
			}
	for(unsigned int i = 0; i < companies.size(); i++)
		for(unsigned int j = 0; j < companies[i].apps.size(); j++)
			if (companies[i].apps[j]->getId() == id) {
				companies[i].apps.erase(companies[i].apps.begin() + j);
				return;
			}
	return;
}

//------------CRUD - Clients----------

bool AppStore::createClient() {
	string us, pass, nam;
	float mo;
	cs();
	cout << "\n\n              Create a new Client";
	cout << "\n\nUsername:                 ";
	getline(cin,us);
	cout << "\nPassword:                   ";
	getline(cin,pass);
	cout << "\nName:                       ";
	getline(cin,nam);
	cout << "\nMoney:                      ";
	cin >> mo;
	cin.clear();
	cin.ignore();
	vector<App*> v;
	vector<classification> b;
	Client final = Client(us, pass, nam, mo, v, b);
	clients.push_back(final);
	return true;
}

void AppStore::readClient() {
	cs();
	int index;
	string n;
	cout << "\n\nType the name of the Client you want to read: ";
	getline(cin,n);
	index = findIndexClient(n);
	if (index == -1) {
		cout << "Name does not exist.";
		return;
	}
	Client a = clients[index];
	cout << "Name:          " << a.getName();
	cout << "\nPassword:    " << a.getPw();
	cout << "\nUsername:    " << a.getUser();
	cout << "\nMoney:       " << a.getMoney();

	cout << "\nThis Client has " << a.getApps().size() << " apps.";

	pause();
}

bool AppStore::updateClient() {
	int intro = 0;
	int index;
	string n, c;
	float l;
	cs();
	cout << "\n\nType the name of the Client you want to update: ";
	cin >> n;
	cin.clear();
	cin.ignore();
	index = findIndexClient(n);
	if (index == -1)
		throw ClientNotFound(n);
	cs();
	while(intro < 1 || intro > 4) {
		cout << "\n\n              What do you want to update?";
		cout << "\n\n1.Name";
		cout << "\n2.Username";
		cout << "\n3.Password";
		cout << "\n4.Money";
		cin >> intro;
		cin.clear();
		cin.ignore();
	}
	cs();
	if (intro == 1) {
		cout << "Name: ";
		cin >> n;
		cin.clear();
		cin.ignore();
		clients[index].setName(n);
	}
	else if (intro == 2) {
		cout << "Username: ";
		cin >> c;
		cin.clear();
		cin.ignore();
		clients[index].setUsername(c);
	}
	else if (intro == 3) {
		cout << "Password: ";
		cin >> n;
		cin.clear();
		cin.ignore();
		clients[index].setPw(n);
	}
	else if (intro == 4) {
		cout << "Money: ";
		cin >> l;
		cin.clear();
		cin.ignore();
		clients[index].setMoney(l);
	}	return true;
}

bool AppStore::deleteClient() {
	string n;
	int index, id;
	cs();
	cout << "\n\n               Delete a Client";
	cout << "\n\nName of the Client to delete: ";
	getline(cin,n);
	cin.clear();
	cin.ignore();
	index = findIndexClient(n);
	if (index == -1)
		return false;
	clients.erase(clients.begin() + index);
	return true;
}

void AppStore::showAllSales() const {
	cs();
	if (sales.size() == 0) {
		cout << "No sales exist";
		pause();
		return;
	}
	cout << "                 List of Sales\n\n\n";
	for (unsigned int i = 0; i < sales.size(); i++) {
		cout << sales[i].getAppSold()->getName() << " - Bought by " << sales[i].getBuyer()->getName()
																				<< " - at " << sales[i].getDate().day << "/" << sales[i].getDate().month << "/"
																				<< sales[i].getDate().year << "\n";
	}
	pause();
}

void AppStore::showAllClients() const {
	cs();
	if (clients.size() == 0) {
		cout << "No clients exist";
		pause();
		return;
	}
	cout << "                 List of Clients\n\n\n";
	for (unsigned int i = 0; i < clients.size(); i++) {
		cout << clients[i].getName() << " - " << clients[i].getMoney() << " - " << clients[i].getApps().size() << " apps.\n";
	}
	pause();
}

void AppStore::showAllApps() const {
	cs();
	if (AllTimeApps.size() == 0) {
		cout << "No apps exist";
		pause();
		return;
	}
	cout << "                 List of Apps\n\n\n";
	for (unsigned int i = 0; i < AllTimeApps.size(); i++) {
		cout << AllTimeApps[i].getId() << " - " << AllTimeApps[i].getName() << " - "
				<< AllTimeApps[i].getCost() << " - " << AllTimeApps[i].getCategory() << "\n";
	}
	pause();
}

void AppStore::showAllDevelopers() const {
	cs();
	if (developers.size() == 0) {
		cout << "No developers exist";
		pause();
		return;
	}
	cout << "                 List of Developers\n\n\n";
	for (unsigned int i = 0; i < developers.size(); i++) {
		cout << developers[i].getName() << " - " << developers[i].getMoney() << " - "
				<< developers[i].getApps().size() << " apps.\n";
	}
	pause();
}

void AppStore::showAllCompanies() const {
	cs();
	if (companies.size() == 0) {
		cout << "No companies exist";
		pause();
		return;
	}
	cout << "                 List of Companies\n\n\n";
	for (unsigned int i = 0; i < companies.size(); i++) {
		cout << companies[i].getName() << " - " << companies[i].getMoney() << " - "
				<< "NIF: " << companies[i].getNif() << companies[i].getApps().size() << " apps.\n";
	}
	//	pause();
}

//------------CRUD - APPs-------------

bool AppStore::createApp() {
	string ca, n, di, temp, dev;
	float co;
	bool b;
	int index;
	cs();
	cout << "\n\n              Create a new App";
	cout << "\n\nName:                     ";
	getline(cin,n);
	cin.clear();
	cin.ignore();
	cout << "\nCost:                       ";
	cin >> co;
	cin.clear();
	cin.ignore();
	cout << "\nCategory:                   ";
	getline(cin,ca);
	cin.clear();
	cin.ignore();
	cout << "\nDescription:                ";
	getline(cin,di);
	cin.clear();
	cin.ignore();
	cout << "\nIs it for sale? (y/n):      ";
	getline(cin,temp);
	cin.clear();
	cin.ignore();
	if (temp != "y" && temp != "n")
		throw OutOfBoolRange(temp);
	else if (temp == "y")
		b = true;
	else
		b = false;
	cout << "\nWhich Developer/Company:    ";
	getline(cin,dev);
	cin.clear();
	cin.ignore();
	App final = App(n, co, ca, di, b);
	if (findIndexDeveloper(dev) == -1){
		if(findIndexCompany(dev) == -1)
			throw DeveloperOrCompanyNotFound(dev);
	}
	if (findIndexCompany(dev) != -1) {
		AllTimeApps.push_back(final);
		App* a = &AllTimeApps[AllTimeApps.size() - 1];
		vector<App*> c = companies[findIndexCompany(dev)].getApps();
		c.push_back(a);
		companies[findIndexCompany(dev)].setApps(c);
	}
	else if (findIndexDeveloper(dev) != -1) {
		AllTimeApps.push_back(final);
		App* a = &AllTimeApps[AllTimeApps.size() - 1];
		vector<App*> c = developers[findIndexDeveloper(dev)].getApps();
		c.push_back(a);
		developers[findIndexDeveloper(dev)].setApps(c);
	}
	AppToBst tem = AppToBst(final.getId(), final.getClassification(), final.getCost(), final.getCategory());
	appsBst.insert(tem);
	return true;
}

void AppStore::readApp() {
	cs();
	int index;
	string n;
	cout << "\n\nType the name of the App you want to read: ";
	getline(cin,n);
	index = findIndexClient(n);
	if (index == -1) {
		cout << "Name does not exist.";
		return;
	}
	App a = AllTimeApps[index];
	cout << "Name:        " << a.getName();
	cout << "\nCost:        $" << a.getCost();
	cout << "\nID:          " << a.getId();
	cout << "\nCategory:    " << a.getCategory();
	cout << "\nDescription: " << a.getDescription();
	if (a.getForSale())
		cout << "\nThis App is for sale.\n\n";
	else
		cout << "\nThis App is not for sale.\n\n";
	pause();
}

bool AppStore::updateApp() {
	int intro = 0;
	int index, index2, index3;
	string n;
	float c;
	cs();
	cout << "\n\nType the name of the App you want to update: ";
	getline(cin,n);
	index = findIndexApp(n);
	if (index == -1)
		throw AppNotFound(n);
	cs();
	while(intro < 1 || intro > 6) {
		cout << "\n\n              What do you want to update?";
		cout << "\n\n1.Name";
		cout << "\n2.Cost";
		cout << "\n3.Category";
		cout << "\n4.Description";
		cout << "\n5.Is it for sale?";
		cout << "\n6.Which Developer/Company made the App\n";
		cin >> intro;
		cin.clear();
		cin.ignore();
	}
	cs();
	if (intro == 1) {
		cout << "Name: ";
		getline(cin,n);
		AllTimeApps[index].setName(n);
	}
	else if (intro == 2) {
		cout << "Cost: ";
		cin >> c;
		cin.clear();
		cin.ignore();
		AllTimeApps[index].setCost(c);
		BSTItrIn<AppToBst> it(appsBst);
		while (!it.isAtEnd()) {
			if (it.retrieve().id == AllTimeApps[index].getId()) {
				it.retrieve().cost = AllTimeApps[index].getCost();
			}
			it.advance();
		}
		BstReorganize();
	}
	else if (intro == 3) {
		cout << "Category: ";
		getline(cin,n);
		AllTimeApps[index].setCategory(n);
		BSTItrIn<AppToBst> it(appsBst);
		while (!it.isAtEnd()) {
			if (it.retrieve().id == AllTimeApps[index].getId()) {
				it.retrieve().categ = AllTimeApps[index].getCategory();
			}
			it.advance();
		}
		BstReorganize();
	}
	else if (intro == 4) {
		cout << "Description: ";
		getline(cin,n);
		AllTimeApps[index].setDescription(n);
	}
	else if (intro == 5) {
		cout << "Is it for sale? (y/n) ";
		getline(cin,n);
		bool q;
		if (n == "y")
			q = true;
		else if (n == "n")
			q = false;
		else
			throw OutOfBoolRange(n);
		AllTimeApps[index].setForSale(q);
	} else {
		cout << "Type the name of the Developer//Company: ";
		getline(cin,n);
		index2 = findIndexDeveloper(n);
		index3 = findIndexCompany(n);
		if (index2 == -1)
			if (index3 == -1)
				throw DeveloperOrCompanyNotFound(n);
			else {
				vector<App*> a = companies[index3].getApps();
				a.push_back(&AllTimeApps[index]);
				eraseAppDeveloper(AllTimeApps[index].getId());
				companies[index3].setApps(a);
			}
		else {
			vector<App*> a = developers[index3].getApps();
			a.push_back(&AllTimeApps[index]);
			eraseAppDeveloper(AllTimeApps[index].getId());
			developers[index2].setApps(a);
		}
	}
	return true;
}

bool AppStore::deleteApp() {
	string n;
	int index, id;
	cs();
	cout << "\n\n               Delete an App";
	cout << "\n\nName of the App to delete: ";
	getline(cin,n);
	index = findIndexApp(n);
	if (index == -1)
		return false;
	id = AllTimeApps[index].getId();
	for (int j = 0; j < developers.size(); j++)
		for (int q = 0; q < developers[j].apps.size(); q++)
			if (developers[j].apps[q]->getId() == id)
				developers[j].apps.erase(developers[j].apps.begin() + q);
	for (int j = 0; j < companies.size(); j++)
		for (int q = 0; q < companies[j].apps.size(); q++)
			if (companies[j].apps[q]->getId() == id)
				companies[j].apps.erase(companies[j].apps.begin() + q);
	AllTimeApps.erase(AllTimeApps.begin() + index);
	BstRemove(id);
	return true;
}

//------------CRUD - Apps Awaiting Approval----------

void AppStore::validateApp(){
	string choice;
	if(validation.empty()){
		cs();
		cout << "There are no apps awaiting approval!";
	}
	else{
		do{
			cs();
			cout << "The next app awaiting your approval is: \n\n" <<
					"Name: " << validation.top().getApp().getName() <<
					"\n\nCost: " << validation.top().getApp().getCost() <<
					"\n\nDescription: " << validation.top().getApp().getDescription() <<
					"\n\nDeveloper: " << validation.top().getUsername() <<
					"\n\nDate of submission: " << validation.top().getSubDate().day << "/" << validation.top().getSubDate().month << "/" << validation.top().getSubDate().year << ", ";
			if(validation.top().getSubDate().hour < 10)
				cout << "0";
			cout << validation.top().getSubDate().hour << ":";
			if(validation.top().getSubDate().minutes < 10)
				cout << "0";
			cout << validation.top().getSubDate().minutes;

			cout << "\n\nDo you wish to give it your approval and make it available for purchase? (y/n)\n";
			cin >> choice;
		}while((choice != "y") && (choice != "Y") && (choice != "n") && (choice != "N"));

		if((choice == "y") || (choice == "Y")){
			string ca = validation.top().getApp().getCategory();
			string n = validation.top().getApp().getName();
			string di = validation.top().getApp().getDescription();
			string dev = validation.top().getUsername();
			float co = validation.top().getApp().getCost();
			int id = validation.top().getApp().getId();
			cs();
			App final = App(n, co, ca, di, true, 0);
			final.setId(id);
			if (findIndexDevUser(dev) == -1){
				if(findIndexCompUser(dev) == -1)
					throw DeveloperOrCompanyNotFound(dev);
			}

			if (findIndexCompUser(dev) != -1) {
				cout << endl << "It's a company app!" << endl;
				AllTimeApps.push_back(final);
				App* a = &AllTimeApps[AllTimeApps.size() - 1];
				AppToBst b = AppToBst(a->getId(), a->getClassification(), a->getCost(), a->getCategory());
				appsBst.insert(b);
				vector<App*> c = companies[findIndexCompUser(dev)].getApps();
				c.push_back(a);
				companies[findIndexCompUser(dev)].setApps(c);
			}
			else if (findIndexDevUser(dev) != -1) {
				cout << endl << "It's a dev app!" << endl;
				AllTimeApps.push_back(final);
				App* a = &AllTimeApps[AllTimeApps.size() - 1];
				AppToBst b = AppToBst(a->getId(), a->getClassification(), a->getCost(), a->getCategory());
				appsBst.insert(b);
				vector<App*> c = developers[findIndexDevUser(dev)].getApps();
				c.push_back(a);
				developers[findIndexDevUser(dev)].setApps(c);
			}
			validation.pop();
			cout << "The App was validated and is now available for purchase!";
			pause();
		}
		else{
			cs();
			validation.pop();
			cout << "The App was not validated and was removed from the \"Apps awaiting approval\" queue!";
		}

	}
	pause();
}

void AppStore::readAppWaitingApproval() {
	cs();
	string n;
	priority_queue<AppForSubmission> tmp = validation;
	cout << "\n\nType the name of the App you want to read: ";
	getline(cin,n);
	while(!tmp.empty()){
		if(tmp.top().getApp().getName() == n)
			break;
	}

	if(tmp.empty())
		cout << "\nThere is no App awaiting approval with that name!" << endl;
	else{
		App a = tmp.top().getApp();
		cout << "Name:        " << a.getName();
		cout << "\nCost:        $" << a.getCost();
		cout << "\nID:          " << a.getId();
		cout << "\nCategory:    " << a.getCategory();
		cout << "\nDescription: " << a.getDescription();
	}
	pause();
}

void AppStore::updateAppWaitingApproval() {
	int intro = 0;
	int appid = -1;
	string n;
	float c;
	cs();
	cout << "\n\nType the name of the App you want to update: ";
	getline(cin,n);
	priority_queue<AppForSubmission> tmp = validation;
	priority_queue<AppForSubmission> set;
	while(!tmp.empty()){
		if(n == tmp.top().getApp().getName()){
			appid = tmp.top().getApp().getId();
			break;
		}
		tmp.pop();
	}
	if(appid == -1)
	{
		cs();
		cout << "There is no App with that name!\n";
		pause();
		return;
	}
	cs();
	while(intro < 1 || intro > 4) {
		cout << "\n\n              What do you want to update?";
		cout << "\n\n1.Name";
		cout << "\n2.Cost";
		cout << "\n3.Category";
		cout << "\n4.Description";
		cin >> intro;
		cin.clear();
		cin.ignore();
	}
	cs();
	if (intro == 1) {
		tmp = validation;
		cout << "New Name: ";
		getline(cin,n);
		while(!tmp.empty()){
			if(tmp.top().getApp().getId() == appid){
				App myapp = tmp.top().getApp();
				myapp.setName(n);
				AppForSubmission mysub(myapp,tmp.top().getSubDate(),tmp.top().getUsername());
				set.push(mysub);
			}else{
				set.push(tmp.top());
			}
			tmp.pop();
		}
		setValidation(set);
	}
	else if (intro == 2) {
		tmp = validation;
		cout << "New Cost: ";
		cin >> c;
		while(!tmp.empty()){
			if(tmp.top().getApp().getId() == appid){
				App myapp = tmp.top().getApp();
				myapp.setCost(c);
				AppForSubmission mysub(myapp,tmp.top().getSubDate(),tmp.top().getUsername());
				set.push(mysub);
			}else{
				set.push(tmp.top());
			}
			tmp.pop();
		}
		setValidation(set);
	}
	else if (intro == 3) {
		tmp = validation;
		cout << "New Category: ";
		getline(cin,n);
		while(!tmp.empty()){
			if(tmp.top().getApp().getId() == appid){
				App myapp = tmp.top().getApp();
				myapp.setCategory(n);
				AppForSubmission mysub(myapp,tmp.top().getSubDate(),tmp.top().getUsername());
				set.push(mysub);
			}else{
				set.push(tmp.top());
			}
			tmp.pop();
		}
		setValidation(set);
	}
	else if (intro == 4) {
		tmp = validation;
		cout << "New Description: ";
		getline(cin,n);
		while(!tmp.empty()){
			if(tmp.top().getApp().getId() == appid){
				App myapp = tmp.top().getApp();
				myapp.setDescription(n);
				AppForSubmission mysub(myapp,tmp.top().getSubDate(),tmp.top().getUsername());
				set.push(mysub);
			}else{
				set.push(tmp.top());
			}
			tmp.pop();
		}
		setValidation(set);
	}
}

void AppStore::deleteAppWaitingApproval() {
	cs();
	string n;
	priority_queue<AppForSubmission> tmp = validation;
	cout << "\n\nType the name of the App you want to delete: ";
	getline(cin,n);
	priority_queue<AppForSubmission> set;
	while(!tmp.empty()){
		if(n != tmp.top().getApp().getName())
			set.push(tmp.top());
		tmp.pop();
	}
	if(validation.size() != set.size()){
		setValidation(set);
		cs();
		cout << endl << endl << "Removed from waiting approval list";
	}
	else{
		cs();
		cout << endl << endl << "There is no App with that name!";
	}
	pause();
}

string AppStore::getDevFromApp(string name){
	for(int i = 0; i < developers.size(); i++){
		for(int a = 0; a < developers[i].getApps().size();a++){
			if(developers[i].getApps()[a]->getName() == name){
				return developers[i].getUser();
			}
		}
	}
	for(int i = 0; i < companies.size(); i++){
		for(int a = 0; a < companies[i].getApps().size();a++){
			if(companies[i].getApps()[a]->getName() == name){
				return companies[i].getUser();
			}
		}
	}
	return "null";
}

void AppStore::showHashApps() {
	cs();
	cout << "\n\nApps not on sale\n\n";
	string n;
	tr1::unordered_set<App*>::iterator i = hash.begin();
	while(i != hash.end()){
		cout << "App Name: " << (*i)->getName() << "  Dev: " << getDevFromApp((*i)->getName());
		cout << endl;
		i++;
	}
	pause();
}

bool AppStore::exist(string name) {
	for(int i = 0; i < AllTimeApps.size(); i++){
		if(AllTimeApps[i].getName() == name){
			return true;
		}
	}
	priority_queue<AppForSubmission> tmp = validation;
	while(!tmp.empty()){
		if(tmp.top().getApp().getName() == name){
			return true;
		}
		tmp.pop();
	}
	return false;
}

bool AppStore::devExist(string name){
	for(int i = 0; i < developers.size(); i++){
		if(developers[i].getName() == name){
			return true;
		}
	}
	for(int i = 0; i < companies.size();i++){
		if(companies[i].getName() == name){
			return true;
		}
	}

	return false;
}

int AppStore::createHashApps(){
	cs();
	cout << "\nApp Info\n\n";
	string name,cost,category,description,dev;
	cout << "Set name: ";
	getline(cin,name);
	if(exist(name)){
		cout << "\nThis app already exists\n";
		pause();
		return 1;
	}
	cout << "Set cost: ";
	getline(cin,cost);
	if(atof(cost.c_str()) < 0){
		cout << "\n\nYou cant set a negative cost\n\n";
		pause();
		return 1;
	}
	cout << "Set description: ";
	getline(cin,description);
	cout << "Set category: ";
	getline(cin,category);
	cout << "Dev or Company Name: ";
	getline(cin,dev);
	if(!devExist(dev)){
		cout << "There is no such Dev or Company" << endl;
		pause();
		return 1;
	}
	App a(name,atof(cost.c_str()),category,description,false,0);
	a.setClassification(-1);
	AllTimeApps.push_back(a);
	appsBst.insert(AppToBst(a.getId(), a.getClassification(), a.getCost(), a.getCategory()));
	hash.insert(&AllTimeApps[AllTimeApps.size()-1]);
	for(int i = 0; i < developers.size(); i++){
		if(developers[i].getName() == dev){
			developers[i].apps.push_back(&AllTimeApps[AllTimeApps.size()-1]);
		}
	}
	for(int i = 0; i < companies.size();i++){
		if(companies[i].getName() == dev){
			companies[i].apps.push_back(&AllTimeApps[AllTimeApps.size()-1]);
		}
	}
	return 0;
}
void AppStore::updateHashApps(){
	vector<App*> temp;
	int choice = -1;
	while(choice < 1 || choice > temp.size()){
		cs();
		temp.clear();
		cout << "\n\nApps not on sale\n\n";
		string n;
		int indice = 1;
		tr1::unordered_set<App*>::iterator i = hash.begin();
		while(i != hash.end()){
			cout << indice << " - App Name: " << (*i)->getName() << "  Dev: " << getDevFromApp((*i)->getName());
			cout << endl;
			temp.push_back(*i);
			indice++;
			i++;
		}
		cin >> choice;
	}
	App*a = temp[choice-1];
	cs();
	cout << "\nApp Info\n\n";
	cout << "App name: " << a->getName() << endl;
	cout << "Cost: " << a->getCost() << endl;
	cout << "Description: " << a->getDescription() << endl;
	cout << "Category: " << a->getCategory() << endl << endl << endl;
	string name,cost,category,description;
	cin.clear();
	cin.ignore();
	cout << "Set new name: ";
	getline(cin,name);
	if(exist(name)){
		cout << "\nThis app already exists\n";
		pause();
		return;
	}
	cout << "Set new cost: ";
	getline(cin,cost);
	cout << "Set new description: ";
	getline(cin,description);
	cout << "Set new description: ";
	getline(cin,category);
	a->setName(name);
	if(atof(cost.c_str()) < 0){
		cout << "\n\nYou cant set a negative cost\n\n";
		pause();
		return;
	}
	a->setCost(atof(cost.c_str()));
	a->setDescription(description);
	a->setCategory(category);
	int ide = a->getId();
	unsigned int i = 0;
	for (i; i < AllTimeApps.size(); i++)
		if (AllTimeApps[i].getId() == ide)
			break;
	BSTItrIn<AppToBst> it(appsBst);
	while (!it.isAtEnd()) {
		if (it.retrieve().id == AllTimeApps[i].getId()) {
			it.retrieve().cost = AllTimeApps[i].getCost();
			it.retrieve().categ = AllTimeApps[i].getCategory();
			it.retrieve().classif = AllTimeApps[i].getClassification();
		}
		it.advance();
	}
	BstReorganize();
}

void AppStore::delHashApps() {
	vector<App*> temp;
	int choice = -1;
	while(choice < 1 || choice > temp.size() + 1){
		cs();
		temp.clear();
		cout << "\n\nApps not on sale\n\n";
		string n;
		int indice = 1;
		tr1::unordered_set<App*>::iterator i = hash.begin();
		while(i != hash.end()){
			cout << indice << " - App Name: " << (*i)->getName() << "  Dev: " << getDevFromApp((*i)->getName());
			cout << endl;
			temp.push_back(*i);
			indice++;
			i++;
		}
		cout << indice << " - Go Back.";
		cin >> choice;
		if(choice == indice) return;
	}
	App*a = temp[choice-1];
	for(int i = 0; i < AllTimeApps.size();i++){
		if(a->getName() == AllTimeApps[i].getName()){
			AllTimeApps[i].setForSale(true);
		}
	}
	temp.erase(temp.begin() + choice - 1);
	tr1::unordered_set<App*> t;
	for(int i = 0; i < temp.size();i++){
		t.insert(temp[i]);
	}
	hash = t;
}
void AppStore::showAllAppsWaitingApproval() const {
	cs();
	if (validation.size() == 0) {
		cout << "There are no Apps awaiting your approval!";
		pause();
		return;
	}
	cout << "                 List of Apps awaiting your approval\n\n\n";
	priority_queue<AppForSubmission> tmp = validation;
	while(!tmp.empty()){
		cout << tmp.top().getApp().getId() << " - " << tmp.top().getApp().getName() << " - "
				<< tmp.top().getApp().getCost() << " - " << tmp.top().getApp().getCategory() << "\n";
		tmp.pop();
	}
	pause();
}






//------------CRUD - Companies--------

bool AppStore::createCompany() {
	string us, pass, nam, add;
	float ni;
	cs();
	cout << "\n\n              Create a new Developer";
	cout << "\n\nUsername:                 ";
	getline(cin,us);
	cout << "\nPassword:                   ";
	getline(cin,pass);;
	cout << "\nName:                       ";
	getline(cin,nam);
	cout << "\nDeveloper:                  ";
	getline(cin,add);
	cout << "\NIF:                         ";
	cin >> ni;
	cin.clear();
	cin.ignore();
	Company final = Company(us, pass, nam, add, ni);
	companies.push_back(final);
	return true;
}

void AppStore::readCompany() {
	cs();
	int index;
	string n;
	cout << "\n\nType the name of the Company you want to read: ";
	getline(cin,n);
	index = findIndexCompany(n);
	Company a = companies[index];
	cout << "Name:          " << a.getName();
	cout << "\nPassword:    " << a.getPw();
	cout << "\nUsername:    " << a.getUser();
	cout << "\nAddress:     " << a.getAddress();
	cout << "\nNIF:         " << a.getNif();

	cout << "\nThis Developer has " << a.getApps().size() << " apps.";

	pause();
}

bool AppStore::updateCompany() {
	int intro = 0;
	int index;
	string n;
	float i;
	cs();
	cout << "\n\nType the name of the Developer you want to update: ";
	getline(cin,n);
	index = findIndexDeveloper(n);
	if (index == -1) {
		cout << "Name does no exist.";
		return false;
	}
	while(intro < 1 || intro > 5) {
		cs();
		cout << "\n\n              What do you want to update?";
		cout << "\n\n1.Name";
		cout << "\n2.Username";
		cout << "\n3.Password";
		cout << "\n4.Address";
		cout << "\n5.NIF";

		cin >> intro;
		cin.clear();
		cin.ignore();
	}
	cs();
	if (intro == 1) {
		cout << "Name: ";
		getline(cin,n);
		companies[index].setName(n);
	}
	else if (intro == 2) {
		cout << "Username: ";
		getline(cin,n);
		companies[index].setUsername(n);
	}
	else if (intro == 3) {
		cout << "Password: ";
		getline(cin,n);
		companies[index].setPw(n);
	}
	else if (intro == 5) {
		cout << "NIF: ";
		cin >> i;
		cin.clear();
		cin.ignore();
		companies[index].setNif(i);
	}
	else if (intro == 4) {
		cout << "Address: ";
		getline(cin,n);
		companies[index].setAddress(n);
	}	return true;
}

bool AppStore::deleteCompany() {
	string n;
	int index;
	cs();
	cout << "\n\n               Delete a Company";
	cout << "\n\nName of the Company to delete: ";
	getline(cin,n);
	index = findIndexCompany(n);
	if (index == -1)
		return false;
	companies.erase(companies.begin() + index);
	return true;
}

//------------CRUD - Developer--------

bool AppStore::createDeveloper() {
	string us, pass, nam, add;
	cs();
	cout << "\n\n              Create a new Developer";
	cout << "\n\nUsername:                 ";
	getline(cin,us);
	cout << "\nPassword:                   ";
	getline(cin,pass);
	cout << "\nName:                       ";
	getline(cin,nam);
	cout << "\nDeveloper:                  ";
	getline(cin,add);
	Developer final = Developer(us, pass, nam, add);
	developers.push_back(final);
	return true;
}

void AppStore::readDeveloper() {
	cs();
	int index;
	string n;
	cout << "\n\nType the name of the Developer you want to read: ";
	getline(cin,n);
	index = findIndexDeveloper(n);
	Developer a = developers[index];
	cout << "Name:          " << a.getName();
	cout << "\nPassword:    " << a.getPw();
	cout << "\nUsername:    " << a.getUser();
	cout << "\nAddress:     " << a.getAddress();

	cout << "\nThis Developer has " << a.getApps().size() << " apps.";

	pause();
}

bool AppStore::updateDeveloper() {
	int intro = 0;
	int index;
	string n;
	cs();
	cout << "\n\nType the name of the Developer you want to update: ";
	getline(cin,n);
	index = findIndexDeveloper(n);
	if (index == -1) {
		cout << "Name does no exist.";
		return false;
	}
	while(intro < 1 || intro > 4) {
		cs();
		cout << "\n\n              What do you want to update?";
		cout << "\n\n1.Name";
		cout << "\n2.Username";
		cout << "\n3.Password";
		cout << "\n4.Address";
		cin >> intro;
		cin.clear();
		cin.ignore();
	}
	cs();
	if (intro == 1) {
		cout << "Name: ";
		getline(cin,n);
		developers[index].setName(n);
	}
	else if (intro == 2) {
		cout << "Username: ";
		getline(cin,n);
		developers[index].setUsername(n);
	}
	else if (intro == 3) {
		cout << "Password: ";
		getline(cin,n);
		developers[index].setPw(n);
	}
	else if (intro == 4) {
		cout << "Address: ";
		getline(cin,n);
		developers[index].setAddress(n);
	}	return true;
}

bool AppStore::deleteDeveloper() {
	string n;
	int index;
	cs();
	cout << "\n\n               Delete a Developer";
	cout << "\n\nName of the Developer to delete: ";
	getline(cin,n);
	index = findIndexDeveloper(n);
	if (index == -1)
		return false;
	developers.erase(developers.begin() + index);
	return true;
}

//Classification

classification::classification(unsigned int i,int st, string c){
	id = i;
	cla = c;
	stars = st;
}

unsigned int classification::getId(){
	return id;
}

string classification::getCla(){
	return cla;
}

void classification::setCla(string c){
	cla = c;
}

int classification::getStars(){
	return stars;
}

void classification::setStars(int set){
	stars = set;
}

void setStars();

//User

User::User(Client*client){
	Developer*dev=0;
	Company*com=0;
	a=client;
	b=dev;
	c=com;
	type = "client";
}

User::User(Developer*developer){
	Client*cli =0;
	Company*com =0;
	a=cli;
	b=developer;
	c=com;
	type="developer";
}

User::User(Company*company){
	Client*cli = 0;
	Developer*dev = 0;
	a=cli;
	b=dev;
	c=company;
	type = "company";
}

User::User(){
	Client*cli = 0;
	Developer*dev = 0;
	Company*com = 0;
	a=cli;
	b=dev;
	c=com;
	type = "admin";
}

User::~User(){

}

void AppStore::setAppClassifications() {
	for (unsigned int i = 0; i < AllTimeApps.size(); i++)
		AllTimeApps[i].setClassification(average(&AllTimeApps[i],clients));
	BstReorganize();
}

bool App::operator==(const App a) const {
	return (id == a.getId());
}

bool App::operator <(const App a) const {
	if (a.getClassification() == classification)
		if (a.getCost() == cost)
			if (a.getCategory() == category)
				return false;
			else
				return (category > a.category);
		else
			return (cost < a.getCost());
	else
		return (classification > a.getClassification());
	return false;
}

bool AppToBst::operator <(const AppToBst a) const {
	if (a.classif == classif)
		if (a.cost == cost)
			if (a.categ == categ)
				return false;
			else
				return (categ > a.categ);
		else
			return (cost < a.cost);
	else
		return (classif > a.classif);
	return false;
}

void AppStore::BstReorganize() {
	BSTItrIn<AppToBst> it(appsBst);
	if (it.isAtEnd())
		return;
	BST<AppToBst> temp(it.retrieve());
	while (!it.isAtEnd()) {
		temp.insert(it.retrieve());
		it.advance();
	}
	appsBst = temp;
}

void AppStore::BstRemove(int id) {
	BSTItrIn<AppToBst> it(appsBst);
	BST<AppToBst> temp(it.retrieve());
	it.advance();
	while (!it.isAtEnd()) {
		if (it.retrieve().id != id)
			temp.insert(it.retrieve());
		it.advance();
	}
	appsBst = temp;
}

App AppStore::getApp(int id) {
	for (unsigned int i = 0; i < AllTimeApps.size(); i++)
		if (AllTimeApps[i].getId() == id)
			return AllTimeApps[i];

	return App();
}

void AppStore::showTop10() {
	cs();
	cout << "                Top 10 Apps\n\n";
	int i = 0;
	int index = 1;
	BSTItrIn<AppToBst> it(appsBst);
	while ((index < 10) && (!it.isAtEnd())) {
		if (it.retrieve().id != -1) {
			App t = getApp(it.retrieve().id);
			cout << index << " - " << t.getName() << " - " << t.getClassification() << " - "
					<< "Costs: " << t.getCost() << "\n";
			index++;
		}
		it.advance();
		i++;
	}
	if (i == 0)
		cout << "No Apps available\n\n";
	return;
}

void AppStore::addToBst() {
	cs();
	unsigned int counter = 0;
	int choice;
	unsigned int i;
	do {
		cout << "                Add Existing App to Bst\n\n\n";
		for (i = 0; i < AllTimeApps.size(); i++) {
			bool temp = false;
			BSTItrIn<AppToBst>it(appsBst);
			while (!it.isAtEnd()) {
				if (it.retrieve().id == AllTimeApps[i].getId()) {
					temp = true;
					break;
				}
				it.advance();
			}
			if (!temp) {
				counter++;
				cout << counter << " - " << AllTimeApps[i].getName() << "\n";
			}
		}
		if (counter == 0) {
			cout << "All existing Apps are in the BST.\n\n";
			system("pause");
			return;
		}
		else
			cin >> choice;
	} while ((choice > counter) && (choice < 0));
	int counter2 = 0;
	for (i = 0; i < AllTimeApps.size(); i++) {
		bool temp = false;
		BSTItrIn<AppToBst>it(appsBst);
		while (!it.isAtEnd()) {
			if (it.retrieve().id == AllTimeApps[i].getId()) {
				temp = true;
				break;
			}
			it.advance();
		}
		if (!temp) {
			counter2++;
		}
		if (counter2 == counter) break;
	}
	if (choice != 0) {
		appsBst.insert(AppToBst(AllTimeApps[i].getId(), AllTimeApps[i].getClassification(), AllTimeApps[i].getCost(),
				AllTimeApps[i].getCategory()));
		pause();
	}
}

void AppStore::readBst() {
	cs();
	cout << "                App Ranking\n\n";
	int index = 1;
	BSTItrIn<AppToBst> it(appsBst);
	while (!it.isAtEnd()) {
		if (it.retrieve().id != -1) {
			App t = getApp(it.retrieve().id);
			cout << index << " - " << t.getName() << " - " << t.getClassification() <<" - "
					<< "Costs: " << t.getCost() << "\n";
			index++;
		}
		it.advance();
	}
	if (index == 1)
		cout << "No Apps available\n\n";
	pause();
	return;
}

void AppStore::removeFromBst() {
	cs();
	cout << "                App Ranking - Choose an App to remove\n\n";
	int index = 1;
	BSTItrIn<AppToBst> it(appsBst);
	while (!it.isAtEnd()) {
		if (it.retrieve().id != -1) {
			App t = getApp(it.retrieve().id);
			cout << index << " - " << t.getName() << " - " << t.getClassification() << "\n";
			index++;
		}
		it.advance();
	}
	if (index == 1) {
		cout << "No Apps available to remove\n\n";
		pause();
		return;
	}
	int choice;
	do {
		cin >> choice;
		if (choice == 0)
			return;
		else if ((choice > 0) && (choice < index)) {
			BSTItrIn<AppToBst> it(appsBst);
			for (unsigned int i = 1; i < choice; i++, it.advance());
			appsBst.remove(it.retrieve());
		}
	} while ((choice < 1) && (choice >= index));
	return;
}

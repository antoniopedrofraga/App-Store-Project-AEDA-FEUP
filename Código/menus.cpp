#include "menus.h"

/**defgroup Menus Menus
 * @{
 * Controls the menus and the interface
 */

/**
 * @brief Exit function
 */
void Exit(void ){
	cs();
	cout << "\nExiting...\n";
	Sleep(2000);
}

/**
 * @brief controls the password access
 *
 * @return password
 */
string askpassword(){
	cs();
	cout << endl << "[ESC] to go back\n" << endl << "Password: ";
	unsigned char a;
	string password = "";
	a = _getch();
	while (a != 13){
		if (a == 27){
			cs();
			cin.clear();
			return "";
		}
		if (a == 0 || a == 0xE0){
			a = _getch();
		}
		else{
			if (a != 8) {
				password.push_back(a);
				cout << '*';
			}
			else if (a == 8){
				cs();
				if (password.length() > 0){
					password.erase(password.begin() + password.size()-1); //apaga uma caracter da string caso backspace
				}
				cout << endl << "[ESC] to back\n" << endl << "Password: ";
				for (int unsigned b = 0; b < password.length(); b++){ //display dos asteriscos
					cout << "*";
				}
			}
		}
		a = _getch();
	}
	cin.clear();
	return password;
}

/**
 * @brief clears screen
 */
void cs() { system("CLS"); }

/**
 * @brief pauses the program
 */
void pause() {
	cout << "\n\nPress any key to continue...\n";
	_getch();
}

/**
 * @brief Shows the first screen
 */
int firstScreen() {
	cs();
	cout << "\n\n" << "AppStore\nCreated by: \nLuis Oliveira,\nPedro Fraga,\nJoao Nogueira\n";
	cout << "\n\n" << "Menu:\n" << "\n1.Sign In" << "\n2.Sign Up" << "\n3.Exit\n";
	int choice;
	cin >> choice;
	return choice;
}

/**
 * @brief Receives a string and checks if it is equal to <-
 *
 * @param a string to check
 *
 * @return Returns true if equal and false otherwise
 */
bool back(string a){
	if(a=="<-"){
		cout << "\nGoing back\n";
		Sleep(1000);
		return true;
	}else{
		return false;
	}
}

/**
 * @brief Receives an int and checks if it is equal to <-
 *
 * @param a int to check
 *
 * @return Returns true if equal and false otherwise
 */
bool back(int a){
	if(a=='<-'){
		cout << "\nGoing back\n";
		Sleep(1000);
		return true;
	}else{
		return false;
	}
}

/**
 * @brief Controls the sign up menu
 *
 * @param apps AppStore
 *
 * @return Returns 1
 */
int signUpMenu(AppStore &apps){
	int accounttype;
	string username;
	string password;
	string name;
	string address;
	bool test;
	int nif;
	do{
		cs();
		cout << "\nType of account you wish to create:\n\n1.Client\n2.Developer\n3.Go Back\n\n";
		cin >> accounttype;
		if(accounttype==3){
			return 1;
		}
		if(accounttype!=1 && accounttype!=2 && accounttype!=3){
			cout << "\n Your answer must range from 1 to 3";
		}
	}while(accounttype!=1 && accounttype!=2 && accounttype!=3);
	cin.clear();
	cin.ignore();
	test = false;
	cout << "\n\nAnytime you can input \"<-\" to go back\n\n";
	pause();
	do{
		cs();
		if(test){cout << "\nthis username already exists, please try again\n\n";}
		cout << "\n\nUsername: ";
		getline(cin,username);
		if(back(username)){
			return 1;
		}
		test = checkusername(username,apps);
	}while(test);
	cin.clear();
	cout << "Password: ";
	getline(cin,password);
	if(back(password)){
		return 1;
	}
	cout << "Full Name: ";
	getline(cin,name);
	if(back(name)){
		return 1;
	}
	if(accounttype==1){
		Client newc = Client(username,password,name);
		apps.clients.push_back(newc);
	}else if(accounttype==2){
		string c;
		cout << "Address: ";
		getline(cin, address);
		if(back(address)){
			return 1;
		}
		cout << "\nAre you a company? y/n\n";
		cin >> c;
		if(c=="y"){
			cout << "NIF: ";
			cin >> nif;
			if(back(nif)){
				return 1;
			}
			Company c = Company(username,password,name,address,nif);
			apps.companies.push_back(c);
		}else if(c=="n"){
			Developer d = Developer(username,password,name,address);
			apps.developers.push_back(d);
		}else{
			throw OutOfBoolRange(c);
		}
	}
	cout << "\nYou just created your account successfully\n";
	Sleep(1000);
	return 1;
}

/**
 * @brief Controls the login menu
 *
 * @param apps AppStore
 *
 * @return returns 0
 */
int loginMenu(AppStore &apps) {
	string username;
	string password;
	for(unsigned int a = 0;a < 3;a++){
		cs();
		cout << "\nUsername: ";
		cin >> username;
		cout << "\nPassword: ";
		password = askpassword();
		if(password == ""){
			return 0;
		}
		int check = checkUser(username,password,apps);
		if(check == 0){
			cout << "\n\nWARNING : there is not such user or pw, " << 3-a-1 << " of 3 chances left\n";
			pause();
			if(3-a-1 == 0){
				return 0;
			}
		}else{
			a = 'GetOutOfFor';
			return check;
		}
	}
	return 0;
}

/**
 * @brief Checks the username
 *
 * @param username the username to check
 * @param apps with the info
 *
 * @return returns true/false depending on que check of the username
 */
bool checkusername(string username,AppStore &apps){
	for(int a = 0; a < apps.clients.size();a++){
		if(apps.clients[a].getUser() == username)
			return true;
	}
	for(int a = 0; a < apps.developers.size();a++){
		if(apps.developers[a].getUser() == username)
			return true;
	}

	for(int a = 0; a < apps.companies.size();a++){
		if(apps.companies[a].getUser() == username)
			return true;
	}

	if("admin" == username)
		return true;

	return false;
}

/**
 * @brief checks if the app is owned
 *
 * @param App* myapp
 * @param apps AppStore
 *
 * @return Returns true or false depending on if it is owned
 */
bool owned(App*myapp,AppStore*apps){
	int size2 = apps->myuser.a->getApps().size();
	for(int a = 0; a < size2;a++){
		if(myapp->getId() == apps->myuser.a->getApps()[a]->getId()){
			return true;
		}
	}
	return false;
}

/**
 * @brief Checks user for the right password
 *
 * @param username name of the user
 * @param password password of theuser
 * @param apps Apps
 *
 * @return returns 0-2
 */
int checkUser(string username, string password, AppStore &apps){
	for(int a = 0; a < apps.clients.size();a++){
		if(apps.clients[a].getUser() == username)
			if(apps.clients[a].getPw() == password){
				apps.myuser = User(&apps.clients[a]);
				return 1;
			}
	}
	for(int a = 0; a < apps.developers.size();a++){
		if(apps.developers[a].getUser() == username)
			if(apps.developers[a].getPw() == password){
				apps.myuser = User(&apps.developers[a]);
				return 2;
			}
	}
	for(int a = 0; a < apps.companies.size();a++){
		if(apps.companies[a].getUser() == username)
			if(apps.companies[a].getPw() == password){
				apps.myuser = User(&apps.companies[a]);
				return 2;
			}
	}

	if("admin" == username)
		if("admin" == password)
			return 3;
	return 0;
}

/**
 * @brief gets the average of an App's classification
 *
 * @param *a App
 * @param clients vector of the clients
 *
 * @return returns the average classification
 */
float average(App*a, vector<Client> clients) {
	int counter=0;
	int average = 0;
	int choice;
	char yn;
	int id = a->getId();
	vector<classification> fag;
	vector<Client> evenmorefag;
	for(int i = 0; i < clients.size(); i++){
		for(int a = 0; a < clients[i].getClass().size();a++){
			if(clients[i].getClass()[a].getId()==id){
				counter++;
				average = average + clients[i].getClass()[a].getStars();
				fag.push_back(clients[i].getClass()[a]);
				evenmorefag.push_back(clients[i]);
			}
		}
	}
	float temp = average/(float)counter;
	if (counter == 0)
		return -1;
	else
		return temp;
}

/**
 * @brief shows somw comments and classifications of the app
 *
 * @param *a App
 * @param apps AppStore
 *
 * @return Returns 0
 */
int appInfo(App*a, AppStore & apps){
	if(!a->getForSale()){
		cout << "\n\nThis app is not for sale\n\n";
		pause();
		return 0;
	}
	srand (time(NULL));
	int counter=0;
	int average = 0;
	int random3 = -1;
	int random2 = -1;
	int random1 = -1;
	int choice;
	char yn;
	int id = a->getId();
	vector<classification> fag;
	vector<Client> evenmorefag;
	for(int i = 0; i < apps.clients.size(); i++){
		for(int a = 0; a < apps.clients[i].getClass().size();a++){
			if(apps.clients[i].getClass()[a].getId()==id){
				counter++;
				average = average + apps.clients[i].getClass()[a].getStars();
				fag.push_back(apps.clients[i].getClass()[a]);
				evenmorefag.push_back(apps.clients[i]);
			}
		}
	}
	if(counter>=1){
		random1 = rand() % counter + 0;
		if(counter >= 2){
			random2 = rand() % counter + 0;
			do{
				random2 = rand() % counter + 0;
			}while(random1==random2);
			if(counter >= 3){
				random3 = rand() % counter + 0;
				do{
					random3 = rand() % counter + 0;
				}while(random1==random3 || random2==random3);
			}
		}
	}
	cs();
	cout << endl << a->getName() << "\t\t\tCost: " << a->getCost() << "$";
	cout << endl << endl << "Dev description: " << a->getDescription();
	if(average!=0){
		cout << endl << endl << "Average Classification: ";
		cout << average/counter << endl;
	}else{
		cout << "\n\nTheres no classifications yet!\n\n";
	}
	if(counter > 0){
		cout << "\nSome coments:\n\n";
		for(int i = 0; i < counter; i++){
			if(i==random1 || i == random2 || i == random3){
				cout << evenmorefag[i].getName() << " said \"" << fag[i].getCla() << "\" and gave it " << fag[i].getStars() << " stars." << endl;
			}
		}
	}
	for(int i = 0; i < apps.myuser.a->getCart().size(); i++){
		if(apps.myuser.a->getCart()[i] == a){
			cout << "\n\nYou already have this app on your cart\n\n";
			pause();
			return 0;
		}
	}
	if(!owned(a,&apps)){
		cout << "\n\n1. Add to cart\n2. Go Back\n\n";
		cin >> choice;
	}else{
		cout << "\n\n[YOU OWN THIS APP]" << endl;
		pause();
		return 0;
	}
	if(choice == 2){
		return 0;
	}else if(choice==1){
		apps.myuser.a->addToCart(a);
		cout << "\n\nYou just added this app to your cart\n\n";
	}
}

/**
 * @brieb shows and controls the menu of the clients purchase
 *
 * @param apps AppStore
 *
 * @return Returns 1
 */
int buyApps(AppStore &apps){
	cout.precision(3);
	int choice;
	int size = apps.AllTimeApps.size();
	int size2 = apps.myuser.a->getApps().size();
	do{
		do{
			cs();
			cin.clear();
			cout << endl << apps.myuser.a->getName() << "\n\nBuy Apps\n\n";
			for(int i = 0; i < size ; i++ ){
				if(apps.AllTimeApps[i].getForSale()){
					cout << i+1 << ". " << apps.AllTimeApps[i].getName() << "\t\tCost: " << apps.AllTimeApps[i].getCost() << "$";
					for(int a = 0; a < size2;a++){
						if(apps.AllTimeApps[i].getId() == apps.myuser.a->getApps()[a]->getId()){
							cout << " [OWNED]";
						}
					}
					cout << endl;
				}
			}
			cout << size + 1 << ". Go Back\n\n";
			cin >> choice;
			if(choice == size + 1){
				return 1;
			}
		}while(choice <= 0 || choice > size);
		choice --;
		appInfo(&apps.AllTimeApps[choice],apps);
	}while(true);
	return 1;
}

/**
 * @brief Controls the menu of a clients Inventory
 *
 * @param apps AppStore
 *
 * @return Returns
 */
int myApps(AppStore &apps){
	cs();
	string text;
	int stars;
	if(!apps.myuser.a->getApps().size()){
		cout << "\n\nYou have no Apps, just go search for some\n\n";
		pause();
		return 0;
	}
	string st;
	int choice = -1;
	do{
		cout << "\n\nThese are your Apps, if you want to classify them just choose a number, if you\n\nIf an App is classified you can classify it again!\n\n";
		for(int a = 0; a < apps.myuser.a->getApps().size(); a++){
			cout << a+1 << ". " << apps.myuser.a->getApps()[a]->getName();
			for(int i = 0; i < apps.myuser.a->getClass().size(); i++){
				if(apps.myuser.a->getClass()[i].getId() == apps.myuser.a->getApps()[a]->getId()){
					cout << "\t";
					for(int e = 0; e < apps.myuser.a->getClass()[i].getStars(); e++){
						cout << "*";
					}
					cout << endl;
					cout << "\nMy Description about " << apps.myuser.a->getApps()[a]->getName() << ": " << apps.myuser.a->getClass()[i].getCla();
				}
			}
			cout << endl << endl;
		}
		cout << apps.myuser.a->getApps().size() + 1 << ". Go Back\n\n";
		cin >> choice;
		if(choice == apps.myuser.a->getApps().size()+1){
			choice = -1;
			cin.clear();
			cin.ignore();
			return 0;
		}
	}while(choice < 0 || choice > apps.myuser.a->getApps().size());
	cin.clear();
	cin.ignore();
	stars = -1;
	while(stars < 0 || stars > 5){
		cs();
		if(stars!=-1){
			cout << "\nWarning your range is from 0 to 5\n";
		}
		cout << "\n\nClassify " << apps.myuser.a->getApps()[choice - 1]->getName() << " from 0 to 5: ";
		cin >> stars;
		cin.clear();
		cin.ignore();
	}
	cout << "\nWrite something about " <<  apps.myuser.a->getApps()[choice - 1]->getName() << ": " << endl << endl << endl;
	getline(cin,
			text);
	apps.myuser.a->pushBackDescription(apps.myuser.a->getApps()[choice - 1]->getId(), stars ,text);
}

/**
 * @brief Buys all of the items in cart
 *
 * @param AppStore
 *
 * @return Returns
 */
int buyall(AppStore &apps){
	string a;
	string disc;
	bool discount = false;
	float money = 0;
	int size = apps.myuser.a->getCart().size();
	do{
		cs();
		cout << "\n\nDo you have a discount code? y/n\n\n";
		getline(cin , a);
	}while(a != "y" && a != "n");
	if(a == "n"){
		for(int i = 0; i < apps.myuser.a->getCart().size() ; i){
			money = money + apps.myuser.a->getCart()[i]->getCost();
			cout << "1";
			if(apps.myuser.a->getMoney() - apps.myuser.a->getCart()[i]->getCost() < 0){
				cs();
				cout << "\n\nYou dont have enough money to buy all apps\n\n";
				pause();
				return 0;
			}
			App*a = apps.myuser.a->getCart()[i];
			Sale sale2;
			sale2.setApp(a);
			sale2.setBuyer(apps.myuser.a);
			apps.myuser.a->pushBackApp(apps.myuser.a->getCart()[i]);
			apps.myuser.a->setMoney(apps.myuser.a->getMoney() - apps.myuser.a->getCart()[i]->getCost());
			for(int a = 0; a < apps.developers.size();a++){
				for(int b = 0; b < apps.developers[a].getApps().size() ; b++){
					if(apps.developers[a].getApps()[b] == apps.myuser.a->getCart()[i]){
						apps.sales.push_back(sale2);
						apps.developers[a].setMoney(apps.developers[a].getMoney() + apps.myuser.a->getCart()[i]->getCost()*0.80);
					}
				}
			}
			cout << "4";
			for(int a = 0; a < apps.companies.size();a++){
				for(int b = 0; b < apps.companies[a].getApps().size() ; b++){
					if(apps.companies[a].getApps()[b] == apps.myuser.a->getCart()[i]){
						apps.sales.push_back(sale2);
						apps.companies[a].setMoney(apps.companies[a].getMoney() + apps.myuser.a->getCart()[i]->getCost()*0.80);
					}
				}
			}
			cout << "5";
			apps.myuser.a->cart.erase(apps.myuser.a->cart.begin());
			cout << apps.myuser.a->cart.size();
		}
	}
	if(a == "y"){
		cout << "Insert your discount code: ";
		getline(cin,disc);
		for(int i = 0; i < apps.codes.size(); i++){
			if(apps.codes[i]==disc) discount = true;
		}
		if(!discount){
			cs();
			cout << "\n\nIts not a valid code \n\n";
			Sleep(1000);
			return 0;
		}
		for(int i = 0; i < apps.myuser.a->getCart().size() ; i){
			money = money + apps.myuser.a->getCart()[i]->getCost()*0.95;
			cout << "1";
			if(apps.myuser.a->getMoney() - apps.myuser.a->getCart()[i]->getCost()*0.95 < 0){
				cs();
				cout << "\n\nYou dont have enough mone to buy all apps\n\n";
				pause();
				return 0;
			}
			App*a = apps.myuser.a->getCart()[i];
			Sale sale2;
			sale2.setApp(a);
			sale2.setBuyer(apps.myuser.a);
			apps.myuser.a->setMoney(apps.myuser.a->getMoney() - apps.myuser.a->getCart()[i]->getCost()*0.95);
			for(int a = 0; a < apps.developers.size();a++){
				for(int b = 0; b < apps.developers[a].getApps().size() ; b++){
					if(apps.developers[a].getApps()[b] == apps.myuser.a->getCart()[i]){
						apps.sales.push_back(sale2);
						apps.developers[a].setMoney(apps.developers[a].getMoney() + apps.myuser.a->getCart()[i]->getCost()*0.95*0.80);
					}
				}
			}
			for(int a = 0; a < apps.companies.size();a++){
				for(int b = 0; b < apps.companies[a].getApps().size() ; b++){
					if(apps.companies[a].getApps()[b] == apps.myuser.a->getCart()[i]){
						apps.sales.push_back(sale2);
						apps.companies[a].setMoney(apps.companies[a].getMoney() + apps.myuser.a->getCart()[i]->getCost()*0.95*0.80);
					}
				}
			}
			cs();
			cout << "\n\nYou just bought " << apps.myuser.a->cart[0]->getName() << "\n\n";
			pause();
			apps.myuser.a->cart.erase(apps.myuser.a->cart.begin());
		}
	}
	return 0;
}

/**
 * @brief Controls the Clients Menu
 *
 * @param apps AppStore
 *
 * @return returns 0
 */
int ClientMenu(AppStore &apps){
	int choice = -1;
	int mychoice = -1;
	int cartsize;
	string pw0;
	cout.precision(3);
	bool exit = false;
	do{
		do{
			cs();
			cout << "\nClient Menu\n\n" << apps.myuser.a->getName() << "\t\t" << apps.myuser.a->getMoney() << "$";
			if(apps.myuser.a->getCart().size()){
				cout << "\n\nCart: " << apps.myuser.a->getCart().size() << " items\n\n";
			}else{
				cout << "\n\nCart is empty\n\n";
			}
			cout << "\n\n1.Search Apps\n2.My Cart\n3.My Apps / Classify Apps\n4.Change password\n5.Add money to your account\n6.Top 10 Apps\n7.Log Out\n\n";
			cin >> choice;
			if(choice=='.'){
				choice = -1;
			}
		}while(choice <= 0 || choice > 7);
		cin.clear();
		cin.ignore();
		switch(choice){
		case 1:
			buyApps(apps);
			break;
		case 2:
			cartsize = apps.myuser.a->getCart().size();
			do{
				cs();
				cout << "\n\nMy Cart\n\nType on of them if you want remove it from your cart\n\n";
				if(!cartsize){
					cout << "\n\nYou have no apps on your cart\n\n";
					pause();
					mychoice = 3;
					break;
				}else{
					for(int i = 0; i < apps.myuser.a->getCart().size();i++){
						cout << i+1 << "." << apps.myuser.a->getCart()[i]->getName() << endl;
					}
					cout << apps.myuser.a->getCart().size() + 1 << ".Buy All" << endl << endl;
					cout << apps.myuser.a->getCart().size() + 2 << ".Go Back" << endl << endl;
					cin >> mychoice;}
			}while( mychoice <= 0 || mychoice > (apps.myuser.a->getCart().size() + 2));
			mychoice--;
			if(cartsize){
				if(mychoice == (apps.myuser.a->getCart().size() + 1)){
					break;
				}
				if(mychoice == apps.myuser.a->getCart().size()) buyall(apps);
				else apps.myuser.a->eraseCartApp(mychoice);
			}
			break;
		case 3:
			if(myApps(apps)==0)
				choice = -1;
			break;
		case 4:
			cs();
			cout << "\nYour password: ";
			getline(cin,pw0);
			if(pw0==apps.myuser.a->getPw()){
				string pw2;
				string pw3;
				cout << "\nNew Password: ";
				getline(cin,pw2);
				cout << "\n\nYou changed your password successfully";
				apps.myuser.a->setPw(pw2);
				Sleep(750);
			}else{
				cout << "\n\nThat is not your password";
				Sleep(750);
			}
			break;
		case 5:
			float m;
			cs();
			cout << "\nDear " << apps.myuser.a->getName() << endl;
			cout << "\n\nHow much money do you want to add to your account? ";
			cin >> m;
			if(m > 0){
				apps.myuser.a->setMoney(apps.myuser.a->getMoney()+m);
				cout << endl << endl << "You just add " << m << " $ to your account\n\n";
				Sleep(750);
			}else{
				cout << "\n\nYou cant add negative money\n\n";
				Sleep(1000);
			}
			break;
		case 6:
			top10menu(apps);
			break;
		case 7:
			return -1;
			break;
		}
	}while(!exit);
}

//DEV MENU ---------

/**
 * @brief shows info of an app
 *
 * @param pos position
 * @param apps AppStore
 *
 * @return returns 0
 */
int appinfo(int pos,AppStore &apps){
	string address;
	string appname;
	string appcost;
	string appcat;
	string appdesc;
	float cost;
	int choice;
	while(true){
		cs();
		if(apps.myuser.type == "developer" ){
			cout << endl << apps.myuser.b->getApps()[pos]->getName() << endl;
			cout << endl << "My description: " << apps.myuser.b->getApps()[pos]->getDescription() << endl;
			cout << endl << "Cost:  " << apps.myuser.b->getApps()[pos]->getCost() << endl;
			cout << endl << "category:  " << apps.myuser.b->getApps()[pos]->getCategory() << endl;
			cout << endl;
			if(apps.myuser.b->getApps()[pos]->getForSale()){
				cout << "This app is for sale";
			}else{
				cout << "This app is not for sale";
			}
			cout << endl;

		}else{
			cout << endl << apps.myuser.c->getApps()[pos]->getName() << endl;
			cout << endl << "My description: " << apps.myuser.c->getApps()[pos]->getDescription() << endl;
			cout << endl << "Cost:  " << apps.myuser.c->getApps()[pos]->getCost() << endl;
			cout << endl << "category:  " << apps.myuser.c->getApps()[pos]->getCategory() << endl << endl;
			if(apps.myuser.c->getApps()[pos]->getForSale()){
				cout << "This app is for sale";
			}else{
				cout << "This app is not for sale";
			}
			cout << endl;
		}
		cout << "\n1.Update App\n2.Change Sale status\n3.Go back\n\n";
		cin >> choice;
		if(choice == 3){
			return 1;
		}else if(choice == 2){
			if(apps.myuser.type == "company")
				if(apps.myuser.c->getApps()[pos]->getForSale()){
					apps.myuser.c->apps[pos]->setForSale(false);
					apps.hashInsert(apps.myuser.c->getApps()[pos]);
				}else{
					apps.myuser.c->apps[pos]->setForSale(true);
					apps.hashRemove(apps.myuser.c->getApps()[pos]);
				}
			else
				if(apps.myuser.b->getApps()[pos]->getForSale()){
					apps.myuser.b->apps[pos]->setForSale(false);
					apps.hashInsert(apps.myuser.b->getApps()[pos]);
				}else{
					apps.myuser.b->apps[pos]->setForSale(true);
					apps.hashRemove(apps.myuser.b->getApps()[pos]);
				}

			cs();
			cout << endl << endl << "Sale status was changed";
			Sleep(750);
			return 1;
		}else if(choice == 1){
			cs();
			cout << "\nYou can input '<-' to go back\n";
			cout << "\n\nApp Name: ";
			getline(cin,appname);
			if(appname=="<-") return 1;
			cout << "\n\nApp Cost: ";
			getline(cin,appcost);
			if(appcost=="<-") return 1;
			cout << "\n\nApp Category: ";
			getline(cin,appcat);
			if(appcat=="<-") return 1;
			cout << "\n\nYour App Description: ";
			getline(cin,appdesc);
			if(appdesc=="<-") return 1;
			cost = atof(appcost.c_str());
			if(apps.myuser.type ==  "developer"){
				apps.myuser.b->apps[pos]->setName(appname);
				apps.myuser.b->apps[pos]->setCost(cost);
				apps.myuser.b->apps[pos]->setDescription(appdesc);
				apps.myuser.b->apps[pos]->setCategory(appcat);
				unsigned int i;
				for (i = 0; i < apps.AllTimeApps.size(); i++) {
					if (apps.AllTimeApps[i].getId() == apps.myuser.b->apps[pos]->getId())
						break;
				}
				BSTItrIn<AppToBst> it(apps.appsBst);
				while (!it.isAtEnd()) {
					if (it.retrieve().id == apps.AllTimeApps[i].getId()) {
						it.retrieve().cost = apps.AllTimeApps[i].getCost();
						it.retrieve().categ = apps.AllTimeApps[i].getCategory();
						it.retrieve().classif = apps.AllTimeApps[i].getClassification();
					}
					it.advance();
				}
				apps.BstReorganize();
			}else{
				apps.myuser.c->apps[pos]->setName(appname);
				apps.myuser.c->apps[pos]->setCost(cost);
				apps.myuser.c->apps[pos]->setDescription(appdesc);
				apps.myuser.c->apps[pos]->setCategory(appcat);
				unsigned int i;
				for (i = 0; i < apps.AllTimeApps.size(); i++) {
					if (apps.AllTimeApps[i].getId() == apps.myuser.b->apps[pos]->getId())
						break;
				}
				BSTItrIn<AppToBst> it(apps.appsBst);
				while (!it.isAtEnd()) {
					if (it.retrieve().id == apps.AllTimeApps[i].getId()) {
						it.retrieve().cost = apps.AllTimeApps[i].getCost();
						it.retrieve().categ = apps.AllTimeApps[i].getCategory();
						it.retrieve().classif = apps.AllTimeApps[i].getClassification();
					}
					it.advance();
				}
				apps.BstReorganize();
			}
			cs();
			cout << "\n\nApp was changed successfully\n\n";
			Sleep(750);
			return 1;
		}
	}
}

/**
 * @brief Controls Edition of Apps in queue
 *
 * @param pos position
 * @param apps AppStore
 * @param a App For Submission
 *
 * @return returns 0
 */
int waitingappinfo(int pos,AppStore &apps,AppForSubmission a){
	string address;
	string appname;
	string appcost;
	string appcat;
	string appdesc;
	float cost;
	int choice;
	while(true){
		cs();
		cout << endl << a.getApp().getName() << endl;
		cout << endl << "My description: " << a.getApp().getDescription() << endl;
		cout << endl << "Cost:  " << a.getApp().getCost() << endl;
		cout << endl << "category:  " << a.getApp().getCategory() << endl << endl;
		cout << endl;

		//------------
		cout << "\n1.Update App\n2.Remove from waiting approval list\n3.Go back\n\n";
		cin >> choice;
		if(choice == 3){
			return 1;
		}else if(choice == 2){
			priority_queue<AppForSubmission> foo = apps.getValidation();
			priority_queue<AppForSubmission> set;
			while(!foo.empty()){
				if(a.getApp().getId() != foo.top().getApp().getId())
					set.push(foo.top());
				foo.pop();
			}
			apps.setValidation(set);
			cs();
			cout << endl << endl << "Removed from waiting approval list";
			Sleep(750);
			return 1;
		}else if(choice == 1){
			cs();
			cin.clear();
			cin.ignore();
			cout << "\nYou can input '<-' to go back\n";
			cout << "\n\nApp Name: ";
			getline(cin,appname);
			if(appname=="<-") return 1;
			cout << "\n\nApp Cost: ";
			getline(cin,appcost);
			if(appcost=="<-") return 1;
			cout << "\n\nApp Category: ";
			getline(cin,appcat);
			if(appcat=="<-") return 1;
			cout << "\n\nYour App Description: ";
			getline(cin,appdesc);
			if(appdesc=="<-") return 1;
			cost = atof(appcost.c_str());
			a.setApp(appname,cost,appcat,appdesc);
			priority_queue<AppForSubmission> foo = apps.getValidation();
			priority_queue<AppForSubmission> set;
			while(!foo.empty()){
				if(a.getApp().getId() != foo.top().getApp().getId())
					set.push(foo.top());
				else
					set.push(a);
				foo.pop();
			}
			apps.setValidation(set);
			cs();
			cout << "\n\nApp was changed successfully\n\n";
			Sleep(750);
			return 1;
		}
	}
}

/**
 * @brief Shows 1 apps info
 *
 * @param apps AppStore
 *
 * @return returns 1
 */
int showapps(AppStore &apps){
	int choice = -1;
	int size = 0;
	string type = apps.myuser.type;
	int a = 0;
	if(type=="developer")
		size = apps.myuser.b->apps.size();
	else
		size = apps.myuser.c->apps.size();
	if(!size){
		cs();
		cout << "\n\nYou dont have any app published!\n\n";
		pause();
		return 1;
	}
	do{
		cs();
		cout << "\n\nMy Apps\n\nType one of them if you want to edit it, or if you want a detailed description\n\n";
		for(int i = 0;i<size;i++){
			if(type == "developer")
				cout << i+1 << "." << apps.myuser.b->apps[i]->getName() << endl;
			else
				cout << i+1 << "." << apps.myuser.c->apps[i]->getName() << endl;
		}
		cout << size + 1 << "." << "Go Back\n\n";
		cin >> choice;
		if(choice  == size + 1){
			return 1;
		}
	}while(choice <= 0 || choice > size);
	choice --;
	appinfo(choice,apps);
	return 1;
}


/**
 * @brief List Apps Awaiting for Validation on screen
 *
 * @param apps AppStore
 */
int showAppsAwatingValidation(AppStore &apps){
	int choice = -1;
	vector<AppForSubmission> vec;
	if(apps.myuser.type == "company"){
		priority_queue<AppForSubmission> foo = apps.getValidation();
		while(!foo.empty()){
			if(apps.myuser.c->getUser() == foo.top().getUsername())
				vec.push_back(foo.top());
			foo.pop();
		}
	}else{
		priority_queue<AppForSubmission> foo = apps.getValidation();
		while(!foo.empty()){
			if(apps.myuser.b->getUser() == foo.top().getUsername())
				vec.push_back(foo.top());
			foo.pop();
		}
	}

	if(vec.size() == 0){
		cs();
		cout << "\n\nYou dont have any apps awaiting approval!\n\n";
		pause();
		return 1;
	}
	do{
		cs();
		cout << "\n\nMy Apps awaiting approval\n\nType one of them if you want to edit it, or if you want a detailed description\n\n";
		for(int i = 0;i<vec.size();i++)
			cout << i+1 << "." << vec[i].getApp().getName() << endl;
		cout << vec.size() + 1 << "." << "Go Back\n\n";
		cin >> choice;
		if(choice  == vec.size() + 1){
			return 1;
		}
	}while(choice <= 0 || choice > vec.size());
	choice --;
	waitingappinfo(choice,apps,vec[choice]);
	return 1;
}

/**
 * @brief Dev Menu
 *
 * @param apps AppStore
 *
 */
int DevMenu(AppStore &apps){
	int choice=-1;
	string pw;
	string pw1;
	string address;
	string appname;
	string appcost;
	string appcat;
	string appdesc;
	int y, m, d, h, min;
	App myapp;
	float cost;
	do{
		do{
			cs();
			cout << endl << "Developer Menu" << endl << endl;
			if(apps.myuser.type == "developer"){
				cout << apps.myuser.b->getName() << "\t\t" << apps.myuser.b->getMoney() << "$ ";
			}else if(apps.myuser.type == "company"){
				cout << apps.myuser.c->getName() << "\t\t" << apps.myuser.c->getMoney() << "$ ";
			}
			cout << "\n\n1.Make App\n2.My Apps\n3.My Apps awaiting approval\n4.Change address\n5.Change Password\n6.Top 10 Apps\n7.LogOut\n\n";
			cin >> choice;
		}while(choice <= 0 || choice >7);
		cin.clear();
		cin.ignore();
		priority_queue<AppForSubmission> tmp = apps.getValidation();
		bool alreadyExists = false;
		switch(choice){
		case 1:
			cs();
			cout << "\nYou can input '<-' to go back\n";
			cout << "\n\nApp Name: ";
			getline(cin,appname);
			if(appname=="<-") break;
			cout << "\n\nApp Cost: ";
			getline(cin,appcost);
			if(appcost=="<-") break;
			cout << "\n\nApp Category: ";
			getline(cin,appcat);
			if(appcat=="<-") break;
			cout << "\n\nYour App Description: ";
			getline(cin,appdesc);
			if(appdesc=="<-") break;
			cost = atof(appcost.c_str());
			while(!tmp.empty()){
				if(appname == tmp.top().getApp().getName()){
					alreadyExists = true;
					break;
				}
				tmp.pop();
			}
			if(!alreadyExists){
				for(size_t i = 0; i < apps.AllTimeApps.size(); i++)
					if(appname == apps.AllTimeApps[i].getName()){
						alreadyExists = true;
						break;
					}
			}
			if(!alreadyExists){
				myapp = App(appname,cost, appcat, appdesc, false, 0);
				printf("Created App id: %d\n",myapp.getId());
				if(apps.myuser.type == "company"){
					AppForSubmission mySubApp(myapp, Date(), apps.myuser.c->getUser() );
					apps.validation.push(mySubApp);
				}else{
					AppForSubmission mySubApp(myapp, Date(), apps.myuser.b->getUser() );
					apps.validation.push(mySubApp);
				}
				cout << "\n\nYour app was created successfully and submitted for approval\n\n";

			}
			else{
				cout << "\n\nAn app with name already exists, therefore your app was not created!\n\n";
			}
			pause();
			break;
		case 2:
			showapps(apps);
			break;
		case 3:
			showAppsAwatingValidation(apps);
			break;
		case 4:
			cs();
			cout << "\nWrite '<-' to go back\n\nYour new address: ";
			getline(cin,address);
			if(address != "<-"){
				if(apps.myuser.type == "developer"){
					apps.myuser.c->setAddress(address);
				}else{
					apps.myuser.b->setAddress(address);
				}
				cout << "\n\nYour address was changed successfully\n";
				Sleep(1000);
			}
			break;
		case 5:
			cs();
			cout << "\nYour Password: ";
			getline(cin,pw);
			if(apps.myuser.type == "developer"){
				if(apps.myuser.b->getPw()==pw){
					cout << "\nYour new pw: ";
					getline(cin,pw1);
					apps.myuser.b->setPw(pw1);
					cout << "Your pw was changed successfully";
				}else{
					cout << "\n\nThat is not your pw\n\n";
					pause();
				}
			}else if(apps.myuser.type == "company"){
				if(apps.myuser.c->getPw()==pw){
					getline(cin,pw1);
					apps.myuser.c->setPw(pw1);
					cout << "Your pw was changed successfully";
				}else{
					cout << "\n\nThat is not your pw\n\n";
					pause();
				}
			}
			break;
		case 6:
			top10menu(apps);
			break;
		case 7:
			return -1;
			break;
		}
	}while(true);
}

/**
 * @brief CRUD Menu for clients
 *
 * @param apps AppStore
 *
 */

void AdminClient(AppStore &apps) {
	int choice;
	bool a = true;
	while (a) {
		do {
			cs();
			cout << "                Admin Menu - Clients\n";
			cout << "                         CRUD\n\n\n\n";
			cout << "        1.Create\n" <<
					"        2.Read\n" <<
					"        3.Update\n" <<
					"        4.Delete\n" <<
					"        5.Show All\n" <<
					"        6.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 6) || (choice < 1));
		switch (choice) {
		case 1: apps.createClient(); break;
		case 2: apps.readClient(); break;
		case 3: {
			try {
				apps.updateClient();
			} catch (ClientNotFound &f) {
				cout << "Client " << f.retname() << " not found.\n";
			}
			break;
		}
		case 4: apps.deleteClient(); break;
		case 5: { apps.showAllClients(); break; }
		case 6: { a = false; break; }
		}
	}
}


/**
 * @brief CRUD Menu for BST
 *
 * @param apps AppStore
 *
 */
void AdminBST(AppStore &apps) {
	apps.setAppClassifications();
	int choice;
	bool a = true;
	while (a) {
		do {
			cs();
			cout << "                Admin Menu - BST - Apps\n";
			cout << "                         CRUD\n\n";
			cout << "As the Binary Search tree is composed of existing Apps it is\n"
					"not logical to allow introduction of members that do not\n"
					"correspond to any existing one. It is, however, allowed to add\n"
					"Apps that exist but do not take part in the BST. The same aplies\n"
					"to update, when an App is updated the BST is automaticly updated\n"
					"too.\n\n\n";
			cout << "        1.Add to BST\n" <<
					"        2.Read BSTs content\n" <<
					"        3.Remove from BST\n" <<
					"        4.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 4) || (choice < 1));
		switch (choice) {
		case 1: apps.addToBst(); break;
		case 2: apps.readBst(); break;
		case 3: apps.removeFromBst(); break;
		case 4: { a = false; break; }
		}
	}
}

/**
 * @brief CRUD Menu for Devs
 *
 * @param apps AppStore
 *
 */

void AdminDev(AppStore &apps) {
	int choice;
	bool a = true;
	while (a) {
		do {
			cs();
			cout << "                Admin Menu - Developers\n";
			cout << "                         CRUD\n\n\n\n";
			cout << "        1.Create\n" <<
					"        2.Read\n" <<
					"        3.Update\n" <<
					"        4.Delete\n" <<
					"        5.Show all\n" <<
					"        6.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 6) || (choice < 1));
		switch (choice) {
		case 1: apps.createDeveloper(); break;
		case 2: apps.readDeveloper(); break;
		case 3: apps.updateDeveloper(); break;
		case 4: apps.deleteDeveloper(); break;
		case 5: { apps.showAllDevelopers(); break; }
		case 6: { a = false; break; }
		}
	}
}

/**
 * @brief CRUD Menu for companies
 *
 * @param apps AppStore
 *
 */

void AdminCompany(AppStore &apps) {
	int choice;
	bool a = true;
	while (a) {
		do {
			cs();
			cout << "                Admin Menu - Companies\n";
			cout << "                         CRUD\n\n\n\n";
			cout << "        1.Create\n" <<
					"        2.Read\n" <<
					"        3.Update\n" <<
					"        4.Delete\n" <<
					"        5.Show all\n" <<
					"        6.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 6) || (choice < 1));
		switch (choice) {
		case 1: apps.createCompany(); break;
		case 2: apps.readCompany(); break;
		case 3: apps.updateCompany(); break;
		case 4: apps.deleteCompany(); break;
		case 5: { apps.showAllCompanies(); break; }
		case 6: { a = false; break; }
		}
	}
}

/**
 * @brief CRUD Menu for Apps
 *
 * @param apps AppStore
 *
 */

void AdminApps(AppStore &apps) {
	int choice;
	bool a = true;
	while (a) {
		do {
			cs();
			cout << "                Admin Menu - Apps\n";
			cout << "                         CRUD\n\n\n\n";
			cout << "        1.Create\n" <<
					"        2.Read\n" <<
					"        3.Update\n" <<
					"        4.Delete\n" <<
					"        5.Show all\n" <<
					"        6.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 6) || (choice < 1));
		switch (choice) {
		case 1: {
			try {
				apps.createApp();
			} catch (OutOfBoolRange &f) {
				cout << "Invalid input.\n";
			}
			break;
		}
		case 2: apps.readApp(); break;
		case 3: {
			try {
				apps.updateApp();
			}
			catch (OutOfBoolRange &f) {
				cout << "Invalid input.\n";
			}
			catch (DeveloperOrCompanyNotFound &f) {
				cout << "Invalid input.\n";
			}
			break;
		}
		case 4: apps.deleteApp(); break;
		case 5: { apps.showAllApps(); break; }
		case 6: { a = false; break; }
		}
	}
}

/**
 * @brief CRUD Menu for Apps waiting for validation
 *
 * @param apps AppStore
 *
 */

void AdminWaitingApps(AppStore &apps) {
	int choice;
	bool a = true;
	while (a) {
		do {
			cs();
			cout << "                Admin Menu - Apps\n";
			cout << "                         CRUD\n\n\n\n";
			cout << "        1.Validate App\n" <<
					"        2.Read\n" <<
					"        3.Update\n" <<
					"        4.Delete\n" <<
					"        5.Show all\n" <<
					"        6.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 6) || (choice < 1));
		switch (choice) {
		case 1: {
			try {
				apps.validateApp();
			} catch (OutOfBoolRange &f) {
				cout << "Invalid input.\n";
			}
			break;
		}
		case 2: apps.readAppWaitingApproval(); break;
		case 3:	apps.updateAppWaitingApproval(); break;
		case 4: apps.deleteAppWaitingApproval(); break;
		case 5: apps.showAllAppsWaitingApproval(); break;
		case 6: { a = false; break; }
		}
	}
}

/**
 * @brief CRUD Menu for Apps out of sales
 *
 * @param apps AppStore
 *
 */

int AdminHashApps(AppStore &apps) {
	int choice;
	bool a = true;
	while (a) {
		do {
			cs();
			cout << "                Admin Menu - Apps\n";
			cout << "                         CRUD\n\n\n\n";
			cout << "        1.Create\n" <<
					"        2.Update\n" <<
					"        3.Delete\n" <<
					"        4.Show all\n" <<
					"        5.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 5) || (choice < 1));
		switch (choice) {
		case 1: apps.createHashApps(); break;
		case 2: apps.updateHashApps(); break;
		case 3:	apps.delHashApps(); break;
		case 4: apps.showHashApps(); break;
		case 5: { a = false; break; }
		}
	}
	return 1;
}


/**
 * @brief CRUD Menus
 *
 * @param apps AppStore
 *
 */

int AdminMenu(AppStore &apps) {
	int choice;
	bool a = true;
	while(a){
		do {
			cs();
			cout << "                Admin Menu\n\n\n\n";
			cout << "        1.Client\n" <<
					"        2.Developer\n" <<
					"        3.Company\n" <<
					"        4.Apps\n" <<
					"        5.Apps awaiting approval\n" <<
					"        6.Hidden Apps\n" <<
					"        7.Show All Sales\n" <<
					"        8.Top 10 Apps\n" <<
					"        9.Edit ranking\n" <<
					"        10.Back\n";
			cin >> choice;
			cin.clear();
			cin.ignore();
		} while ((choice > 10) || (choice < 1));
		switch (choice) {
		case 1: AdminClient(apps); break;
		case 2: AdminDev(apps); break;
		case 3: AdminCompany(apps); break;
		case 4: AdminApps(apps); break;
		case 5: AdminWaitingApps(apps); break;
		case 6: {AdminHashApps(apps); break;}
		case 7: { apps.showAllSales(); break; }
		case 8: { top10menu(apps); break; }
		case 9: { AdminBST(apps); break; }
		case 10: { a = false; break; }
		}
	}
	return choice;
}

/**
 * @brief function to redirect to menu type
 *
 * @param apps AppStore
 * @param a type of menun (from 1 to 3)
 *
 */

int Menu(int a,AppStore &apps) {
	cs();
	if(a == 1) {
		cout << "\n\nRedirecting you to client menu\n";
		Sleep(750);
		if(ClientMenu(apps)==-1){
			return 0;
		}
		return 0;
	} else if(a == 2) {
		cout << "\n\nRedirecting to developer menu\n";
		DevMenu(apps);
		return 1;
	} else if(a == 3) {
		cout << "\n\nRedirecting to admin menu\n";
		AdminMenu(apps); //CRUD
	}
	pause();
	return 1;
}

//CLIENTS--------------------------

/**
 * @brief Function to get an App from an ID
 *
 * @param apps AppStore
 * @return Returns an app Pointer with that ID
 */

App*idtoapp(int id, AppStore &appst){
	unsigned int size = appst.AllTimeApps.size();
	for(int i = 0; i<size;i++){
		if(appst.AllTimeApps[i].getId()==id){
			return &appst.AllTimeApps[i];
		}
	}
	throw NotAnApp(id);
}

/**
 * @brief Function to read clients info from text file
 *
 * @param apps AppStore
 *
 */

vector<Client> readClients(AppStore &apps){
	vector<Client> clie;
	vector<App*> myapps;
	vector<classification> classif;
	string info;
	int stars;
	ifstream myfile;
	myfile.open("clients.txt");
	if (myfile.is_open())
		while(getline(myfile,info)) {
			string user = info;
			getline(myfile,info);
			string pw = info;
			getline(myfile,info);
			string nome = info;
			getline(myfile,info);
			float money = atof(info.c_str());
			getline(myfile,info);//Descobre o id da primeira APP
			while(info!="endapps") {
				int id = atoi(info.c_str());
				App *thisapp;
				try {
					thisapp = idtoapp(id,apps);
				} catch (NotAnApp &f) {
					cout << "ERROR: App with id " << f.retid() << " not on AppStore vector.";
				}
				myapps.push_back(thisapp);
				getline(myfile,info);
			}
			getline(myfile,info);
			while(info!="endclassifs") {
				int id = atoi(info.c_str());
				getline(myfile,info);
				int stars = atoi(info.c_str());
				getline(myfile,info);
				string cla = info;
				classification a = classification(id,stars,cla);
				classif.push_back(a);
				getline(myfile,info);
			}
			Client a = Client(user,pw,nome,money,myapps,classif);
			clie.push_back(a);
			myapps.clear();
			classif.clear();
		}
	else
		throw fileNotOpened("clients.txt");
	myfile.close();
	return clie;
}

/**
 * @brief Function to write clients info to text file
 *
 * @param apps AppStore
 *
 */

void writeClients(vector<Client> vc) {//MESMO QUE A ANTERIOR

	ofstream myfile;
	myfile.open("clients.txt");
	if (myfile.is_open())
		for(unsigned int i = 0; i < vc.size(); i++){
			myfile << vc[i].getUser() << endl;
			myfile << vc[i].getPw() << endl;
			myfile << vc[i].getName() << endl;
			myfile << vc[i].getMoney() << endl;
			vector<App*> myapps = vc[i].getApps();
			vector<classification> myclassifs = vc[i].getClass();
			int size = myapps.size();
			for(unsigned int a = 0;a < size;a++){
				myfile << myapps[a]->getId() << endl;
			}
			myfile << "endapps" << endl;
			for(unsigned int a = 0;a < myclassifs.size();a++){
				myfile << myclassifs[a].getId() << endl;
				myfile << myclassifs[a].getStars() << endl;
				myfile << myclassifs[a].getCla() << endl;
			}
			myfile << "endclassifs" << endl;
		}
	else
		throw fileNotOpened("clients.txt");
	myfile.close();
}

//APPS------------------------------

/**
 * @brief Function to read Apps info from text file
 *
 * @param apps AppStore
 * @return vector of apps
 */
vector<App> readApps(AppStore & apps){ //VERIFICAR PORQUE ERRA E PORQUE THROW NAO RESULTA
	vector<App> initial;
	string info;
	ifstream myfile;
	myfile.open("Apps.txt");
	if (myfile.is_open())
		while(getline(myfile,info)) {
			string name = info;
			getline(myfile,info);
			float cost = atof(info.c_str());
			getline(myfile,info);
			string category = info;
			getline(myfile,info);
			string description = info;
			getline(myfile,info);
			bool boolean = atof(info.c_str());
			getline(myfile,info);
			int id = atoi(info.c_str());
			App a = App(name,cost,category,description,boolean);
			a.setId(id);
			initial.push_back(a);
		}
	else
		throw fileNotOpened("Apps.txt");
	myfile.close();
	int id = 0;
	for(int i = 0; i < initial.size();i++){
		if(id < initial[i].getId()){
			id = initial[i].getId() + 1;
		}
	}
	setAppId(id);
	return initial;
}

void readAppstoBst(AppStore & apps){ //VERIFICAR PORQUE ERRA E PORQUE THROW NAO RESULTA
	string info, info2, info3, info4;
	ifstream myfile;
	myfile.open("BST.txt");
	if (myfile.is_open())
		while(getline(myfile,info)) {
			getline(myfile,info2);
			getline(myfile,info3);
			getline(myfile,info4);
			float cost = atof(info3.c_str());
			int id = atoi(info.c_str());
			int cl = atoi(info2.c_str());
			string ca = info4;
			AppToBst a = AppToBst(id,cl,cost,ca);
			apps.appsBst.insert(a);
		}
	else
		throw fileNotOpened("BST.txt");
	myfile.close();
	return;
}

/**
 * @brief Function to write Apps info to text file
 *
 * @param apps AppStore
 *
 */

void writeAppsToBst(BST<AppToBst> app) {//MESMO QUE A ANTERIOR
	ofstream myfile;
	myfile.open("BST.txt");
	BSTItrIn<AppToBst> it(app);
	int i = 0;
	if (myfile.is_open())
		while (!it.isAtEnd()) {
			if (i > 0)
				myfile << endl;
			myfile << it.retrieve().id << endl;
			myfile << it.retrieve().classif << endl;
			myfile << it.retrieve().cost << endl;
			myfile << it.retrieve().categ;
			i++;
			it.advance();
		}
	else
		throw fileNotOpened("BST.txt");
	myfile.close();
}

void writeApps(vector<App> &v) {//MESMO QUE A ANTERIOR
	ofstream myfile;
	myfile.open("Apps.txt");
	if (myfile.is_open())
		for(unsigned int i = 0; i < v.size(); i++){
			if(i!=0) myfile << endl;
			myfile << v[i].getName() << endl;
			myfile << v[i].getCost() << endl;
			myfile << v[i].getCategory() << endl;
			myfile << v[i].getDescription() << endl;
			if(v[i].getForSale())
				myfile << 1;
			else
				myfile << 0;
			myfile << endl;
			myfile << v[i].getId();
		}
	else
		throw fileNotOpened("Apps.txt");
	myfile.close();
}

//DEVELOPERS---------------------------------------



/**
 * @brief Function to read Devs info from text file
 *
 * @param apps AppStore
 * @return vector of Devs
 */
vector<Developer> readDevs(AppStore &apps){
	vector<Developer> dev;
	vector<App*> myapps;
	string info;
	ifstream myfile;
	myfile.open("developers.txt");
	if (myfile.is_open()) {

		while(getline(myfile,info)) {

			string user = info;
			getline(myfile,info);
			string pw = info;
			getline(myfile,info);
			string nome = info;
			getline(myfile,info);
			string morada = info;
			getline(myfile,info);//Descobre o nome da primeira APP
			string m = info;
			float money= atof(m.c_str());
			getline(myfile,info);
			while(info!="endapps") {

				int id = atoi(info.c_str());
				App *thisapp;

				bool temp = false;

				try {
					thisapp = idtoapp(id,apps);
				} catch (NotAnApp &f) {
					temp = true;
					cout << "ERROR: App with id " << f.retid() << " not on AppStore vector.";
					getline(myfile,info);
				}

				if (!temp) {
					myapps.push_back(thisapp);
					getline(myfile,info);
				}
			}
			Developer a = Developer(user,pw,nome,morada,money,myapps);
			dev.push_back(a);
		}
	}
	else {
		throw fileNotOpened("clients.txt");
	}
	myfile.close();

	return dev;
}

/**
 * @brief Function to write Devs info to text file
 *
 * @param apps AppStore
 *
 */
void writeDevs(AppStore & apps) {//MESMO QUE A ANTERIOR

	ofstream myfile;
	myfile.open("developers.txt");
	if (myfile.is_open())
		for(unsigned int i = 0; i < apps.developers.size(); i++){
			if(i!=0){
				myfile << endl;
			}
			myfile << apps.developers[i].getUser() << endl;
			myfile << apps.developers[i].getPw() << endl;
			myfile << apps.developers[i].getName() << endl;
			myfile << apps.developers[i].getAddress() << endl;
			myfile << apps.developers[i].getMoney() << endl;
			vector<App*> myapps = apps.developers[i].getApps();
			int size = myapps.size();
			for(unsigned int a = 0;a < size;a++){
				App* temp = myapps[a];
				myfile << temp->getId() << endl;
			}
			myapps.clear();
			myfile << "endapps";
		}
	else
		throw fileNotOpened("developers.txt");
	myfile.close();
}

//COMPANIES-----------------------------------
/**
 * @brief Function to read Companies info from text file
 *
 * @param apps AppStore
 * @return vector of companies
 */
vector<Company> readComp(AppStore &apps){
	vector<Company> comp;
	vector<App*> myapps;
	string info;
	ifstream myfile;
	myfile.open("companies.txt");
	if (myfile.is_open())
		while(getline(myfile,info)) {
			string user = info;
			getline(myfile,info);
			string pw = info;
			getline(myfile,info);
			string nome = info;
			getline(myfile,info);
			string morada = info;
			getline(myfile,info);
			float money = atoi(info.c_str());
			getline(myfile,info);
			int nif = atoi(info.c_str());
			getline(myfile,info);//Descobre o nome da primeira APP
			while(info!="endapps") {

				int id = atoi(info.c_str());
				App *thisapp;
				try {
					thisapp = idtoapp(id,apps);
				} catch (NotAnApp &f) {
					cout << "ERROR: App with id " << f.retid() << " not on AppStore vector.";
				}
				myapps.push_back(thisapp);
				if(!thisapp->getForSale()){
					apps.hashInsert(thisapp);
				}
				getline(myfile,info);
			}

			Company a = Company(user,pw,nome,morada,money,nif,myapps);
			comp.push_back(a);
			myapps.clear();
		}
	else
		throw fileNotOpened("companies.txt");
	myfile.close();
	return comp;
}

/**
 * @brief Function to write Companies info to text file
 *
 * @param apps AppStore
 *
 */
void writeComp(vector<Company> vd) {//MESMO QUE A ANTERIOR

	ofstream myfile;
	myfile.open("companies.txt");
	if (myfile.is_open())
		for(unsigned int i = 0; i < vd.size(); i++){
			if(i!=0){
				myfile << endl;
			}
			myfile << vd[i].getUser() << endl;
			myfile << vd[i].getPw() << endl;
			myfile << vd[i].getName() << endl;
			myfile << vd[i].getAddress() << endl;
			myfile << vd[i].getMoney() << endl;
			myfile << vd[i].getNif() << endl;
			vector<App*> myapps = vd[i].getApps();
			int size = myapps.size();
			for(unsigned int a = 0;a < size;a++){
				myfile << vd[i].getApps()[a]->getId() << endl;
			}
			myapps.clear();
			myfile << "endapps";
		}
	else
		throw fileNotOpened("companies.txt");
	myfile.close();
}

//CODES----------------------------------------------------
/**
 * @brief Function to read Codes from text file
 *
 * @param apps AppStore
 * @return vector of strings with codes
 */

vector <string> readCodes(AppStore &apps){
	vector<string> cod;
	string info;
	ifstream myfile;
	myfile.open("codes.txt");
	if (myfile.is_open())
		while(getline(myfile,info)) {
			cod.push_back(info);
		}
	else
		throw fileNotOpened("codes.txt");
	myfile.close();
	return cod;
}



//SALES----------------------------------------------------

/**
 * @brief Function to read Codes from text file
 *
 * @param apps AppStore
 * @return vector of strings with codes
 */
vector<Sale> readSales(AppStore &apps){
	vector<Sale> retsales;
	ifstream myfile;
	string info;
	myfile.open("Sales.txt");
	if (myfile.is_open())
		while(getline(myfile,info)) {
			int hour = atoi(info.c_str());
			getline(myfile,info);
			int minutes = atoi(info.c_str());
			getline(myfile,info);
			int day = atoi(info.c_str());
			getline(myfile,info);
			int month = atoi(info.c_str());
			getline(myfile,info);
			int year = atoi(info.c_str());
			getline(myfile,info);
			int id = atoi(info.c_str());
			getline(myfile,info);
			string user = info;
			Date d = Date(hour,minutes,day,month,year);
			Sale s;
			s.setDate(d);
			for(int i = 0; i < apps.clients.size() ; i++){
				if(apps.clients[i].getUser() == user){
					s.setBuyer(&apps.clients[i]);
				}
			}
			for(int i = 0; i < apps.AllTimeApps.size() ; i++){
				if(apps.AllTimeApps[i].getId() == id){
					s.setApp(&apps.AllTimeApps[i]);
				}
			}
			retsales.push_back(s);
		}
	else
		throw fileNotOpened("Sales.txt");
	myfile.close();
	return retsales;
}

/**
 * @brief Function to write sales to text file
 *
 * @param vd Vector of sales
 *
 */
void writeSales(vector<Sale> vd) {//MESMO QUE A ANTERIOR

	ofstream myfile;
	myfile.open("Sales.txt");
	if (myfile.is_open())
		for(unsigned int i = 0; i < vd.size(); i++){
			if(i!=0){
				myfile << endl;
			}
			myfile << vd[i].getDate().day << endl;
			myfile << vd[i].getDate().month << endl;
			myfile << vd[i].getDate().year << endl;
			myfile << vd[i].getDate().hour << endl;
			myfile << vd[i].getDate().minutes << endl;
			myfile << vd[i].getAppSold()->getId()  << endl;
			myfile << vd[i].getUser();
		}
	else
		throw fileNotOpened("Sales.txt");
	myfile.close();
}

/**
 * @brief Function to show apps from BST
 *
 * @param apps AppStore
 *
 */

void top10menu(AppStore apps) {
	cs();
	apps.setAppClassifications();
	cout << "                Top 10 Apps\n\n\n\n";
	apps.showTop10();
	cout << "\n\n\n";
	system("pause");
	return;
}


//VALIDATION

/**
 * @brief Function to read companies info from text file
 *
 * @param apps AppStore data structure
 * @return vector of companies
 */

vector<Company> read(AppStore &apps){
	vector<Company> comp;
	vector<App*> myapps;
	string info;
	ifstream myfile;
	myfile.open("companies.txt");
	if (myfile.is_open())
		while(getline(myfile,info)) {
			string user = info;
			getline(myfile,info);
			string pw = info;
			getline(myfile,info);
			string nome = info;
			getline(myfile,info);
			string morada = info;
			getline(myfile,info);
			float money = atoi(info.c_str());
			getline(myfile,info);
			int nif = atoi(info.c_str());
			getline(myfile,info);//Descobre o nome da primeira APP
			while(info!="endapps") {

				int id = atoi(info.c_str());
				App *thisapp;
				try {
					thisapp = idtoapp(id,apps);
				} catch (NotAnApp &f) {
					cout << "ERROR: App with id " << f.retid() << " not on AppStore vector.";
				}
				myapps.push_back(thisapp);
				if(!thisapp->getForSale()){
					apps.hashInsert(thisapp);
				}
				getline(myfile,info);
			}

			Company a = Company(user,pw,nome,morada,money,nif,myapps);
			comp.push_back(a);
			myapps.clear();
		}
	else
		throw fileNotOpened("companies.txt");
	myfile.close();
	return comp;
}

/**
 * @brief Function read validations from text file
 *
 * @param apps AppStore Data Structure
 *
 */
void readVals(AppStore & apps){
	ifstream myfile;
	myfile.open("vals.txt");
	string info;
	if (myfile.is_open())
		while(getline(myfile,info)){
			string name = info;
			float cost;
			string cat;
			string desc;
			int minutes;
			int hours;
			int day;
			int month;
			int year;
			string user;
			getline(myfile,info);
			cost = atof(info.c_str());
			getline(myfile,info);
			cat = info;
			getline(myfile,info);
			desc = info;
			getline(myfile,info);
			minutes = atoi(info.c_str());
			getline(myfile,info);
			hours = atoi(info.c_str());
			getline(myfile,info);
			day = atoi(info.c_str());
			getline(myfile,info);
			month = atoi(info.c_str());
			getline(myfile,info);
			year = atoi(info.c_str());
			getline(myfile,info);
			user = info;
			App myapp(name, cost, cat, desc, false);
			Date mydate(hours,minutes,day,month,year);
			AppForSubmission mysub(myapp,mydate,user);
			apps.validation.push(mysub);
		}
	else
		throw fileNotOpened("vals.txt");
}

/**
 * @brief Write Apps waiting for validation info to text file
 *
 * @param apps AppStore Data structure
 *
 */

void writeVals(AppStore & apps) {//MESMO QUE A ANTERIOR
	priority_queue<AppForSubmission> temp = apps.getValidation();
	ofstream myfile;
	myfile.open("vals.txt");
	if (myfile.is_open())
		while(!temp.empty()){
			myfile << temp.top().getApp().getName() << endl;
			myfile << temp.top().getApp().getCost() << endl;
			myfile << temp.top().getApp().getCategory() << endl;
			myfile << temp.top().getApp().getDescription() << endl;
			myfile << temp.top().getSubDate().minutes << endl;
			myfile << temp.top().getSubDate().hour << endl;
			myfile << temp.top().getSubDate().day << endl;
			myfile << temp.top().getSubDate().month << endl;
			myfile << temp.top().getSubDate().year << endl;
			myfile << temp.top().getUsername() << endl;
			temp.pop();
		}
	else
		throw fileNotOpened("vals.txt");
	myfile.close();
}

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <tr1/unordered_set>
#include <queue>
#include "BST.h"

/** @defgroup appStore appStore
 * @{
 * Main functions controlling the appStore
 */

using namespace std;

/**
 * @brief Changes the global variable to the value given
 *
 * @param id value of destiny
 */
void setAppId(int id);

class App;
class Client;
class Developer;
class Sale;
class Company;
class AppForSubmission;

class AppToBst {
public:
	int id;
	int classif;
	float cost;
	string categ;
	/**
	 * @brief Creates an object of AppToBst class
	 */
	AppToBst() {
		id = -1;
		classif = -1;
		cost = -1;
		categ = "";
	};
	/**
	 * @brief Creates an object of AppToBst class
	 *
	 * @param i ID
	 * @param classi Classification
	 * @param c Cost
	 * @param ca Category
	 */
	AppToBst(int i, int classi, float c, string ca)
	:id(i), classif(classi), cost(c), categ(ca) {};
	/**
	 * @brief operator < overload
	 * 
	 * @param a AppToBst class object
	 */
	bool operator <(const AppToBst a) const;
};

class User{  //Classe que tem a informação (apontador) para um cliente/developer/company que tenha feito
public:      //login no menu de login
	Client*a;
	Developer*b;
	Company*c;
	string type;
	/**
	 * @brief Builds the object
	 */
	User(Client*a);
	/**
	 * @brief Builds the object
	 */
	User(Developer*a);
	/**
	 * @brief Builds the object
	 */
	User(Company*a);
	/**
	 * @brief Builds the object
	 */
	User();
	/**
	 * @brief Destroys the object
	 */
	~User();
};

class AppStore {	//A classe AppStore tem toda a informção mais relevante do projecto, toda a informação
public:				//carregada a partir de ficheiros txt, a maior parte das classes são classes derivadas desta classe
	vector<App> AllTimeApps;
	vector<Client> clients;
	vector<Developer> developers;
	vector<Company> companies;
	vector<Sale> sales;
	vector<string> codes;
	BST<AppToBst> appsBst;
	tr1::unordered_set<App*> hash;
	priority_queue<AppForSubmission> validation;
	User myuser;

	/**
	 * @brief creates an App
	 */
	AppStore();

	//CRUD - Apps - NECESSARIO TRATAR EXCECOES

	/**
	 * @brief Creates an App asking for its atributes
	 */
	bool createApp();
	/**
	 * @brief Reads the info of an App
	 */
	void readApp();
	/**
	 * @ brief Updates an App asking for its atributtes
	 *
	 * @return Returns true upon success
	 */
	bool updateApp();
	/**
	 * @ brief Deletes an App
	 *
	 * @return Returns true upon success
	 */
	bool deleteApp();
	/**
	 * @brief Shows all Apps
	 */
	void showAllApps() const;

	/**
	 * @ brief Validates the apps created and waiting for validation and puts it, or not in the vector os AllTimeApps
	 */
	void validateApp();
	/**
	 * @brief Display info on 1 App waiting to be aproved
	 */
	void readAppWaitingApproval();
	/**
	 *@brief Deletes an App that is waiting for Aproval
	 */
	void deleteAppWaitingApproval();
	/**
	 * @brief Displays the list of all Apps waiting for approval
	 */
	void showAllAppsWaitingApproval() const;
	/**
	 * @brief Updates one of the Apps waiting for approval
	 */
	void updateAppWaitingApproval();

	/**
	 * @brief Creates a Client - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool createClient();
	/**
	 * @brief Reads intel on a Client - CRUD
	 */
	void readClient();
	/**
	 * @brief Updates a Client - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool updateClient();
	/**
	 * @brief Deletes a Client - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool deleteClient();
	/**
	 * @brief Shows the list of all Clients - CRUD
	 */
	void showAllClients() const;

	/**
	 * @brief Creates a Developer - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool createDeveloper();
	/**
	 * @brief Reads intel on a Developer - CRUD
	 */
	void readDeveloper();
	/**
	 * @brief Updates a Development - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool updateDeveloper();
	/**
	 * @brief Deletes a Developer - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool deleteDeveloper();
	/**
	 * @brief Shows all Developers - CRUD
	 */
	void showAllDevelopers() const;

	/**
	 * @brief Creates a Company - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool createCompany();
	/**
	 * @brief Reads intel of a Company - CRUD
	 */
	void readCompany();
	/**
	 * @brief Updates a Company - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool updateCompany();
	/**
	 * @brief Deletes a Company - CRUD
	 *
	 * @return Returns true upon success
	 */
	bool deleteCompany();
	/**
	 * @brief Shows the list of all Companies - CRUD
	 */
	void showAllCompanies() const;

	/**
	 * @brief Shows the list of all Sales - CRUD
	 */
	void showAllSales() const;

	/**
	 * @brief Finds the index of the client in the respective vector
	 *
	 * @param n The name of the client
	 *
	 * @return Returns the index. Returns -1 when not successful
	 */
	int findIndexClient(string n);
	/**
	 * @brief Finds the index of the Developer in the respective vector
	 *
	 * @param n The name of the developer
	 *
	 * @return Returns the index. Returns -1 when not successful
	 */
	int findIndexDeveloper(string n);
	/**
	 * @brief Finds the index of the user in the respective vector
	 *
	 * @param n The name of the user
	 *
	 * @return Returns the index. Returns -1 when not successful
	 */
	int findIndexDevUser(string n);
	/**
	 * @brief Finds the index of the company in the respective vector
	 *
	 * @param n The name of the company
	 *
	 * @return Returns the index. Returns -1 when not successful
	 */
	int findIndexCompany(string n);
	/**
	 * @brief Finds the index of the user in the respective vector
	 *
	 * @param n The name of the user
	 *
	 * @return Returns the index. Returns -1 when not successful
	 */
	int findIndexCompUser(string n);
	/**
	 * @brief Finds the index of the app in the respective vector
	 *
	 * @param n The name of the app
	 *
	 * @return Returns the index. Returns -1 when not successful
	 */
	int findIndexApp(string n);
	/**
	 * @brief Deletes an app of the developers vector
	 *
	 * @param n The id of the app
	 */
	void eraseAppDeveloper(int id);
	/**
	 * @brief Calculates the average of classification of each app
	 */
	void setAppClassifications();

	/**
	 * @brief Inserts a in the hash
	 *
	 * @param *a App to insert on hash
	 */
	void hashInsert(App*a){
		hash.insert(a);
	}
	/**
	 * @brief Removes a in the hash
	 *
	 * @param *a App to removes on hash
	 */
	void hashRemove(App*a){
		tr1::unordered_set<App*>::const_iterator it = hash.find(a);
		hash.erase(it);
	}
	/**
	 * @brief Gets the queue of apps waiting validation
	 *
	 * @return Returns queue of apps waiting validation
	 */
	priority_queue<AppForSubmission> getValidation() { return validation; }

	/**
	 * @brief Shows the top 10 Apps
	 */
	void showTop();
	/**
	 * @brief Frees the *App BST and replaces all Apps
	 */
	void appsToBst();

	/**
	 * @brief Sets the validation status
	 *
	 * @param validation queue of apps for submission
	 */
	void setValidation(const priority_queue<AppForSubmission>& validation) {
		this->validation = validation;
	}

	/**
	 * @brief List apps from Hash Table
	 *
	 */
	void showHashApps();
	/**
	 * @brief Returns a Dev name giving dev app
	 *
	 * @param name App name
	 * @return Dev Name
	 */
	string getDevFromApp(string name);

	/**
	 * @brief Deletes apps from hash tables
	 */
	void delHashApps();
	/**
	 * @brief Update Apps from Hash tables
	 *
	 */
	void updateHashApps();
	/**
	 * @brief Checks if an App exist
	 *
	 * @param name App name
	 * @return true if it exists, false if not
	 */
	bool exist(string name);
	/**
	 * @brief Checks if a Dev exist
	 *
	 * @param name Dev name
	 * @return true if it exists, false if not
	 */
	bool devExist(string name);

	/**
	 * @brief Create apps to insert on the hash table and other data structure
	 *
	 */
	int createHashApps();
	/**
	 * @brief All arguments are inserted with correct order on BST
	 *
	 */
	void BstReorganize();
	/**
	 * @brief Remove an App from BST
	 *
	 */
	void BstRemove(int id);
	/**
	 * @brief Shows top 10 Apps from BST
	 *
	 */
	void showTop10();
	/**
	 * @brief returns an App from a giving ID
	 * @param id giving Id
	 * @return Returns an App
	 */
	App getApp(int id);
	/**
	 * @brief Add an App to the BST
	 *
	 */

	void addToBst();
	/**
	 * @brief Read from BST
	 *
	 */

	void readBst();
	/**
	 * @brief Remove an App from BST
	 *
	 */

	void removeFromBst();
};

struct classification{ // Esta estrutura existe para permitir aos clientes darem uma espécie de nota às aplicações
	unsigned int id; //Há um vetor de classificações em cada cliente, com um id de cada app, para sabermos
	int stars;       //a qual app nos estamos a referir, estrelas de 0 a 5 e um comentário
	string cla;
public:
	classification(unsigned int i, int s ,string c);
	unsigned int getId();
	string getCla();
	void setCla(string c);
	int getStars();
	void setStars(int s);
};

struct Date{ //No construtor vazio desta estrutura vai-se buscar a data actual no computador
	int hour;
	int minutes;
	int day;
	int month;
	int year;
public:
	/**
	 * @brief Creates a date class object
	 */
	Date();
	/**
	 * @brief Creates a date class object
	 *
	 * @param h hours
	 * @param mi minutes
	 * @param d day
	 * @param m month
	 * @param y year
	 */
	Date(int h, int mi, int d, int m, int y);
	/**
	 * @brief Operator < overload
	 *
	 * @param Date structure
	 *
	 * @return Returns true if <
	 */
	bool operator <(Date const& b) const;
	/**
	 * @brief Operator > overload
	 *
	 * @param Date structure
	 *
	 * @return Returns true if >
	 */
	bool operator >(Date const& b) const;
	/**
	 * @brief Operator == overload
	 *
	 * @param Date structure
	 *
	 * @return Returns true if ==
	 */
	bool operator==(Date const& b) const;
};

class App : public AppStore { //Uma classe que tem toda a informação sobre uma aplicação, o booleano
	string name; 			  //permite perceber se a aplicação deve ser mostrada no menu de compras ou não
	float cost;				  //desta form nunca se vaii perder informação sobre a aplicação
	int id;
	string category;
	string description;
	float classification;
	bool forSale;
public:
	/**
	 * @brief Creates an object of App class
	 */
	App();
	/**
	 * @brief Creates an object of App class
	 *
	 * @param n Name
	 * @param co cost
	 * @param ca category
	 * @param di discription
	 * @param b bool
	 * @param classif 0
	 */
	App(string n, float co, string ca, string di, bool b, float classific = 0);
	/**
	 * @brief Gets classification
	 *
	 * @return classification
	 */
	float getClassification() const { return classification; };
	/**
	 * @brief Sets Classification
	 *
	 * @param a classification
	 */
	void setClassification(float a)  { classification = a; };
	/**
	 * @brief gets the name of the app
	 *
	 * @return Returns the name of the App
	 */
	string getName() const;
	/**
	 * @brief Sets the name of the App
	 *
	 * @param n name to set
	 */
	void setName(string n);
	/**
	 * @brief Gets the cost of the App
	 */
	float getCost() const;
	/**
	 * @brief Sets the cost of the App
	 *
	 * @param c cost of the App to set
	 */
	void setCost(float c);
	/**
	 * @brief Gets the App category
	 *
	 * @return Returns the Apps category
	 */
	string getCategory() const;
	/**
	 * @brief Sets the category
	 *
	 * @param cat category to set
	 */
	void setCategory(string cat);
	/**
	 * @brief Gets the description of the App
	 *
	 * @return Returns the Apps description
	 */
	string getDescription() const;
	/**
	 * @brief Sets the Apps description
	 *
	 * @return Returns the Apps description
	 */
	void setDescription(string desc);
	/**
	 * @brief Gets the Apps Id
	 *
	 * @return Returns the Apps Id
	 */
	int getId() const;
	/**
	 * @brief Gets the sale status of the App
	 *
	 * @return Returns true if for sale
	 */
	bool getForSale() const;
	/**
	 * @brief Sets the sale status of the App
	 *
	 * @param b the status to set
	 */
	void setForSale(bool b);
	/**
	 * @brief Sets the Apps Id
	 *
	 * @param nid Id to set
	 */
	void setId(int nid){
		id = nid;
	}
	/**
	 * @brief gets the %10 of the Apps Id
	 *
	 * @return Returns the %10 of the Apps Id
	 */
	int operator() (const App & ap) const
	{
		return ap.getId() % 10;
	}
	/**
	 * @brief compares two Apps Id
	 *
	 * @return Returns true if Id1 == Id2
	 */
	bool operator() (const App & ap1, const App & ap2) const
	{
		return ap1.getId() == ap2.getId();
	}
	/**
	 * @brief Operator < overload
	 *
	 * @param a App
	 *
	 * @return Returns true if first < second
	 */
	bool operator<(const App a) const;
	/**
	 * @brief Operator == overload
	 *
	 * @param a App
	 *
	 * @return Returns true if first == second
	 */
	bool operator==(const App a) const;
};



class AppForSubmission{
	App app;
	Date SubDate;
	string username;
public:
	/**
	 * @brief Creates an object of AppForSubmission class
	 */
	AppForSubmission(){
		app = App();
		SubDate = Date();
		username = "";
	}
	/**
	 * @brief Creates an object of AppForSubmission class
	 *
	 * @param a App
	 * @param sd date of insertion
	 * @param uName user name
	 */
	AppForSubmission(App a, Date sd, string uName);
	/**
	 * @brief Operator < overload
	 *
	 * @param b AppForSubmission
	 *
	 * @return Returnstrue if first < sencond
	 */
	bool operator <(AppForSubmission const& b) const;
	/**
	 * @brief Gets the App
	 *
	 * @return Returns an App
	 */
	App getApp() const { return app; }
	/**
	 * @brief Gets sub date
	 *
	 * @return Returns the submission date
	 */
	Date getSubDate() const { return SubDate; }
	/**
	 * @brief Get the users name
	 *
	 * @return Returns the users name
	 */
	string getUsername() const { return username; }
	/**
	 * @brief Sets the App
	 *
	 * @param appname Apps name
	 * @param cost Apps cost
	 * @param cat Apps category
	 * @param desc Apps description
	 */
	void setApp(string appname,float cost,string cat,string desc) {
		app.setName(appname);
		app.setCost(cost);
		app.setDescription(desc);
		app.setCategory(cat);
	}
};

class Client : public AppStore { //A classe cliente é um tipo de utilizador que nos permite apenas
	string username;		//comprar e classificar apps já compradas
	string password;
	string name;
	float money;
	vector<App*> apps;
	vector<classification> classif;
public:
	vector<App*> cart;
	/**
	 * @brief Creates an object of Client class
	 */
	Client();
	/**
	 * @brief Creates an object of Client class
	 *
	 * @param n clients name
	 */
	Client(string n);
	/**
	 * @brief Creates an object of Client class
	 *
	 * @param u username
	 * @param p password
	 * @param n name
	 */
	Client(string u,string p,string n);
	/**
	 * @brief Creates an object of Client class
	 *
	 * @param user username of the client
	 * @param pw clients password
	 * @param n clients name
	 * @param money clients actual money
	 * @param v clients apps
	 * @param vc clients classifications
	 */
	Client(string user,string pw,string n,float money, vector<App*> v,vector<classification> vc);
	/**
	 * @brief Gets clients name
	 *
	 * @return Returns clients name
	 */
	string getName() const;
	/**
	 * @brief Gets clients username
	 *
	 * @return Returns clients username
	 */
	string getUser() const;
	/**
	 * @brief Gets clients password
	 *
	 * @return Returns clients password
	 */
	string getPw() const;
	/**
	 * @brief Sets clients username
	 *
	 * @param n clients username
	 */
	void setUsername(string n);
	/**
	 * @brief Sets clients name
	 *
	 * @param n clients name
	 */
	void setName(string n);
	/**
	 * @brief Gets clients apps
	 *
	 * @return Returns clients apps
	 */
	vector<App*> getApps() const;
	/**
	 * @brief Sets clients apps
	 *
	 * @param Apps to set
	 */
	void setApps(vector<App*> v);
	/**
	 * @brief Gets clients classifications
	 *
	 * @return Returns clients classifications
	 */
	vector<classification> getClass() const;
	/**
	 * @brief Sets clients classifications
	 *
	 * @param c clients classifications to set
	 */
	void setClass(vector<classification> c);
	/**
	 * @brief Puts an App in the vector
	 *
	 * @param *a App to insert
	 */
	void pushBackApp(App*a);
	/**
	 * @brief Add to cart
	 *
	 * @param *a App to add
	 */
	void addToCart(App*a);
	/**
	 * @brief Gets clients cart
	 *
	 * @return Returns clients cart
	 */
	vector<App*> getCart();
	/**
	 * @brief Puts new description
	 *
	 * @param id Id of the app to describe
	 * @param s Stars given by the client
	 * @param description new description of the client
	 *
	 * @return 1
	 */
	int pushBackDescription(int id, int s,string descripton);
	/**
	 * @brief Sets the clients password
	 *
	 * @param Password to set
	 */
	void setPw(string pw);
	/**
	 * @brief Adds money
	 *
	 * @param l money to add
	 */
	void plusMoney(float l);
	/**
	 * @brief Gets the clients money
	 *
	 * @return Returns clients money
	 */
	float getMoney() const;
	/**
	 * @brief Sets clients money
	 *
	 * @param l money to be set
	 */
	void setMoney(float l);
	/**
	 * @brief Erases carts App
	 *
	 * @param app to delete
	 */
	void eraseCartApp(int a);
};

class Developer : public AppStore {//A classe Developer é uma classe que nos permite criar apps enquanto utilizador
	string username;
	string password;
	string name;
	string address;
	float money;
public:
	vector<App*> apps;
	/**
	 * @brief Creates an object of class Developer
	 */
	Developer();
	/**
	 * @brief Creates an object of class Developer
	 *
	 * @param n name of the developer
	 * @param a adress of the developer
	 */
	Developer(string n, string a);
	/**
	 * @brief Creates an object of class Developer
	 *
	 * @param username username of the developer
	 * @param password password of the developer
	 * @param n name of the developer
	 * @param a adress of the developer
	 * @param m money of the developer
	 * @param v apps of the developer
	 */
	Developer(string username,string password,string n, string a,float m, vector<App*> v);
	/**
	 * @brief Creates an object of class Developer
	 *
	 * @param username username of the developer
	 * @param password password of the developer
	 * @param n name of the developer
	 * @param a adress of the developer
	 */
	Developer(string username,string password,string n, string a);
	/**
	 * @brief Gets the name of the developer
	 *
	 * @return Returns the name of the developer
	 */
	string getName() const;
	/**
	 * @brief Sets the name of the developer
	 *
	 * @param n developers name
	 */
	void setName(string n);
	/**
	 * @brief Gets the address of the developer
	 *
	 * @return Returns the address of the developer
	 */
	string getAddress() const;
	/**
	 * @brief Sets the address of the developer
	 *
	 * @param ad address of the developer
	 */
	void setAddress(string ad);
	/**
	 * @brief Gets the username of the developer
	 *
	 * @return Returns the username of the developer
	 */
	string getUser() const;
	/**
	 * @brief Gets the password of the developer
	 *
	 * @return Returns the password of the developer
	 */
	string getPw() const;
	/**
	 * @brief Gets the Apps of the developer
	 *
	 * @return Returns the Apps of the developer
	 */
	vector<App*> getApps() const;
	/**
	 * @brief Sets the Apps of the developer
	 *
	 * @param Apps of the developer
	 */
	void setApps(vector<App*> v);
	/**
	 * @brief Sets the password of the developer
	 *
	 * @param password of the developer
	 */
	void setPw(string pw);
	/**
	 * @brief Sets the username of the developer
	 *
	 * @param username of the developer
	 */
	void setUsername(string n);
	/**
	 * @brief Gets the Money of the developer
	 *
	 * @return Returns Money of the developer
	 */
	float getMoney() const;
	/**
	 * @brief Sets the money of the developer
	 *
	 * @param money of the developer
	 */
	void setMoney(float m);


};

class Company: public Developer { //Uma company é uma classe derivada da classe developer com um nif
	int nif;
public:
    /**
     * @brief creates an object of class Company
     */
	Company();
    /**
     * @brief creates an object of class Company
     *
     * @param username
     * @param password
     * @param name
     * @param address
     * @param nif
     */
	Company(string username,string password,string name,string address,int nif);
    /**
     * @brief creates an object of class Company
     *
     * @param username username of the buyer
     * @param password of the user
     * @param n name of the user
     * @param a address of the user
     * @param m money of the user
     * @param nif
     * @param v apps of the user
     */
	Company(string username,string password,string n, string a,float m,int nif, vector<App*> v);
	/**
	 * @brief Gets the official name
	 *
	 * @return returns the official name
	 */
	string getOfficialName() const;
	/**
	 * @brief sets the official name
	 *
	 * @param ofn official name
	 */
	void setOfficialName(string ofn);
	/**
	 * @brief gets the official name
	 *
	 * @return official name
	 */
	int getNif() const;
	/**
	 * @brief sets the nif
	 *
	 * @param nif
	 */
	void setNif(int n);
	//CRUD
};

class Sale : public AppStore { //É uma classe que nos permite controlar as vendas feitas pelos developers
	Date date;
    int id;
    App*sold;
    Client* buyer;
public:
    /**
     * @brief Creates an object of type Sale
     */
    Sale();
    /**
     * @brief Creates an object of type Sale
     */
    Sale(App * s, Client* b);
    /**
     * @brief gets the date of the sale
     *
     * @return the date of the sale
     */
    Date getDate() const;
    /**
     * @brief sets the date of the sale
     *
     * @param the date of the sale
     */
    void setDate(Date d);
    /**
     * @brief gets the id of the sale
     *
     * @return the id of the sale
     */
    int getID() const;
    /**
     * @brief sets the id of the sale
     *
     * @param the id of the sale
     */
    void setID(int i);
    /**
     * @brief gets the static id of the sales
     *
     * @return the static id of the sales
     */
    int getStaticID() const;
    /**
     * @brief sets the static id of the sales
     *
     * @param the static id of the sales
     */
    void setStaticID(int i);
    /**
     * @brief gets the apps sold
     *
     * @return the apps sold
     */
    App*getAppSold() const;
    /**
     * @brief gets buyer
     *
     * @return the *buyer
     */
    Client* getBuyer() const;
    /**
     * @brief sets the app of the sale
     *
     * @param the app of the sale
     */
    void setApp(App*a);
    /**
     * @brief sets the client of the sale
     *
     * @param the buyer of the sale
     */
    void setBuyer(Client* b);
    /**
     * @brief gets user
     *
     * @return the user
     */
    string getUser();
};

class ClientNotFound { //Tratamento de exceçoes
public:
	string name;
	/**
	 * @brief Creates an objecto (exception) of class ClientNotFound
	 *
	 * @param n name
	 */
	ClientNotFound(string n) {
		name = n;
	}
	string retname() { return name; }
};

class AppNotFound { //tratamento de exceçoes
public:
	string name;
	/**
	 * @brief Creates an objecto (exception) of class AppNotFound
	 *
	 * @param n developer
	 */
	AppNotFound(string dev) {
		name = dev;
	}
};

class OutOfBoolRange { //tratamento de exceçoes
public:
	string intro;
	/**
	 * @brief Creates an objecto (exception) of class OutOfBoolRange
	 *
	 * @param n name
	 */
	OutOfBoolRange(string n) {
		intro = n;
	};
	/**
	 * @brief Returns intro
	 *
	 * @return returns intro
	 */
	string retintro() const {
		return intro;
	};
};

class DeveloperOrCompanyNotFound { //tratamento de exceçoes
public:
	string name;
	/**
	 * @brief Creates an objecto (exception) of class DeveloperOrCompanyNotFound
	 *
	 * @param dev developer
	 */
	DeveloperOrCompanyNotFound(string dev) {
		name = dev;
	}
};

class fileNotOpened { //tratamento de exceçoes
public:
	string name;
	/**
	 * @brief Creates an objecto (exception) of class fileNotFound
	 *
	 * @param n name
	 */
	fileNotOpened(string n) {
		name = n;
	};
	/**
	 * @brief Gets the name
	 *
	 * @returns the name
	 */
	string retname() const {
		return name;
	};
};

class NotAnApp { //Tratamento de  exceçoes
public:
	int id;
	/**
	 * @brief Creates an objecto (exception) of class NotAnApp
	 *
	 * @param n id
	 */
	NotAnApp(int n) {
		id = n;
	};
	/**
	 * @brief Gets the apps id
	 *
	 * @returns returns the apps Id
	 */
	int retid() const {
		return id;
	};
};



/**@}*/

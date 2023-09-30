#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

//files paths
const string fileName = "clientsdata.txt";
const string usresFile = "systemusers.txt";

//structs for all program
struct clientData {
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	float accountBalance;
	bool markToDelete = false;
};
struct UsersData {
	string userName;
	string password;
	int access;
	bool markToDelete = false;
};

//global Vars
UsersData currentUser;

//funcations For All Parts
bool checkAccessPermission(int permission) {
	if (currentUser.access == 0)
		return true;
	if ((permission & currentUser.access) == permission)
		return true;
	else
		return false;
}
void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
	cout << "\n------------------------------------\n";
}

//funcations intilizations
void goBackTOmainMenue();
void PrintMainScreen();
void PrintMangeUserScreen();
void LoginScreen();

//genral funcations that reused many times in clients part
string getAccNumberFromUser() {
	string accNumber;
	cout << "Enter Account Number : ";
	getline(cin >> ws, accNumber);
	cout << endl;
	return accNumber;
}
vector <string> splitStr(string line) {
	vector <string> vString;
	int pos = 0;
	string seprator = "#//#";
	string word = "";
	while ((pos = line.find(seprator)) != std::string::npos)
	{
		word = line.substr(0, pos);
		if (word != "") {
			vString.push_back(word);
		}
		line.erase(0, pos + seprator.length());
	}
	if (line != "") {
		word = line;
		vString.push_back(word);
	}
	return vString;
}
clientData convertLineTOStruct(string line) {
	vector <string> vLine = splitStr(line);
	clientData client;
	client.accountNumber = vLine[0];
	client.pinCode = vLine[1];
	client.name = vLine[2];
	client.phone = vLine[3];
	client.accountBalance = stof(vLine[4]);
	return client;
}
vector <clientData> getLinesFromFileIntoVector(string fileName) {
	vector <clientData> vClients;
	fstream myFile;
	myFile.open(fileName, ios::in);


	if (myFile.is_open()) {
		string line;
		clientData client;
		while (getline(myFile, line))
		{
			client = convertLineTOStruct(line);
			vClients.push_back(client);
		}
		myFile.close();
	}
	return vClients;
}
void ClientCard(clientData client) {
	cout << "Account number  :" << client.accountNumber;
	cout << "\nPine Code       :" << client.pinCode;
	cout << "\nFull Name       :" << client.name;
	cout << "\nPhone Number    :" << client.phone;
	cout << "\nAccount Balance :" << client.accountBalance;
}
bool checkIfaccNumberExist(string accNumber, vector <clientData> vClients, clientData& client) {
	for (clientData c : vClients) {
		if (c.accountNumber == accNumber) {
			client = c;
			return true;
		}
	}
	return false;
}
string convertStructToLine(clientData client) {
	string seprator = "#//#";
	string line = client.accountNumber + seprator + client.pinCode + seprator + client.name
		+ seprator + client.phone + seprator + to_string(client.accountBalance);
	return line;
}
vector <clientData> saveClientsToFile(vector <clientData> vClients, string fileName) {
	fstream myFile;
	myFile.open(fileName, ios::out);

	if (myFile.is_open()) {
		string line;
		for (clientData c : vClients) {
			if (c.markToDelete == false) {
				line = convertStructToLine(c);
				myFile << line << endl;
			}
		}
		myFile.close();
	}
	return vClients;
}


//----------------------Clients Part--------------------------------

//funcations for show all list screen
void PrintEachClientCard(clientData client) {
	cout << "| " << setw(15) << left << client.accountNumber;
	cout << "| " << setw(10) << left << client.pinCode;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(12) << left << client.phone;
	cout << "| " << setw(12) << left << client.accountBalance;
}
void printListoFClients(vector <clientData> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (clientData& client : vClients) {
		PrintEachClientCard(client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void ShowClientsList() {
	if (!checkAccessPermission(1)) {
		ShowAccessDeniedMessage();
		goBackTOmainMenue();
	}

	vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
	printListoFClients(vClients);
}

//funcations for adding new client screen
clientData getNewClientDataFromUser() {
	clientData client;

	cout << "Add New CLient : \n\n";

	cout << "enter account number  : ";
	getline(cin >> ws, client.accountNumber);

	cout << "enter pin code        : ";
	getline(cin >> ws, client.pinCode);

	cout << "enter client name     : ";
	getline(cin >> ws, client.name);

	cout << "enter client phone    : ";
	getline(cin >> ws, client.phone);

	cout << "enter account balance : ";
	cin >> client.accountBalance;

	return client;
}
void saveNewClientToFile(string line, string fileName) {
	fstream myFile;
	myFile.open(fileName, ios::out | ios::app);

	if (myFile.is_open()) {
		myFile << line << endl;
		myFile.close();
	}
}
void addNewClientScreen() {
	
	if (!checkAccessPermission(2)) {
		ShowAccessDeniedMessage();
		goBackTOmainMenue();
	}

	cout << "==========================================\n";
	cout << "\t Add Clients Screen\n";
	cout << "==========================================\n";
	char choice = 'y';
	do {
		clientData client = getNewClientDataFromUser();
		vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
		if (!checkIfaccNumberExist(client.accountNumber, vClients, client)) {
			saveNewClientToFile(convertStructToLine(client), fileName);
			cout << "\nClient Added Successfuly, Add more clients (y/n)? ";
		}
		else {
			cout << "\nThis Account Number Is already Exist ,try Agian (y/n)? ";
		}
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}

// funcations for delete client
bool MarkClientForDeleteByAccountNumber(string accNumber, vector <clientData>& vClients) {
	for (clientData& c : vClients) {
		if (c.accountNumber == accNumber) {
			c.markToDelete = true;
			return true;
		}
	}
	return false;
}
bool DeleteClientByAccNum(string accNumber, vector <clientData>& vClients) {
	clientData client;
	char answer = 'N';

	if (checkIfaccNumberExist(accNumber, vClients, client)) {
		ClientCard(client);

		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			MarkClientForDeleteByAccountNumber(accNumber, vClients);
			saveClientsToFile(vClients, fileName);

			//Refresh Clients
			vClients = getLinesFromFileIntoVector(fileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else {
		cout << "Account number [ " << accNumber << " ] is not exist";
		return false;
	}

}
void deleteClientScreen() {

	if (!checkAccessPermission(4)) {
		ShowAccessDeniedMessage();
		goBackTOmainMenue();
	}

	cout << "==========================================\n";
	cout << "\t Delete Client Screen\n";
	cout << "==========================================\n";
	string accNumber = getAccNumberFromUser();

	vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
	DeleteClientByAccNum(accNumber, vClients);
}

// funcation for Edit client
clientData EditClientRecord(string accNumber) {
	clientData client;
	client.accountNumber = accNumber;

	cout << "\n\nadd new data: \n\n";

	cout << "enter pin code        : ";
	getline(cin >> ws, client.pinCode);

	cout << "enter client name     : ";
	getline(cin >> ws, client.name);

	cout << "enter client phone    : ";
	getline(cin >> ws, client.phone);

	cout << "enter account balance : ";
	cin >> client.accountBalance;

	return client;
}
bool EditClientByAccNum(string accNumber, vector <clientData>& vClients) {
	clientData client;
	char answer = 'N';

	if (checkIfaccNumberExist(accNumber, vClients, client)) {
		ClientCard(client);

		cout << "\n\nAre you sure you want edit this client? y/n ? ";
		cin >> answer;

		if (toupper(answer) == 'Y') {

			for (clientData& c : vClients) {
				if (c.accountNumber == accNumber) {
					c = EditClientRecord(accNumber);
					break;
				}
			}
			saveClientsToFile(vClients, fileName);

			cout << "\n\nClient Edited Successfully.";
			return true;
		}
	}
	else {
		cout << "Account number [ " << accNumber << " ] is not exist";
		return false;
	}
}
void UpdateClientInfoScreen() {
	
	if (!checkAccessPermission(8)) {
		ShowAccessDeniedMessage();
		goBackTOmainMenue();
	}

	cout << "==========================================\n";
	cout << "\t Update Client Screen\n";
	cout << "==========================================\n";
	string accNumber = getAccNumberFromUser();

	vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
	EditClientByAccNum(accNumber, vClients);
}

// funcation for Sreach client
void searchForClient(string accNumber, vector <clientData> vClients, clientData client) {
	if (checkIfaccNumberExist(accNumber, vClients, client))
		ClientCard(client);
	else
		cout << "Client With Account Number [ " << accNumber << " ] is not exist";
}
void printSearchScreen() {

	if (!checkAccessPermission(16)) {
		ShowAccessDeniedMessage();
		goBackTOmainMenue();
	}

	cout << "==========================================\n";
	cout << "\t Find Client Screen\n";
	cout << "==========================================\n";
	string accNumber = getAccNumberFromUser();

	vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
	clientData client;
	searchForClient(accNumber, vClients, client);

}

// funcation for end screen
void printEndScreen() {
	cout << "==========================================\n";
	cout << "\t Program End :-) \n";
	cout << "==========================================\n\n";
}

//-------------------------funcations for transactiona meneu-----------------------

//genral funcations that reused many times in clients part
clientData EditClientBalance(clientData c, float amount) {
	clientData client;
	client.accountNumber = c.accountNumber;
	client.pinCode = c.pinCode;
	client.name = c.name;
	client.phone = c.phone;
	client.accountBalance = c.accountBalance + amount;

	return client;
}
float getAmount() {
	float amount;
	cout << "Enter the Amount : ";
	cin >> amount;
	return amount;
}
void goBackTOTransActionsMenue();

// funcation for Total Balance screen
void PrintEachClientBalance(clientData client) {
	cout << "| " << setw(15) << left << client.accountNumber;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(12) << left << client.accountBalance;
}
void printListoFClientsBalanceOnly(vector <clientData> vClients) {
	float total = 0;
	cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (clientData& client : vClients) {
		PrintEachClientBalance(client);
		cout << endl;
		total += client.accountBalance;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\n\t\t\t\t total amount = " << total << endl;
}
void printTotalBalanceScreen() {
	cout << "==========================================\n";
	cout << "\t Total Balance Screen\n";
	cout << "==========================================\n";

	vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
	printListoFClientsBalanceOnly(vClients);
}

// funcation for Depoist screen
bool depositInAccount(string accNumber, vector <clientData> vClients) {
	clientData client;
	char answer = 'N';

	if (checkIfaccNumberExist(accNumber, vClients, client)) {
		ClientCard(client);

		cout << "\n\nAre you sure you want Depoist in this Account? y/n ? ";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			float deposit = getAmount();
			for (clientData& c : vClients) {
				if (c.accountNumber == accNumber) {
					c = EditClientBalance(c, deposit);
					break;
				}
			}
			saveClientsToFile(vClients, fileName);

			cout << "\n\nDone Successfully, new balance = " << client.accountBalance + deposit;
			return true;
		}
	}
	else {
		cout << "Account number [ " << accNumber << " ] is not exist";
		return false;
	}
}
void printDepositScreen() {
	cout << "==========================================\n";
	cout << "\t Deposit Screen\n";
	cout << "==========================================\n";

	string accNumber = getAccNumberFromUser();
	vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
	depositInAccount(accNumber, vClients);
}

// funcations for Withdraw screen
bool WithDrawFromAccount(string accNumber, vector <clientData> vClients) {
	clientData client;
	char answer = 'N';

	if (checkIfaccNumberExist(accNumber, vClients, client)) {
		ClientCard(client);

		cout << "\n\nAre you sure you want Withdraw from this Account? y/n ? ";
		cin >> answer;

		if (toupper(answer) == 'Y') {
			float Withdraw = getAmount();
			if (client.accountBalance >= Withdraw) {
				for (clientData& c : vClients) {
					if (c.accountNumber == accNumber) {
						c = EditClientBalance(c, -1* Withdraw);
						break;
					}
				}
				saveClientsToFile(vClients, fileName);

				cout << "\n\nDone Successfully, new balance = " << client.accountBalance - Withdraw;
				return true;
			}
			else
				cout << "Sorry but you Can withdraw up to " << client.accountBalance << " only.";
		}
	}
	else {
		cout << "Account number [ " << accNumber << " ] is not exist";
		return false;
	}
}
void printWithDrawScreen() {
	cout << "==========================================\n";
	cout << "\t WithDraw Screen\n";
	cout << "==========================================\n";

	string accNumber = getAccNumberFromUser();
	vector <clientData> vClients = getLinesFromFileIntoVector(fileName);
	WithDrawFromAccount(accNumber, vClients);
	
}

// funcation for print Trans Actions 
void goBasedChoiceInTracAction(int choice) {
	system("cls");
	switch (choice)
	{
	case 1:
		printDepositScreen();
		goBackTOTransActionsMenue();
		break;
	case 2:
		printWithDrawScreen();
		goBackTOTransActionsMenue();
		break;
	case 3:
		printTotalBalanceScreen();
		goBackTOTransActionsMenue();
		break;
	case 4:
		PrintMainScreen();
		break;
	}
}
void PrintTransActionsScreen() {
	
	if (!checkAccessPermission(32)) {
		ShowAccessDeniedMessage();
		goBackTOmainMenue();
	}

	int choice;
	do {
		system("cls");
		cout << "==========================================\n";
		cout << "\t Transactions Screen\n";
		cout << "==========================================\n";
		cout << "\t[1] Deposit.\n";
		cout << "\t[2] Withdrwa.\n";
		cout << "\t[3] Total Balance.\n";
		cout << "\t[4] Main Menue.\n";
		cout << "==========================================\n";
		cout << "Chosse What do you Want to do [1:4] : ";
		cin >> choice;
	} while (choice > 4);
	goBasedChoiceInTracAction(choice);
}
void goBackTOTransActionsMenue() {
	cout << "\n\npress any key to back to TransActions Menue...";
	system("pause>0");
	PrintTransActionsScreen();
}

// funcation for print main screen
void goBasedChoice(int choice) {
	system("cls");
	switch (choice)
	{
	case 1:
		ShowClientsList();
		goBackTOmainMenue();
		break;
	case 2:
		addNewClientScreen();
		goBackTOmainMenue();
		break;
	case 3:
		deleteClientScreen();
		goBackTOmainMenue();
		break;
	case 4:
		UpdateClientInfoScreen();
		goBackTOmainMenue();
		break;
	case 5:
		printSearchScreen();
		goBackTOmainMenue();
		break;
	case 6:
		PrintTransActionsScreen();
		break;
	case 7:
		PrintMangeUserScreen();
		break;
	case 8:
		LoginScreen();
		break;
	}
}
void PrintMainScreen() {
	int choice;
	do {
		system("cls");
		cout << "==========================================\n";
		cout << "\t Main Menue Screen\n";
		cout << "==========================================\n";
		cout << "\t[1] Show Clients List.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client Info.\n";
		cout << "\t[5] Find Client.\n";
		cout << "\t[6] Transactions.\n";
		cout << "\t[7] Manage Users.\n";
		cout << "\t[8] Logout.\n";
		cout << "==========================================\n";
		cout << "Chosse What do you Want to do [1:8] : ";
		cin >> choice;
	} while (choice > 8);
	goBasedChoice(choice);
}
void goBackTOmainMenue() {
	cout << "\n\npress any key to back to Main Menue...";
	system("pause>0");
	PrintMainScreen();
}


// ---------------------------users part--------------------------------

//funcation for users part
UsersData convertUsersLineTOStruct(string line) {
	vector <string> vLine = splitStr(line);
	UsersData user;
	user.userName = vLine[0];
	user.password = vLine[1];
	user.access = stof(vLine[2]);
	return user;
}
vector <UsersData> getLinesFromUsersFileIntoVector(string usresFile) {
	vector <UsersData> vUsers;
	fstream myFile;
	myFile.open(usresFile, ios::in);


	if (myFile.is_open()) {
		string line;
		UsersData user;
		while (getline(myFile, line))
		{
			user = convertUsersLineTOStruct(line);
			vUsers.push_back(user);
		}
		myFile.close();
	}
	return vUsers;
}
bool checkIfUsernameExist(string username, vector <UsersData> vUsers, UsersData& user) {
	for (UsersData c : vUsers) {
		if (c.userName == username) {
			user = c;
			return true;
		}
	}
	return false;
}
string convertUserStructToLine(UsersData user) {
	string seprator = "#//#";
	string line = user.userName + seprator + user.password + seprator + to_string(user.access);
	return line;
}
string getUsernameFromUser() {
	string username;
	cout << "Enter Username : ";
	getline(cin >> ws, username);
	cout << endl;
	return username;
}
void userCard(UsersData user) {
	cout << "Username   :" << " "<< user.userName;
	cout << "\nPassword   :" << " " << user.password;
	cout << "\nPermitions :" << " " << user.access;
}
vector <UsersData> saveUsersToFile(vector <UsersData> vUsers, string usersFile) {
	fstream myFile;
	myFile.open(usersFile, ios::out);

	if (myFile.is_open()) {
		string line;
		for (UsersData c : vUsers) {
			if (c.markToDelete == false) {
				line = convertUserStructToLine(c);
				myFile << line << endl;
			}
		}
		myFile.close();
	}
	return vUsers;
}

//funcations for list all users
void PrintEachUserCard(UsersData user) {
	cout << "| " << setw(15) << left << user.userName;
	cout << "| " << setw(10) << left << user.password;
	cout << "| " << setw(40) << left << user.access;
}
void printListoFUsers(vector <UsersData> vUsers) {
	cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (UsersData& user : vUsers) {
		PrintEachUserCard(user);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void ShowUsersList() {
	vector <UsersData> vUsers = getLinesFromUsersFileIntoVector(usresFile);
	printListoFUsers(vUsers);
}

//funcations for adding new User screen
int detrmineUserAccess(){
	int accessibality = 0;
	char choice;

	cout << "Do you Want to give this User Full Access (y/n)? ";
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		return -1; // have all access
	}

	cout << "show clients List (y/n)";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		accessibality = 1;
	}

	cout << "Add New Client (y/n)";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		accessibality = accessibality + 2;
	}

	cout << "Delete Client (y/n)";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		accessibality = accessibality + 4;
	}

	cout << "Update Client (y/n)";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		accessibality = accessibality + 8;
	}

	cout << "Find Client (y/n)";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		accessibality = accessibality + 16;
	}

	cout << "Open Transaction Menue (y/n)";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		accessibality = accessibality + 32;
	}

	cout << "Manage Users (y/n)";
	cin >> choice;
	if (choice == 'y' || choice == 'Y') {
		accessibality = accessibality + 64;
	}

	return accessibality;
}
UsersData getNewUserDataFromUser() {
	UsersData user;

	cout << "Add New User : \n\n";

	cout << "enter User name  : ";
	getline(cin >> ws, user.userName);

	cout << "enter Password   : ";
	getline(cin >> ws, user.password);

	user.access = detrmineUserAccess();

	return user;
}
void saveNewUsersToFile(string line, string usresFile) {
	fstream myFile;
	myFile.open(usresFile, ios::out | ios::app);

	if (myFile.is_open()) {
		myFile << line << endl;
		myFile.close();
	}
}
void addNewUserScreen() {
	cout << "==========================================\n";
	cout << "\t Add User Screen\n";
	cout << "==========================================\n";
	char choice = 'y';
	do {
		UsersData user = getNewUserDataFromUser();
		vector <UsersData> vUsers = getLinesFromUsersFileIntoVector(usresFile);

		if (!checkIfUsernameExist(user.userName, vUsers, user)) {
			saveNewUsersToFile(convertUserStructToLine(user), usresFile);
			cout << "\nUser Added Successfuly, Add more Users (y/n)? ";
		}
		else {
			cout << "\nThis Username Is already Exist ,try Agian (y/n)? ";
		}
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
}

// funcations for delete user
bool MarkUserForDeleteByAccountNumber(string username, vector <UsersData>& vUsers) {
	for (UsersData& c : vUsers) {
		if (c.userName == username) {
			c.markToDelete = true;
			return true;
		}
	}
	return false;
}
bool DeleteUserByUsername(string username, vector <UsersData>& vUsers) {
	UsersData user;
	char answer = 'N';

	if (checkIfUsernameExist(username, vUsers, user)) {
		userCard(user);

		cout << "\n\nAre you sure you want delete this User? y/n ? ";
		cin >> answer;

		if (answer == 'Y' || answer == 'y') {
			MarkUserForDeleteByAccountNumber(username, vUsers);
			saveUsersToFile(vUsers, usresFile);

			//Refresh Clients
			vUsers = getLinesFromUsersFileIntoVector(usresFile);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else {
		cout << "Account number [ " << username << " ] is not exist";
		return false;
	}

}
void deleteUsersScreen() {
	cout << "==========================================\n";
	cout << "\t Delete Client Screen\n";
	cout << "==========================================\n";
	string username = getUsernameFromUser();
	if (username == "admin") {
		cout << "You cannot Dalete This User";
		return;
	}
	vector <UsersData> vUsers = getLinesFromUsersFileIntoVector(usresFile);
	DeleteUserByUsername(username, vUsers);
}

// funcation for Edit User
UsersData EditUserRecord(string username) {
	UsersData user;
	char fullAccesschoice;

	user.userName = username;

	cout << "\n\nEdit User data: \n\n";

	cout << "enter Password        : ";
	getline(cin >> ws, user.password);

	user.access = detrmineUserAccess();

	return user;
}
bool EditUserByAccNum(string username, vector <UsersData>& vUsers) {
	UsersData user;
	char answer = 'N';

	if (checkIfUsernameExist(username, vUsers, user)) {
		userCard(user);

		cout << "\n\nAre you sure you want edit this user? y/n ? ";
		cin >> answer;

		if (answer == 'Y' || answer == 'y') {

			for (UsersData& c : vUsers) {
				if (c.userName == username) {
					c = EditUserRecord(username);
					break;
				}
			}
			saveUsersToFile(vUsers, usresFile);

			cout << "\n\nuser Edited Successfully.";
			return true;
		}
	}
	else {
		cout << "Account number [ " << username << " ] is not exist";
		return false;
	}
}
void UpdateUserInfoScreen() {
	cout << "==========================================\n";
	cout << "\t Update User Screen\n";
	cout << "==========================================\n";
	string username = getUsernameFromUser();

	vector <UsersData> vUsers = getLinesFromUsersFileIntoVector(usresFile);
	EditUserByAccNum(username, vUsers);
}


// funcation for Find User
void searchForUser(string username, vector <UsersData> vUsers, UsersData user) {
	if (checkIfUsernameExist(username, vUsers, user))
		userCard(user);
	else
		cout << "Client With Account Number [ " << username << " ] is not exist";
}
void printFindUserScreen() {
	cout << "==========================================\n";
	cout << "\t Find User Screen\n";
	cout << "==========================================\n";
	string username = getUsernameFromUser();

	vector <UsersData> vUsers = getLinesFromUsersFileIntoVector(usresFile);
	UsersData user;
	searchForUser(username, vUsers, user);

}


// funcations for mange user screen
void goBackTOUserMangeMenue() {
	cout << "\n\nPress any Key to Back to Mange User Menue...";
	system("pause>0");
	PrintMangeUserScreen();
}
void goBasedChoiceInMangeUser(int choice) {
	system("cls");
	switch (choice)
	{
	case 1:
		ShowUsersList();
		goBackTOUserMangeMenue();
		break;
	case 2:
		addNewUserScreen();
		goBackTOUserMangeMenue();
		break;
	case 3:
		deleteUsersScreen();
		goBackTOUserMangeMenue();
		break;
	case 4:
		UpdateUserInfoScreen();
		goBackTOUserMangeMenue();
		break;
	case 5:
		printFindUserScreen();
		goBackTOUserMangeMenue();
		break;
	case 6:
		PrintMainScreen();
		break;
	}
}
void PrintMangeUserScreen() {
	
	if (!checkAccessPermission(64)) {
		ShowAccessDeniedMessage();
		goBackTOmainMenue();
	}

	int choice;
	do {
		system("cls");
		cout << "==========================================\n";
		cout << "\t Manage Users Menue Screen\n";
		cout << "==========================================\n";
		cout << "\t[1] List Users.\n";
		cout << "\t[2] Add User.\n";
		cout << "\t[3] Delete User.\n";
		cout << "\t[4] Update User.\n";
		cout << "\t[5] Find User.\n";
		cout << "\t[6] Main Menue User.\n";
		cout << "==========================================\n";
		cout << "Chosse What do you Want to do [1:6] : ";
		cin >> choice;
	} while (choice > 6);
	goBasedChoiceInMangeUser(choice);
}

//funcation for Login Screen
bool ValidateLoginData(vector <UsersData> vUsers, UsersData &currentUser) {
	static bool flag = false;
	if (flag == true)
		cout << "***invalid user name or password, pleas try agian***\n\n";

	string username, password;
	cout << "\nEnter your Username :";
	cin >> username;

	cout << "Enter your Password :";
	cin >> password;

	for (UsersData user : vUsers) {
		if (username == user.userName && password == user.password) {
			currentUser = user;
			PrintMainScreen();
			return true;
		}
	}
	system("cls");
	flag = true;
	LoginScreen();
	return false;
}
void LoginScreen() {
	cout << "==========================================\n";
	cout << "\t \t Login Screen\n";
	cout << "==========================================\n";

	vector <UsersData> vUsers = getLinesFromUsersFileIntoVector(usresFile);
	ValidateLoginData(vUsers, currentUser);
}

int main()
{
	LoginScreen();

	return 0;
}
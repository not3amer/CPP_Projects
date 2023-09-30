#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;
 
// file path
const string filePath = "D:\\courses\\Projects_With_C++\\BankProject\\BankProject\\clientsdata.txt";

//structs for program
struct ClientData {
    string accountNumber;
    string pinCode;
    string name;
    string phone;
    float accountBalance;
};

//global Vars
ClientData currentClient;

// some funcations intializations
void Login();
void mainMenueScreen();

//general funcations used many times
vector <string> splitStr(string line) {
    vector <string> vClient;
    string word = "";
    string seprator = "#//#";
    int pos = 0;

    while ((pos = line.find(seprator)) != std::string::npos) {
        word = line.substr(0, pos);
        if (word != "") {
            vClient.push_back(word);
        }
        line.erase(0, pos + seprator.length());
    }
    if (line != "") {
        word = line;
        vClient.push_back(word);
    }
    return vClient;
}
ClientData convertLineToStruct(string line) {
    vector <string> vLine = splitStr(line);
    ClientData client ;

    client.accountNumber = vLine[0];
    client.pinCode = vLine[1];
    client.name = vLine[2];
    client.phone = vLine[3];
    client.accountBalance = stof(vLine[4]);
   
    return client;
}
vector <ClientData> getClientsDataIntoVector() {
    fstream myFile;
    myFile.open(filePath, ios::in);

    vector <ClientData> vClients;
    if (myFile.is_open())
    {
        ClientData client;
        string line;
        while (getline(myFile,line))
        {
            client = convertLineToStruct(line);
            vClients.push_back(client);
        }
        myFile.close();
    }
    return vClients;
}
string convertStructToLine(ClientData client) {
    string seprator = "#//#";
    string line = client.accountNumber + seprator + client.pinCode + seprator + client.name +
        seprator + client.phone + seprator + to_string(client.accountBalance);
    return line;
}
void saveEditsToFile(string fileName) {
    vector <ClientData> vClients = getClientsDataIntoVector();
    fstream myFile;
    myFile.open(filePath, ios::out);
    if (myFile.is_open()) {
        string line;
        for (ClientData &c : vClients) {
            if (c.accountNumber == currentClient.accountNumber) {
                c = currentClient;
                line = convertStructToLine(c);
                myFile << line << endl;
            }
            else
            {
                line = convertStructToLine(c);
                myFile << line << endl;
            }
            
        }
        myFile.close();
    }
  
}


//[1] funcations for quick withdraw screen
void performWithdraw(int amount) {
    char answer;
    cout << "\nAre you sure you Want to do this Transaction (y/n) ?";
    cin >> answer;

    if (answer == 'y' || answer == 'Y')
    {
        if (amount > currentClient.accountBalance) 
            cout << "Sorry but you Can Withdraw up to " << currentClient.accountBalance << " Only\n";
        else {
            currentClient.accountBalance -= amount;
            cout << "Done Successfuly, Your Balance Now : " << currentClient.accountBalance;
        }
    }
    else
        cout << "Transaction Failed.";
    
}
void performQuickWithdrawBasedOnChoice(int choice) {
    switch (choice)
    {
    case 1:
        performWithdraw(20);
        break;
    case 2:
        performWithdraw(50);
        break;
    case 3:
        performWithdraw(100);
        break;
    case 4:
        performWithdraw(200);
        break;
    case 5:
        performWithdraw(400);
        break;
    case 6:
        performWithdraw(600);
        break;
    case 7:
        performWithdraw(800);
        break;
    case 8:
        performWithdraw(1000);
        break;
    case 9:
        system("cls");
        mainMenueScreen();
        break;
    }
}
void quickWithdrawScreen() {
    int choice = 1;
    do {
        if (choice < 1 || choice > 9) {
            system("cls");
        }
        cout << "=================================\n";
        cout << "\tQuick Withdraw Screen\n";
        cout << "=================================\n";

        cout << "\t[1] 20\t\t[2] 50\n";
        cout << "\t[3] 100\t\t[4] 200\n";
        cout << "\t[5] 400\t\t[6] 600\n";
        cout << "\t[7] 800\t\t[8] 1000\n";
        cout << "\t[9] Exit.\n";
        cout << "=================================\n";
        cout << "Enter What do you Want to do [1:9] : ";
        cin >> choice;
    } while (choice < 1 || choice > 9);
    performQuickWithdrawBasedOnChoice(choice);
    saveEditsToFile(filePath);
}


//[2] funcations for quick withdraw screen
void normalWithdrawScreen() {
    int amount = 1;
    do {
        if (amount < 0 && amount % 5 == 0) {
            system("cls");
        }
        cout << "=================================\n";
        cout << "\tNormal Withdraw Screen\n";
        cout << "=================================\n";
        cout << "Enter an Amount multiple of 5 : ";
        cin >> amount;
    } while (amount < 0 && amount %5 == 0);
    performWithdraw(amount);
    saveEditsToFile(filePath);

}

//[3] funcations for print Deposit screen
void performDeposit(int amount) {
    currentClient.accountBalance += amount;
    cout << "Done Successfuly, Your Balance Now : " << currentClient.accountBalance;
}
void depositScreen() {
    int amount = 1;
    do {
        if (amount < 0) {
            system("cls");
        }
        cout << "=================================\n";
        cout << "\tDeposit Screen\n";
        cout << "=================================\n";
        cout << "Enter a Positive Deposit Amount : ";
        cin >> amount;
    } while (amount < 0);
    
    char answer;
    cout << "\nAre you sure you Want to do this Transaction (y/n) ?";
    cin >> answer;

    if (answer == 'y' || answer == 'Y') {
        performDeposit(amount);
        saveEditsToFile(filePath);
    }
    else
        cout << "Transaction Failed.";
}

//[4] funcations for print check balance screen
void checkBalanceScreen() {
    cout << "=================================\n";
    cout << "\tCheck Balance Screen\n";
    cout << "=================================\n";
    cout << "\nYour Account Balance : " << currentClient.accountBalance;
}

//funcations for print main menue screen
void goBackToMainMenue() {
    cout << "\n\npress any key to back to TransActions Menue...";
    system("pause>0");
    system("cls");
    mainMenueScreen();
}
void goBasedChoice(int choice) {
    switch (choice)
    {
    case 1:
        system("cls");
        quickWithdrawScreen();
        goBackToMainMenue();
        break;
    case 2:
        system("cls");
        normalWithdrawScreen();
        goBackToMainMenue();
        break;
    case 3:
        system("cls");
        depositScreen();
        goBackToMainMenue();
        break;
    case 4:
        system("cls");
        checkBalanceScreen();
        goBackToMainMenue();
        break;
    case 5:
        system("cls");
        Login();
        break;
    }
}
void mainMenueScreen() {
    int choice = 1;
    do {
        if (choice < 1 || choice > 5) {
            system("cls");
        }
        cout << "=================================\n";
        cout << "\tATM Main Menue Screen\n";
        cout << "=================================\n";
    
        cout << "\t[1] Quick Withdrwa.\n";
        cout << "\t[2] Normal Withdrwa.\n";
        cout << "\t[3] Deposit.\n";
        cout << "\t[4] Check Balance.\n";
        cout << "\t[5] Logout.\n";
        cout << "=================================\n";
        cout << "Enter What do you Want to do [1:5] : ";
        cin >> choice;
    } while (choice < 1 || choice > 5);
    goBasedChoice(choice);
}

//funcations for login screen
void getAccNumberAndPinCodeFromUser(string &accNumber, string& pinCode) {
    cout << "Enter your Account Number :";
    cin >> accNumber;

    cout << "Enter your Pin Code :";
    cin >> pinCode;
}
bool CheckLoginData(string accNumber, string pinCode, ClientData& currentClient) {
    vector <ClientData> vClients = getClientsDataIntoVector();
    for (ClientData& c : vClients) {
        if (c.accountNumber == accNumber && c.pinCode == pinCode) {
            currentClient = c;
            return true;
        }
    }
    return false;
}
void Login() {
    bool loginfield = true;
    string accNumber, pinCode;

    do {
        system("cls");
        cout << "---------------------------------\n";
        cout << "\t   Login Screen\n";
        cout << "---------------------------------\n";
        
        if (!loginfield) {
            cout << "******* invalid account number or pincode *******\n\n";
        }
        
        getAccNumberAndPinCodeFromUser(accNumber, pinCode);
        loginfield = CheckLoginData(accNumber, pinCode, currentClient);
    } while (!loginfield);
    system("cls");
    mainMenueScreen();

}

int main()
{
    Login();
    
    return 0;
}
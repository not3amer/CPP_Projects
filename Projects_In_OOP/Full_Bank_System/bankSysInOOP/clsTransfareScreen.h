#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsTransfareScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient& Client) {
        cout << "--------------------------------\n";
        cout << "Full Name      : " << Client.FullName() << endl;
        cout << "Account Number : " << Client.AccountNumber() << endl;
        cout << "Account Balance: " << Client.AccountBalance << endl;
        cout << "--------------------------------\n";
    }
   
    static double _getAmount() {
        double Amount;
        cout << "\nEnter the Amount : ";
        cin >> Amount;
        return Amount;
    }

public:
	static void ShowTransfareScreen() {
        clsScreen::_DrawScreenHeader("\t   Transfare Screen");

        cout << "Enter Account Number to Transfare From: ";
        string AccountNumber1 = clsInputValidate::ReadString();

        while ((!clsBankClient::IsExist(AccountNumber1))) {
            cout << "Account not Exist, Enter Correct Account Number : ";
            AccountNumber1 = clsInputValidate::ReadString();
        }

        cout << "\nAccount Data:\n";
        clsBankClient Client = clsBankClient::Find(AccountNumber1);
        _PrintClient(Client);


        cout << "\nEnter Account Number to Transfare To: ";
        string AccountNumber2 = clsInputValidate::ReadString();

        while ((!clsBankClient::IsExist(AccountNumber2))) {
            cout << "Account not Exist, Enter Correct Account Number : ";
            AccountNumber2 = clsInputValidate::ReadString();
        }

        cout << "\nAccount Data:\n";
        clsBankClient Client2 = clsBankClient::Find(AccountNumber2);
        _PrintClient(Client2);

        
        double Amount = _getAmount();

        cout << "\nAre you Want do this Transfare (Y/N) ? ";
        char Answer;
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y') {
            while (Client.MakeTransfare(Client2, Amount)) {
                cout << "Amount Exceeds the Avaliable Balance, Enter Another Amount : ";
                cin >> Amount;
            }
            cout << "\nTransfare Done Successfully.\n\n";
            _PrintClient(Client);
            _PrintClient(Client2);
            
        }
        else {
            cout << "Transfare Failed :-(";
        }
        
	}
};


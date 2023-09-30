#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDepositScreen : protected clsScreen
{
private:
    static void _PrintClient(clsBankClient& Client) {
        cout << "--------------------------------\n";
        cout << "First Name     : " << Client.FirstName << endl;
        cout << "Last Name      : " << Client.LastName << endl;
        cout << "Full Name      : " << Client.FullName() << endl;
        cout << "Email          : " << Client.Email << endl;
        cout << "Phone          : " << Client.Phone << endl;
        cout << "Account Number : " << Client.AccountNumber() << endl;
        cout << "Pin Code       : " << Client.PinCode << endl;
        cout << "Account Balance: " << Client.AccountBalance << endl;
        cout << "--------------------------------\n";
    }
    static string _ReadAccountNumber() {
        cout << "Enter Account Number : ";
        return clsInputValidate::ReadString();
    }
public:
	static void ShowDepositScreen() {
        clsScreen::_DrawScreenHeader("\t   Deposit Screen");
        string AccountNumber = _ReadAccountNumber();

        while ((!clsBankClient::IsExist(AccountNumber))) {
            cout << "Account not Exist, Enter Correct Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        cout << "\nAccount Data:\n";
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char choice;
        cout << "\nAre you want Deposit in this Account (Y/N)? ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            double Amount;
            cout << "Enter Amount : ";
            cin >> Amount;
            Client.Deposit(Amount);
            cout << "Amount Added Successfully Your Balance : " << Client.AccountBalance;
        }
	}
};


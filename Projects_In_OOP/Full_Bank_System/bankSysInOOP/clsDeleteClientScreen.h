#pragma once
#include<iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsDeleteClientScreen : protected clsScreen
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
public:
    static void DeleteClient() {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }
        clsScreen::_DrawScreenHeader("Delete Client Screen");
        string AccountNumber = "";

        cout << "Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while ((!clsBankClient::IsExist(AccountNumber))) {
            cout << "Account not Exist, Enter Correct Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char choice;
        cout << "\nAre you want delete this Account (Y/N)? ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (Client.Delete()) {
                cout << "\nclient deleted successfully.\n";
                _PrintClient(Client);
            }
            else
                cout << "\nError in Delete Client\n";
        }
    }
};


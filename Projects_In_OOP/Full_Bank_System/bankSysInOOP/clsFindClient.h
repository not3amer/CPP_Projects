#pragma once
#include<iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsFindClient : protected clsScreen
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
    static void ShowFindClientScreen() {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;// this will exit the function and it will not continue
        }
        clsScreen::_DrawScreenHeader("Find Client Screen");
        string AccountNumber = "";

        cout << "Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while ((!clsBankClient::IsExist(AccountNumber))) {
            cout << "Account not Exist, Enter Correct Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        cout << "\nAccount Data:\n";
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
    }
};


#pragma once
#include<iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsUpdateClientScreen :protected clsScreen
{
private:
    static void _readClientInfo(clsBankClient& Client) {
        cout << "Enter Your First Name     : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "Enter Your Last Name      : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "Enter Your Email          : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "Enter Your Phone          : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "Enter Your Pin Code       : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter Your Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();

    }
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
    static void UpdateClient() {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }
        clsScreen::_DrawScreenHeader("Update Client Screen");
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

        char choice;
        cout << "\nAre you want Edit this Account (Y/N)? ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            _readClientInfo(Client);
            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client.Save();
            switch (SaveResult)
            {
            case clsBankClient::svFailedEmptyObject:
                cout << "\nError Account not Saved Because Object is Empty.\n";
                _PrintClient(Client);
                break;
            case clsBankClient::svSucceeded:
                cout << "\nClient Successfully Saved.";
                break;
            }
        }        
    }
};


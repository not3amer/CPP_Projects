#pragma once
#include<iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsAddNewClient : protected clsScreen
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
    static void AddNewClient() {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }
        clsScreen::_DrawScreenHeader("Add New Client Screen");
        string AccountNumber = "";

        cout << "Enter Account Number : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsExist(AccountNumber)) {
            cout << "Account is Exist, Enter New Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient NewClient = clsBankClient::getAddNewModeObject(AccountNumber);
        _readClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResults;
        SaveResults = NewClient.Save();
        switch (SaveResults)
        {
        case clsBankClient::svFailedEmptyObject:
            cout << "\nAccount was not Save Because it^s Empty Object.";
            break;
        case clsBankClient::svSucceeded:
            cout << "\nAccount Added Successfully.";
            break;
        case clsBankClient::svFailedExistAccNumber:
            cout << "\nAccount was not Save Because Account Number Is Exist.";
            break;
        }
    }
};


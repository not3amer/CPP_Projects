#pragma once

#include <iostream>
#include <fstream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "GlobalVars.h"
#include "clsUtil.h"
#include "clsDate.h"
class clsLoginScreen : protected clsScreen
{
private:
    
    
	static bool _Login() {
        bool LoginFaild = false;
        bool flag = true;
        string Username, Password;
        short counter = 0;
        do
        {

            if (LoginFaild)
            {
                counter ++;
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "You have " << 3 - counter<< " Trials to Login\n";
            }
            if (counter == 3) {
                cout << "You are Locked After 3 Trails.\n\n";
                return false;
            }
                
            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;
            

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);
        CurrentUser.AddLogToFile();
        system("cls");
        clsMainScreen::ShowMainMenue();
	}
public:

	static bool ShowLoginScreen() {
		system("cls");
		_DrawScreenHeader("\t    LoginScreen");
		return _Login();
	}
};


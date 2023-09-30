#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransfareScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionMenueScreen : protected clsScreen
{
private:
    enum enTransactionMenueOptions {
        eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3,
        eTransfare=4 ,eTransfareLog=5 ,eShowMainMenue = 6
    };

    static short _ReadTransactionMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6 ? ");
        return Choice;
    }
    static  void _GoBackToTransactionMenue()
    {
        cout << "\n\nPress any key to go back to Transaction Menue...\n";

        system("pause>0");
        system("cls");
        ShowTransactionMenue();
    }

    static void _ShowDepositScreen()
    {
       // cout << "\nDeposit Screen Will be here...\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        //cout << "\nWithdraw Screen Will be here...\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalanceScreen()
    {
       // cout << "\nTotal Balance Screen Will be here...\n";
        clsTotalBalanceScreen::ShowTotalBalances();
    }

    static void _ShowTransfareScreen() {
        //cout << "\nTransfare Screen Will be here...\n";
        clsTransfareScreen::ShowTransfareScreen();
    }

    static void _ShowTransfaresLogScreen() {
       // cout << "\nTransfare log Screen Will be here...\n";
        clsTransferLogScreen::ShowLoginRegisterScreen();
    }

    static void _PerfromTransactionMenueOption(enTransactionMenueOptions TransactionMenueOption) {
        switch (TransactionMenueOption)
        {
        case enTransactionMenueOptions::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionMenue();
            break;
        case enTransactionMenueOptions::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionMenue();
            break;
        case enTransactionMenueOptions::eShowTotalBalance:
            system("cls");
            _ShowTotalBalanceScreen();
            _GoBackToTransactionMenue();
            break;
        case enTransactionMenueOptions::eTransfare:
            system("cls");
            _ShowTransfareScreen();
            _GoBackToTransactionMenue();
            break;
        case enTransactionMenueOptions::eTransfareLog:
            system("cls");
            _ShowTransfaresLogScreen();
            _GoBackToTransactionMenue();
            break;
        case enTransactionMenueOptions::eShowMainMenue:

            break;
        }
    }
public:
    static void ShowTransactionMenue() {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            return;// this will exit the function and it will not continue
        }
        clsScreen::_DrawScreenHeader("\t   Transaction Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tTransaction Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balance.\n";
        cout << setw(37) << left << "" << "\t[4] Transfare.\n";
        cout << setw(37) << left << "" << "\t[5] Transfares Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromTransactionMenueOption((enTransactionMenueOptions)_ReadTransactionMenueOption());
    }
};


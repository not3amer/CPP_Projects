#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "CurrencyCalculatorScreen.h"
class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:
    enum enCurrencyExchangeMenueOptions {
        eListCurrencies = 1, eFindCurrency = 2, eUpdateRate = 3,
        eCurrencyCalculator = 4, eShowMainMenue = 5
    };

    static short _ReadCurrencyExchangeMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5 ? ");
        return Choice;
    }
    static  void _GoBackToCurrencyExchangeMenue()
    {
        cout << "\n\nPress any key to go back to Currency Exchange Menue...\n";

        system("pause>0");
        system("cls");
        ShowExchangeMenue();
    }

    static void _ShowListCurrenciesScreen()
    {
        //cout << "\nList Currencies Screen Will be here...\n";
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
       // cout << "\nFind Currency Screen Will be here...\n";
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        //cout << "\nUpdate Rate Screen Will be here...\n";
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen() {
        //cout << "\nCurrency Calculator Screen Will be here...\n";
        CurrencyCalculatorScreen::ShowCurrencyCalculator();
    }
    static void _PerfromCurrencyExchangeMenueOption(enCurrencyExchangeMenueOptions CurrencyExchangeMenueOption) {
        switch (CurrencyExchangeMenueOption)
        {
        case enCurrencyExchangeMenueOptions::eListCurrencies:
            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        case enCurrencyExchangeMenueOptions::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        case enCurrencyExchangeMenueOptions::eUpdateRate:
            system("cls");
           _ShowUpdateRateScreen();
           _GoBackToCurrencyExchangeMenue();
            break;
        case enCurrencyExchangeMenueOptions::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrencyExchangeMenue();
            break;
        case enCurrencyExchangeMenueOptions::eShowMainMenue:

            break;
        }
    }
public:
    static void ShowExchangeMenue() {
        if (!CheckAccessRights(clsUser::enPermissions::pCurrencyExchange))
        {
            return;// this will exit the function and it will not continue
        }
        clsScreen::_DrawScreenHeader("    Currency Exchange Main Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tCurrency Exchange Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator .\n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrencyExchangeMenueOption((enCurrencyExchangeMenueOptions)_ReadCurrencyExchangeMenueOption());
    }
};
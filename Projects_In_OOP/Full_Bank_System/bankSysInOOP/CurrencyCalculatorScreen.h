#pragma once
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"
class CurrencyCalculatorScreen : protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }
public:
	static void ShowCurrencyCalculator() {
        char Answer = 'y';
        while (Answer == 'y' || Answer == 'Y') {
            system("cls");
            _DrawScreenHeader("\tUpdate Currency Screen");

            string CurrencyCode1 = "";
            cout << "\nPlease Enter Currency Code: ";
            CurrencyCode1 = clsInputValidate::ReadString();
            while (!clsCurrency::IsCurrencyExist(CurrencyCode1))
            {
                cout << "\nCurrency is not found, choose another one: ";
                CurrencyCode1 = clsInputValidate::ReadString();
            }
            clsCurrency Currency1 = clsCurrency::FindByCode(CurrencyCode1);

            string CurrencyCode2 = "";
            cout << "\nPlease Enter Currency Code: ";
            CurrencyCode2 = clsInputValidate::ReadString();
            while (!clsCurrency::IsCurrencyExist(CurrencyCode2))
            {
                cout << "\nCurrency is not found, choose another one: ";
                CurrencyCode2 = clsInputValidate::ReadString();
            }
            clsCurrency Currency2 = clsCurrency::FindByCode(CurrencyCode2);

            cout << "\nEnter the Amount : ";
            float Amount = clsInputValidate::ReadFloatNumber();


            _PrintCurrency(Currency1);

            cout << Amount << " " << Currency1.CurrencyCode() << " = "
                << Currency1.CurrencyCalculator(Currency2, Amount) << " " << Currency2.CurrencyCode();


            cout << "\n\nDo you Want Perform Another Calculation (Y/N) ? ";
            cin >> Answer;
        }
        
	}
};


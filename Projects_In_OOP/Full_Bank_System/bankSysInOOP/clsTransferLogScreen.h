#pragma once
#include "clsScreen.h"
#include <iomanip>
#include "clsBankClient.h"
class clsTransferLogScreen : protected clsScreen
{
private:

    static void _PrintTransferLogsRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
    {
        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(10) << left << TransferLogRecord.sAccount;
        cout << "| " << setw(10) << left << TransferLogRecord.dAccount;
        cout << "| " << setw(10) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.sBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.dBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.userName;
    }

public:

    static void ShowLoginRegisterScreen()
    {

        vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogsList();

        string Title = "\tTransfer Logs List Screen";
        string SubTitle = "\t\t(" + to_string(vTransferLogRecord.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Account";
        cout << "| " << left << setw(10) << "D.Account";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(10) << "Username";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
            {

                _PrintTransferLogsRecordLine(Record);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};


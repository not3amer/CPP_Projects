#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsString.h"
#include "clsPerson.h"
class clsBankClient :public clsPerson
{
private:
	enum enMood { EmptyMode = 0, UpdateMode = 1, AddNewMode=2};
	enMood _Mood;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkToDelete = false;

	static clsBankClient _EmptyObject() {
		clsBankClient EClient(enMood::EmptyMode,"","","","","","",0);
		return EClient;
	}
	static clsBankClient _ConvertLineToObject(string line) {
		vector <string> vLine = clsString::Split(line, "#//#");
		return clsBankClient(enMood::UpdateMode,vLine[0], vLine[1], vLine[2], vLine[3], vLine[4], vLine[5], stod(vLine[6]));
	}
	static vector <clsBankClient> _LoadFileLinesFromFileToObject() {
		vector <clsBankClient> vClients;

		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open()){
			string line;
			while (getline(myFile,line)) {
				clsBankClient Client = _ConvertLineToObject(line);
				vClients.push_back(Client);
			}
			myFile.close();
		}
		return vClients;
	}
	string _ConvertObjectToLine(clsBankClient c) {
		string seprator = "#//#";
		return c.FirstName + seprator + c.LastName + seprator + c.Email + seprator + c.Phone + seprator
			+ c._AccountNumber + seprator + c.PinCode + seprator + to_string(c.AccountBalance);
	}
	void _SaveClientsFromObjectToFile(vector <clsBankClient> vClients) {

		fstream myFile;
		myFile.open("Clients.txt", ios::out);
		string Line;
		if (myFile.is_open()) {
			for (clsBankClient& c : vClients) {
				if (!c.MarkToDelete) {
					Line = _ConvertObjectToLine(c);
					myFile << Line << endl;
				}
				
			}
			myFile.close();
		}
	}
	void _Update() {
		vector <clsBankClient> _vClients;
		_vClients = _LoadFileLinesFromFileToObject();

		for(clsBankClient &c : _vClients)
		{
			if (c._AccountNumber == AccountNumber()) {
				c = *this;
				break;
			}
		}
		_SaveClientsFromObjectToFile(_vClients);
	}
	void _AddNew() {
		fstream myFile;
		myFile.open("Clients.txt", ios::out | ios::app);

		string Line;

		if (myFile.is_open()) {
			Line = _ConvertObjectToLine(*this);
			myFile << Line << endl;
			myFile.close();
		}
	}
	string _ConvertTransfareLogToLine(clsBankClient c2,double Amount ) {
		string seprator = "#//#";
		return clsDate::getSystemTime() + seprator + AccountNumber() + seprator 
			+ c2.AccountNumber() + seprator + to_string(Amount) + seprator
			+ to_string(AccountBalance) + seprator + to_string(c2.AccountBalance)
			+seprator + CurrentUser.UserName ;
	}
	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogToStruct(string Line, string Seperator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;

		vector <string> vTransferLogLine = clsString::Split(Line, Seperator);
		TransferLogRecord.DateTime = vTransferLogLine[0];
		TransferLogRecord.sAccount = vTransferLogLine[1];
		TransferLogRecord.dAccount = vTransferLogLine[2];
		TransferLogRecord.Amount = stod(vTransferLogLine[3]);
		TransferLogRecord.sBalance = stod(vTransferLogLine[4]);
		TransferLogRecord.dBalance = stod(vTransferLogLine[5]);
		TransferLogRecord.userName = vTransferLogLine[6];

		return TransferLogRecord;

	}
	
	
public:
	clsBankClient (enMood mood,string firstName, string lastName, string email, string phone
		, string accNumber, string pinCode, float accBalance)
		: clsPerson(firstName, lastName, email, phone)
	{
		_Mood = mood;
		_AccountNumber = accNumber;
		_PinCode = pinCode;
		_AccountBalance = accBalance;
	}

	struct stTransferLogRecord
	{
		string DateTime;
		string sAccount;
		string dAccount;
		double Amount;
		double sBalance;
		double dBalance;
		string userName;
	};
	string AccountNumber() {
		return _AccountNumber;
	}

	void setPinCode(string pincode) {
		_PinCode = pincode;
	}
	string getPinecode() {
		return _PinCode;
	}
	__declspec(property(get = getPinecode, put = setPinCode))string PinCode;

	void setAccountBalance(float accBalance) {
		_AccountBalance = accBalance;
	}
	float getAccountBalance() {
		return _AccountBalance;
	}
	__declspec(property(get = getAccountBalance, put = setAccountBalance))float AccountBalance;

	void setMarkToDelete(bool Mark) {
		_MarkToDelete = Mark;
	}
	bool getMarkToDelete() {
		return _MarkToDelete;
	}
	__declspec(property(get = getMarkToDelete, put = setMarkToDelete))bool MarkToDelete;

	
	bool isEmpty() {
		return (_Mood == enMood::EmptyMode);
	}
	static bool IsExist(string accountNumber) {
		clsBankClient Client = clsBankClient::Find(accountNumber);
		return (!Client.isEmpty());
	}
	static clsBankClient Find(string accountNumber) {
		vector <clsBankClient> vClients = _LoadFileLinesFromFileToObject();
		for (clsBankClient c : vClients) {
			if (c._AccountNumber == accountNumber) {
				return c;
			}
		}
		return _EmptyObject();
	}
	static clsBankClient Find(string accountNumber,string PinCode) {
		vector <clsBankClient> vClients = _LoadFileLinesFromFileToObject();
		for (clsBankClient c : vClients) {
			if (c._AccountNumber == accountNumber && c._PinCode == PinCode) {
				return c;
			}
		}
		return _EmptyObject();
	}
	enum enSaveResults{svFailedEmptyObject = 0, svSucceeded = 1, svFailedExistAccNumber =2};
	enSaveResults Save() {
		switch (_Mood)
		{
		case enMood::EmptyMode:
			return enSaveResults::svFailedEmptyObject;
		case enMood::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case enMood::AddNewMode:
			if (clsBankClient::IsExist(_AccountNumber)) {
				return enSaveResults::svFailedExistAccNumber;
			}
			else {
				_AddNew();
				_Mood = enMood::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
	}
	static clsBankClient getAddNewModeObject(string accountNumber) {
		return clsBankClient(enMood::AddNewMode,"","","","", accountNumber,"",0);
	}
	
	bool Delete() {
		vector <clsBankClient> vClients;
		vClients = _LoadFileLinesFromFileToObject();
		
		for (clsBankClient& c : vClients) {
			if (c.AccountNumber() == _AccountNumber) {
				c._MarkToDelete = true;
				break;
			}
		}
		_SaveClientsFromObjectToFile(vClients);
		*this = _EmptyObject();
		return true;
		
	}
	

	static vector <clsBankClient> GetClientsList() {
		return _LoadFileLinesFromFileToObject();
	}


	void Deposit(double Amount) {
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount) {
		if (Amount > _AccountBalance)
			return false;
		else {
			_AccountBalance -= Amount;
			Save();
		}
	}
	static double GetTotalBalances() {
		double TotalBalances = 0;
		vector <clsBankClient> vClients;
		vClients = _LoadFileLinesFromFileToObject();

		for (clsBankClient& c : vClients)
		{
			TotalBalances += c.AccountBalance;
		}
		return TotalBalances;
	}

	bool MakeTransfare(clsBankClient &c2, double Amount) {
		if (Amount > AccountBalance)
		{
			return true;
		}
		Withdraw(Amount);
		c2.Deposit(Amount);
		AddLogToFile(c2, Amount);
		return false;
	}

	void AddLogToFile(clsBankClient c2, double Amount) {
        string Line = _ConvertTransfareLogToLine(c2,Amount);

        fstream myFile;
        myFile.open("TransfareLogs.txt", ios::out | ios::app);

        if (myFile.is_open()) {
            myFile << Line << endl;
            myFile.close();
        }
    }
	static  vector <stTransferLogRecord> GetTransferLogsList()
	{
		vector <stTransferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransfareLogs.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTransferLogRecord TransferLogRecord;

			while (getline(MyFile, Line))
			{

				TransferLogRecord = _ConvertTransferLogToStruct(Line);

				vTransferLogRecord.push_back(TransferLogRecord);

			}

			MyFile.close();

		}

		return vTransferLogRecord;

	}
};


#pragma once
#include<iostream>
using namespace std;

class clsPerson {
private:
    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;
public:
    clsPerson(string firstName, string lastName, string email, string phone) {
        _FirstName = firstName;
        _LastName = lastName;
        _Email = email;
        _Phone = phone;
    }

    void setFirstName(string first) {
        _FirstName = first;
    }
    string getFirstName() {
        return _FirstName;
    }
    __declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

    void setLastName(string last) {
        _LastName = last;
    }
    string getLastName() {
        return _LastName;
    }
    __declspec(property(get = getLastName, put = setLastName)) string LastName;

    void setEmail(string email) {
        _Email = email;
    }
    string getEmail() {
        return _Email;
    }
    __declspec(property(get = getEmail, put = setEmail)) string Email;

    void setPhone(string phone) {
        _Phone = phone;
    }
    string getPhone() {
        return _Phone;
    }
    __declspec(property(get = getPhone, put = setPhone)) string Phone;

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }
};

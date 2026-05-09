#ifndef AUTH_H
#define AUTH_H

#pragma once
#include <iostream>
#include "Account.h"
#include "Checker.h"
#include "Encryption.h"
using namespace std;

class AuthSystem
{

private:

	Account* account;
	validation* validator;

public:

	AuthSystem(Account* accountPtr, validation* validatorPtr = nullptr) // I wrote nullptr for the validator because i want to make it optional
	{
		account = accountPtr;
		validator = validatorPtr;
	}

	void registerUser(string e, string p)
	{
		if (validator != nullptr)
		{
			if (!validator->checkPassword(p))
			{
				cout << "Password does not meet the requirements. Please try again." << endl;
				return;
			}
		}
		
		if (e != account->email)
		{
			account->email = e;
			account->email_password_combined = enc(e, p);
			account->isLoggedIn = true;
			account->exists = true;

			cout << "Signup successful!" << endl;

			account->setUsername();
			account->setNickname();
		}

		else
		{
			cout << "An account with this email already exists. Please try again." << endl;
		}
	}

	void authenticate(string e, string p)
	{
		if (!account->exists)
		{
			cout << "No Account found with this email. Please register first." << endl;
			return;
		}

		string decrypted = dec(account->email_password_combined, account->email.length());
		string input = e + ":" + p;

		if (input == decrypted)
		{
			account->isLoggedIn = true;
			cout << "Login successful!" << endl;
		}

		else
		{
			while (true)
			{
				cout << "Incorrect email or password. Please try again." << endl;
				cout << "if you want to exit, type 'exit' in email or password." << endl;
				cout << "Email: ";
				cin >> e;

				if (e == "exit")
				{
					cout << "Exiting login process." << endl;
					return;
				}

				cout << "Password: ";
				cin >> p;

				if (p == "exit")
				{
					cout << "Exiting login process." << endl;
					return;
				}

				if ((e + ":" + p) == dec(account->email_password_combined, account->email.length()))
				{
					account->isLoggedIn = true;
					cout << "Login successful!" << endl;
					break;
				}
			}
		}
	}

	void logout()
	{
		if (account->isLoggedIn)
		{
			account->isLoggedIn = false;
			cout << "Logout successful!" << endl;

		}
	}

	void del()
	{
		char answer;
		
		if (account->isLoggedIn)
		{
			cout << "Would you want to delete your account? y/n: ";
			cin >> answer;

			if (answer == 'y' || answer == 'Y')
			{
				account->exists = false;
				account->isLoggedIn = false;

				account->email.clear();
				account->username.clear();
				account->nickname.clear();
				account->email_password_combined.clear();

				cout << "Delete successful!" << endl;
			}
		}
	}
};

#endif
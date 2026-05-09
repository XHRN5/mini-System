#ifndef SETTINGS_H
#define SETTINGS_H

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Account.h"
#include "Encryption.h"
using namespace std;

class settings
{
private:

	Account* account;

public:

	settings(Account* accountPtr)
	{
		account = accountPtr;
	}

	void exportBackup()
	{
		if (account->canAccess())
		{
			ofstream outFile("backup.txt");
			if (outFile.is_open())
			{
				outFile << account->email << endl;
				outFile << account->email_password_combined << endl;
				outFile << account->username << endl;
				outFile << account->nickname << endl;
				outFile.close();
				cout << "Backup exported successfully!" << endl;
			}

			else
			{
				cout << "Error: Unable to create backup file." << endl;
			}
		}

		else
		{
			cout << "Error: You must be logged in to export. File was not modified." << endl;
		}
	}

	void importBackup()
	{
		ifstream inFile("backup.txt");
		
		string savedEmail;
		string savedPassword;
		string savedUsername;
		string savedNickname;

		getline(inFile, savedEmail);
		getline(inFile, savedPassword);
		getline(inFile, savedUsername);
		getline(inFile, savedNickname);

		account->email = savedEmail;
		account->email_password_combined = savedPassword;
		account->username = savedUsername;
		account->nickname = savedNickname;

		account->exists = true;
		account->isLoggedIn = false;
	}

	void changeUsername(string newUsername)
	{
		if (account->isLoggedIn)
		{
			account->username = newUsername;

			//cout << "Username updated to: " << account->getUsername() << endl;
		}
	}

	void changeNickname(string newNickname)
	{
		if (account->isLoggedIn)
		{
			account->nickname = newNickname;
		}
	}

	void changeEmail(string newEmail)
	{
		if (account->canAccess())
		{
			// 1. Decrypt the current combined string to get the current password

			string decrypted = dec(account->email_password_combined, account->email.length());
			size_t colonPos = decrypted.find(':');
			string currentPassword = decrypted.substr(colonPos + 1);

			// 2. Update the email in the account

			account->email = newEmail;

			// 3. Re-encrypt the combined string with the new email and current password

			account->email_password_combined = enc(newEmail, currentPassword);

			// 4. Update the username based on the new email

			account->setUsername();

			cout << "Email updated and re-encrypted successfully!" << endl;
		}
	}

	void changePassword(string newPassword)
	{
		if (account->canAccess())
		{
			account->email_password_combined = enc(account->email, newPassword);

			cout << "Password updated and re-encrypted successfully!" << endl;
		}
	}


};

#endif
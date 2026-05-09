#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class AuthSystem;
class settings;

//This to tell the compiler that these classes will be defined later, allowing us to use them as friends in the Account class without needing their full definitions at this point.

class Account
{

	friend AuthSystem;
	friend settings;

public:

	string getCombined() const
	{
		return canAccess() ? email_password_combined : "";
	}

	string getEmail() const
	{
		return canAccess() ? email : "";
	}
	
	string getNickname() const
	{
		return canAccess() ? nickname : "";
	}

	string getUsername() const
	{
		return canAccess() ? username : "";
	}

private:

		string email;
		string email_password_combined;
		//string password;
		string username;
		string nickname;
		bool isLoggedIn = false;
		bool exists = false;
		
		bool canAccess() const
		{
			return exists && isLoggedIn;
		}

		void setNickname()
		{	
			if (canAccess())
			{
				int randomNum = rand() % 1000000;

				nickname = "U-" + to_string(randomNum);
			}
		}
		
		void setUsername()
		{
			if (canAccess())
			{
				size_t pos = email.find('@');
				if (pos != string::npos)
				{
					username = email.substr(0, pos);
					//cout << "Username set to: " << username << endl;
				}
			}
		}
		
		
};

#endif
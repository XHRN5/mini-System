#ifndef CHECKER_H
#define CHECKER_H

#pragma once
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class validation
{

private:

	int minLen = 0;
	int maxLen = 100;
	int reqDigits = 0;
	int reqSpecial = 0;

public:

	enum passwordRules
	{
		MIN_LENGTH,
		MAX_LENGTH,
		REQUIRED_DIGITS,
		REQUIRED_SPECIAL_CHAR
	};

	void setPasswordRule(passwordRules rule, int value)
	{
		switch (rule)
		{
		case MIN_LENGTH:
			minLen = value;
			break;

		case MAX_LENGTH:
			maxLen = value;
			break;

		case REQUIRED_DIGITS:
			reqDigits = value;
			break;

		case REQUIRED_SPECIAL_CHAR:
			reqSpecial = value;
			break;
		}
	}

	bool checkPassword(const string& password)
	{
		bool isValid = true;
		int digitCount = 0;
		int specialCount = 0;

		if (password.length() < minLen)
		{
			cout << "Error: Password must be at least " << minLen << " Characters" << endl;
			isValid = false;
		}

		if (password.length() > maxLen)
		{
			cout << "Error: Password must not exceed " << maxLen << " Characters" << endl;
			isValid = false;
		}

		for (char ch : password)
		{
			if (isdigit(ch))
			{
				digitCount++;
			}

			if (ispunct(ch))
			{
				specialCount++;
			}
		}

		if (digitCount < reqDigits)
		{
			cout << "Error: Password needs at least " << reqDigits << " digits" << endl;
			isValid = false;
		}

		if (specialCount < reqSpecial)
		{
			cout << "Error: Password needs at least " << reqSpecial << " Special characters" << endl;
			isValid = false;
		}


		return isValid;
	}
};

#endif
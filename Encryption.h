#include <iostream>
#include <fstream>
using namespace std;

#pragma once
inline string enc(string email, string password) // i wrote inline for the enc and dec functions because they are small and we want to avoid function call overhead, especially since they might be called frequently in the authentication process.
{
	char dynamicKey = (char)email.length();

	string combined = email + ":" + password;

	for (int i = 0; i < combined.size(); i++)
	{
		combined[i] ^= (dynamicKey);
	}

	return combined;
}

inline string dec(string encryptedData, int emailLength)
{
    
    char dynamicKey = (char)emailLength;

    string decrypted = encryptedData;

    for (int i = 0; i < decrypted.size(); i++)
    {
        decrypted[i] ^= (dynamicKey);
    }

    return decrypted;
}
#include <iostream>
#include <string>
#include "Account.h"
#include "Auth.h"
#include "Checker.h"
#include "Encryption.h"
#include "Settings.h"

using namespace std;

int main()
{
    // 1. Initialize Password Validation Rules
    validation validator;
    validator.setPasswordRule(validation::MIN_LENGTH, 6);
    validator.setPasswordRule(validation::REQUIRED_DIGITS, 1);
    validator.setPasswordRule(validation::REQUIRED_SPECIAL_CHAR, 1);

    // 2. Initialize Core Objects
    Account myAccount;
    AuthSystem auth(&myAccount, &validator);
    settings userSettings(&myAccount);

    int choice;
    string emailIn, passIn;

    do {
        cout << "\n======================================" << endl;
        cout << "      ADVANCED AUTH SYSTEM (V2)       " << endl;
        cout << "======================================" << endl;
        cout << "1. Register New Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Change Password" << endl;
        cout << "4. Change Email (Updates Encryption Key)" << endl;
        cout << "5. Export Backup (To File)" << endl;
        cout << "6. Import Backup (From File)" << endl;
        cout << "7. Show Memory State (Encrypted Data)" << endl;
        cout << "8. Logout" << endl;
        cout << "9. Delete Account" << endl;
        cout << "0. Exit" << endl;
        cout << "--------------------------------------" << endl;
        cout << "Selection: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Email: "; cin >> emailIn;
            cout << "Password: "; cin >> passIn;
            auth.registerUser(emailIn, passIn);
            break;

        case 2:
            cout << "Email: "; cin >> emailIn;
            cout << "Password: "; cin >> passIn;
            auth.authenticate(emailIn, passIn);
            break;

        case 3:
            cout << "New Password: "; cin >> passIn;
            userSettings.changePassword(passIn);
            break;

        case 4:
            cout << "New Email: "; cin >> emailIn;
            userSettings.changeEmail(emailIn);
            break;

        case 5:
            userSettings.exportBackup();
            break;

        case 6:
            userSettings.importBackup();
            break;

        case 7:
            // Using public getters since main is not a 'friend'
            if (myAccount.getCombined() != "") {
                cout << "\n--- Current RAM State ---" << endl;
                cout << "Username: " << myAccount.getUsername() << endl;
                cout << "Nickname: " << myAccount.getNickname() << endl;
                cout << "XOR Combined Data: " << myAccount.getCombined() << endl;
            }
            else {
                cout << "[!] No data available in RAM. Please login first." << endl;
            }
            break;

        case 8:
            auth.logout();
            break;

        case 9:
            auth.del();
            break;

        case 0:
            cout << "Exiting system..." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
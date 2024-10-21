#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include <process.h>
#include <dos.h>
#include "menu.h"
#include "FinanceManagerImpl.h"
#include "menu.cpp"
#include "FinanceManagerImpl.cpp"
#include "FinanceManager.cpp"
#include "Income.cpp"
#include "Transaction.cpp"
#include "Debt.cpp"
#include "Asset.cpp"
#include "Final.cpp"
#include "Expense.cpp"
#include "Username.cpp"

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayLoginMenu() {
    cout << "\n\t\t\t1. Login" << endl;
    cout << "\t\t\t2. Exit" << endl;
    cout << "\t\t\tEnter your choice => ";
}

void displayWelcomeMessage() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

    cout << "\n\n\t            ";
    cout << "     C++ Personal Financial Management System";
    cout << "\n\n\t\t\t\t     MADE BY";
    cout << "\n**************************";
    cout << "************************";
    cout << "||\t\t\t\t\t\t\t\t\t      ||";
    cout << "||\t\t\t\t\t\t\t\t\t      ||";
    cout << "||\t\t\t\tMbuso Masinda\t\t\t      ||";
    cout << "||\t\t\t\t\t\t\t\t\t      ||";
    cout << "||\t\t\t\t\t\t\t\t\t      ||";
    cout << "**************************";
    cout << "***********************";
    cout << endl;
    cout << "\n\n\nPlease Enter your correct username and password to access PFMS" << endl;
    cout << "	\n\n\n	Connecting to Server...\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "	Server Successfully connected." << endl;
}

void loginAndAuthenticate(bool& isAuthenticated, bool& isAdmin, std::string& username) {
    while (!isAuthenticated) {
        displayLoginMenu();
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout << endl;

        if (choice == 1) {
            string password;
            cout << "\n\n\t\t\t|Enter username => ";
            cin >> username;
            cout << "\n\t\t\t|Enter password => ";
            cin >> password;

            if (AuthenticateUser(username, password)) {
                isAuthenticated = true;
                isAdmin = IsAdmin(username);
                cout << endl << "\n\n\t\t\t  !!!Login Successful!!!" << endl;
                cout << "	\n\n\n	Connecting to Account\n 	Syncing Data";
                for (int i = 0; i < 10; ++i) {
                    cout << ".";
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
                cout << endl;
                clearScreen();
            } else {
                cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!" << endl << endl;
            }
        } else if (choice == 2) {
            cout << "	\n\n\n	Disconnecting server...\n";
            #ifdef _WIN32
                Sleep(5000);
            #else
                std::this_thread::sleep_for(std::chrono::seconds(5));
            #endif
            cout << "	Exiting the program..." << endl;
            exit(0);
        } else {
            cout << "Invalid choice." << endl << endl;
        }
    }
}

void handleAdminActions(bool& isAuthenticated) {
    while (true) {
        cout << "Admin Menu:" << endl;
        cout << "1. Add User as Admin" << endl;
        cout << "2. Add User as Regular User" << endl;
        cout << "3. Remove User" << endl;
        cout << "4. View Users" << endl;
        cout << "5. Edit User" << endl;
        cout << "6. Search User" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cout << endl;

        if (choice == 1) {
            AddUser(true); // Admin user
        } else if (choice == 2) {
            AddUser(false); // Regular user
        } else if (choice == 3) {
            RemoveUser(); // Remove user
        } else if (choice == 4) {
            ViewUsers(); // View all users
        } else if (choice == 5) {
            EditUser(); // Edit user
        } else if (choice == 6) {
            SearchUser(); // Search user by username
        } else if (choice == 7) {
            cout << "Logging out." << endl << endl;
            isAuthenticated = false;
            clearScreen();
            break; // Logout and return to login page
        } else {
            cout << "Invalid choice." << endl << endl;
        }
    }
}

double getValidAmount() {
    double amount;
    while (true) {
        cout << "Enter the amount: R";
        if (cin >> amount) {
            if (amount >= 0) break;
            else cout << "Amount must be non-negative. Please try again." << endl;
        } else {
            cout << "Invalid input. Amount must be a number. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return amount;
}

void handleUserActions(FinanceManagerImpl& financeManager, bool& isAuthenticated) {
    while (true) {
        displayMenu();
        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        clearScreen();

        switch (choice) {
            case 1: {
                double amount = getValidAmount();
                string type, description, date;
                cout << "        *******INCOME RECORD********       " << endl;
                cout << "Enter the Date(dd-mm-yy): ";
                cin.ignore();
                getline(cin, date);
                cout << "Enter the type of income: ";
                getline(cin, type);
                cout << "Enter a description: ";
                getline(cin, description);
                cout << endl;
                financeManager.addIncome(amount, type, description, date);
                cout << "Press Enter to return to the menu...";
                cin.get();
                clearScreen();
                break;
            }
            case 2: {
                double amount = getValidAmount();
                string category, description, date;
                cout << "        *******EXPENSE RECORD********       " << endl;
                cout << "Enter the Date: ";
                cin.ignore();
                getline(cin, date);
                cout << "Enter the category of expense: ";
                getline(cin, category);
                cout << "Enter a description: ";
                getline(cin, description);
                financeManager.addExpense(amount, category, description, date);
                cout << "Press Enter to return to the menu...";
                cin.get();
                clearScreen();
                break;
            }
            case 3: {
                double amount = getValidAmount();
                string description, date;
                cout << "        *******ADD DEBT********       " << endl;
                cout << "Enter the Date: ";
                cin.ignore();
                getline(cin, date);
                cout << "Enter a description: ";
                getline(cin, description);
                financeManager.addDebt(amount, description, date);
                cout << "Press Enter to return to the menu...";
                cin.get();
                clearScreen();
                break;
            }
            case 4: {
                int index;
                cout << "        *******REMOVE DEBT********       " << endl;
                while (true) {
                    cout << "Enter the index of the debt to remove: ";
                    if (cin >> index) {
                        break;
                    } else {
                        cout << "Invalid input. Index must be a number. Please try again." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                financeManager.removeDebt(index);
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                clearScreen();
                break;
            }
            case 5: {
                double amount = getValidAmount();
                string description, date;
                cout << "        *******ADD ASSET********       " << endl;
                cout << "Enter the Date: ";
                cin.ignore();
                getline(cin, date);
                cout << "Enter a description: ";
                getline(cin, description);
                financeManager.addAsset(amount, description, date);
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                clearScreen();
                break;
            }
            case 6: {
                int index;
                cout << "        *******REMOVE ASSET********       " << endl;
                while (true) {
                    cout << "Enter the index of the asset to remove: ";
                    if (cin >> index) {
                        break;
                    } else {
                        cout << "Invalid input. Index must be a number. Please try again." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                financeManager.removeAsset(index);
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                clearScreen();
                break;
            }
            case 7: {
                financeManager.displaySummary();
                cout << "Press Enter to return to the menu...";
                cin.ignore();
                cin.get();
                clearScreen();
                break;
            }
            case 8:
                isAuthenticated = false;
                clearScreen();
                break; // Logout and return to login page
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        if (!isAuthenticated) break;
    }
}

void createUserDirectory(const string& username) {
    string path = "user_data/" + username;
    #ifdef _WIN32
    _mkdir(path.c_str());
    #else
    mkdir(path.c_str(), 0755);
    #endif
}

void adminFunctions() {
    cout << "\n\t\t\tEnter Username: ";
    string username;
    cin >> username;

    // Create user directory and transaction file
    createUserDirectory(username);
    string filePath = "user_data/" + username + "/" + username + "_transactions.csv";

    FinanceManagerImpl financeManager(filePath);

    while (true) {
        cout << "\n\t\t\t1. Add Debt" << endl;
        cout << "\t\t\t2. Remove Debt" << endl;
        cout << "\t\t\t3. Add Asset" << endl;
        cout << "\t\t\t4. Remove Asset" << endl;
        cout << "\t\t\t5. Display Summary" << endl;
        cout << "\t\t\t6. Exit" << endl;
        cout << "\t\t\tEnter your choice => ";
        int choice;
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            double amount;
            string description, date;
            cout << "\t\t\tEnter amount: ";
            cin >> amount;
            cout << "\t\t\tEnter description: ";
            cin.ignore();
            getline(cin, description);
            cout << "\t\t\tEnter date (YYYY-MM-DD): ";
            cin >> date;
            financeManager.addDebt(amount, description, date);
        } else if (choice == 2) {
            int index;
            cout << "\t\t\tEnter debt index to remove: ";
            cin >> index;
            financeManager.removeDebt(index);
        } else if (choice == 3) {
            double amount;
            string description, date;
            cout << "\t\t\tEnter amount: ";
            cin >> amount;
            cout << "\t\t\tEnter description: ";
            cin.ignore();
            getline(cin, description);
            cout << "\t\t\tEnter date (YYYY-MM-DD): ";
            cin >> date;
            financeManager.addAsset(amount, description, date);
        } else if (choice == 4) {
            int index;
            cout << "\t\t\tEnter asset index to remove: ";
            cin >> index;
            financeManager.removeAsset(index);
        } else if (choice == 5) {
            financeManager.displaySummary();
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}

int main() {
    while (true) {
        displayWelcomeMessage();

        bool isAuthenticated = false;
        bool isAdmin = false;
        std::string username;
        loginAndAuthenticate(isAuthenticated, isAdmin, username);

        if (isAdmin) {
            handleAdminActions(isAuthenticated);
        } else {
            FinanceManagerImpl financeManager(username);
            handleUserActions(financeManager, isAuthenticated);
            string filePath = "user_data/" + username + "/" + username + "_transactions.csv";
        }
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h> // For directory creation
#include <sys/types.h>

#ifdef _WIN32
#include <direct.h> // For Windows directory creation
#endif

using namespace std;

// User structure
struct User {
    string username;
    string password;
    bool isAdmin;
    string phoneNumber;
    string email;
    string bankNumber;
    string name;
    string surname;
    string idNumber;
};

// Function to create directory if it doesn't exist
void create_directory(const string& dir) {
#ifdef _WIN32
    if (_mkdir(dir.c_str()) != 0) {
        cerr << "Error creating directory: " << dir << endl;
    }
#else
    struct stat info;
    if (stat(dir.c_str(), &info) != 0) {
        // Directory does not exist, create it
        if (mkdir(dir.c_str(), 0777) != 0) {
            cerr << "Error creating directory: " << dir << endl;
        }
    }
#endif
}

// Function to read users from the binary file
vector<User> ReadUsers() {
    vector<User> users;
    ifstream file("user_data/users.dat", ios::binary);
    if (file.is_open()) {
        while (true) {
            User user;
            size_t usernameSize, passwordSize, phoneNumberSize, emailSize, bankNumberSize, nameSize, surnameSize, idNumberSize;
            file.read(reinterpret_cast<char*>(&usernameSize), sizeof(usernameSize));
            if (file.eof()) break;
            user.username.resize(usernameSize);
            file.read(&user.username[0], usernameSize);

            file.read(reinterpret_cast<char*>(&passwordSize), sizeof(passwordSize));
            user.password.resize(passwordSize);
            file.read(&user.password[0], passwordSize);

            file.read(reinterpret_cast<char*>(&user.isAdmin), sizeof(user.isAdmin));

            file.read(reinterpret_cast<char*>(&phoneNumberSize), sizeof(phoneNumberSize));
            user.phoneNumber.resize(phoneNumberSize);
            file.read(&user.phoneNumber[0], phoneNumberSize);

            file.read(reinterpret_cast<char*>(&emailSize), sizeof(emailSize));
            user.email.resize(emailSize);
            file.read(&user.email[0], emailSize);

            file.read(reinterpret_cast<char*>(&bankNumberSize), sizeof(bankNumberSize));
            user.bankNumber.resize(bankNumberSize);
            file.read(&user.bankNumber[0], bankNumberSize);

            file.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
            user.name.resize(nameSize);
            file.read(&user.name[0], nameSize);

            file.read(reinterpret_cast<char*>(&surnameSize), sizeof(surnameSize));
            user.surname.resize(surnameSize);
            file.read(&user.surname[0], surnameSize);

            file.read(reinterpret_cast<char*>(&idNumberSize), sizeof(idNumberSize));
            user.idNumber.resize(idNumberSize);
            file.read(&user.idNumber[0], idNumberSize);

            users.push_back(user);
        }
        file.close();
    }
    return users;
}

// Function to write users to the binary file
void WriteUsers(const vector<User>& users) {
    create_directory("user_data"); // Ensure directory exists

    ofstream file("user_data/users.dat", ios::binary);
    if (file.is_open()) {
        for (const User& user : users) {
            size_t usernameSize = user.username.size();
            size_t passwordSize = user.password.size();
            size_t phoneNumberSize = user.phoneNumber.size();
            size_t emailSize = user.email.size();
            size_t bankNumberSize = user.bankNumber.size();
            size_t nameSize = user.name.size();
            size_t surnameSize = user.surname.size();
            size_t idNumberSize = user.idNumber.size();

            file.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
            file.write(user.username.c_str(), usernameSize);

            file.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
            file.write(user.password.c_str(), passwordSize);

            file.write(reinterpret_cast<const char*>(&user.isAdmin), sizeof(user.isAdmin));

            file.write(reinterpret_cast<const char*>(&phoneNumberSize), sizeof(phoneNumberSize));
            file.write(user.phoneNumber.c_str(), phoneNumberSize);

            file.write(reinterpret_cast<const char*>(&emailSize), sizeof(emailSize));
            file.write(user.email.c_str(), emailSize);

            file.write(reinterpret_cast<const char*>(&bankNumberSize), sizeof(bankNumberSize));
            file.write(user.bankNumber.c_str(), bankNumberSize);

            file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
            file.write(user.name.c_str(), nameSize);

            file.write(reinterpret_cast<const char*>(&surnameSize), sizeof(surnameSize));
            file.write(user.surname.c_str(), surnameSize);

            file.write(reinterpret_cast<const char*>(&idNumberSize), sizeof(idNumberSize));
            file.write(user.idNumber.c_str(), idNumberSize);
        }
        file.close();
    } else {
        cout << "Error opening file." << endl;
    }
}

// Function to authenticate a user
bool AuthenticateUser(const string& username, const string& password) {
    vector<User> users = ReadUsers();
    for (const User& user : users) {
        if (user.username == username && user.password == password) {
            return true;
        }
    }
    return false;
}

// Function to check if a user is an admin
bool IsAdmin(const string& username) {
    vector<User> users = ReadUsers();
    for (const User& user : users) {
        if (user.username == username && user.isAdmin) {
            return true;
        }
    }
    return false;
}

// Function to add a new user (admin-only)
void AddUser(bool isAdmin) {
    string username, password, phoneNumber, email, bankNumber, name, surname, idNumber;
    cout << "Enter new username: ";
    cin >> username;

    // Check if the user already exists
    vector<User> users = ReadUsers();
    for (const User& user : users) {
        if (user.username == username) {
            cout << "User '" << username << "' already exists." << endl;
            return;
        }
    }

    cout << "Enter new password: ";
    cin >> password;
    cout << "Enter phone number: ";
    cin >> phoneNumber;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter bank number: ";
    cin >> bankNumber;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter surname: ";
    cin >> surname;
    cout << "Enter ID number: ";
    cin >> idNumber;

    users.push_back({username, password, isAdmin, phoneNumber, email, bankNumber, name, surname, idNumber});
    WriteUsers(users);
    cout << "User added successfully!" << endl << endl;
}

// Function to remove a user (admin-only)
void RemoveUser() {
    string username;
    cout << "Enter username to remove: ";
    cin >> username;

    vector<User> users = ReadUsers();
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->username == username) {
            users.erase(it);
            WriteUsers(users);
            cout << "User '" << username << "' removed." << endl << endl;
            return;
        }
    }
    cout << "User not found." << endl << endl;
}

// Function to view all users (admin-only)
void ViewUsers() {
    vector<User> users = ReadUsers();
    cout << "Users:" << endl;
    for (size_t i = 0; i < users.size(); ++i) {
        cout << i + 1 << ". " << users[i].username << endl;
    }

    cout << "Enter the number of the user to view details (or 0 to go back): ";
    int userIndex;
    cin >> userIndex;

    if (userIndex == 0) {
        cout << "Returning to the previous menu." << endl << endl;
        return;
    }

    if (userIndex < 1 || userIndex > users.size()) {
        cout << "Invalid selection." << endl << endl;
        return;
    }

    const User& user = users[userIndex - 1];
    cout << endl;
    cout << "Username: " << user.username << endl;
    cout << "Password: " << user.password << endl;
    cout << "Role: " << (user.isAdmin ? "Admin" : "User") << endl;
    cout << "Phone Number: " << user.phoneNumber << endl;
    cout << "Email: " << user.email << endl;
    cout << "Bank Number: " << user.bankNumber << endl;
    cout << "Name: " << user.name << endl;
    cout << "Surname: " << user.surname << endl;
    cout << "ID Number: " << user.idNumber << endl << endl;
}

// Function to edit a user (admin-only)
void EditUser() {
    string username;
    cout << "Enter username to edit: ";
    cin >> username;

    vector<User> users = ReadUsers();
    for (User& user : users) {
        if (user.username == username) {
            cout << "Select field to edit:" << endl;
            cout << "1. Username" << endl;
            cout << "2. Password" << endl;
            cout << "3. Role" << endl;
            cout << "4. Phone Number" << endl;
            cout << "5. Email" << endl;
            cout << "6. Bank Number" << endl;
            cout << "7. Name" << endl;
            cout << "8. Surname" << endl;
            cout << "9. ID Number" << endl;
            cout << "Enter your choice: ";
            int editChoice;
            cin >> editChoice;

            if (editChoice == 1) {
                string newUsername;
                cout << "Enter new username: ";
                cin >> newUsername;
                user.username = newUsername;
                cout << "Username changed successfully!" << endl << endl;
            } else if (editChoice == 2) {
                string newPassword;
                cout << "Enter new password: ";
                cin >> newPassword;
                user.password = newPassword;
                cout << "Password changed successfully!" << endl << endl;
            } else if (editChoice == 3) {
                string newRole;
                cout << "Enter new role (admin/user): ";
                cin >> newRole;
                user.isAdmin = (newRole == "admin");
                cout << "Role changed successfully!" << endl << endl;
            } else if (editChoice == 4) {
                string newPhoneNumber;
                cout << "Enter new phone number: ";
                cin >> newPhoneNumber;
                user.phoneNumber = newPhoneNumber;
                cout << "Phone number changed successfully!" << endl << endl;
            } else if (editChoice == 5) {
                string newEmail;
                cout << "Enter new email: ";
                cin >> newEmail;
                user.email = newEmail;
                cout << "Email changed successfully!" << endl << endl;
            } else if (editChoice == 6) {
                string newBankNumber;
                cout << "Enter new bank number: ";
                cin >> newBankNumber;
                user.bankNumber = newBankNumber;
                cout << "Bank number changed successfully!" << endl << endl;
            } else if (editChoice == 7) {
                string newName;
                cout << "Enter new name: ";
                cin >> newName;
                user.name = newName;
                cout << "Name changed successfully!" << endl << endl;
            } else if (editChoice == 8) {
                string newSurname;
                cout << "Enter new surname: ";
                cin >> newSurname;
                user.surname = newSurname;
                cout << "Surname changed successfully!" << endl << endl;
            } else if (editChoice == 9) {
                string newIdNumber;
                cout << "Enter new ID number: ";
                cin >> newIdNumber;
                user.idNumber = newIdNumber;
                cout << "ID number changed successfully!" << endl << endl;
            } else {
                cout << "Invalid choice." << endl << endl;
            }

            WriteUsers(users);
            return;
        }
    }
    cout << "User not found." << endl << endl;
}

// Function to search for a user by username (admin-only)
void SearchUser() {
    string username;
    cout << "Enter username to search: ";
    cin >> username;

    vector<User> users = ReadUsers();
    for (const User& user : users) {
        if (user.username == username) {
            cout << endl;
            cout << "User found:" << endl;
            cout << "Username: " << user.username << endl;
            cout << "Password: " << user.password << endl;
            cout << "Role: " << (user.isAdmin ? "Admin" : "User") << endl;
            cout << "Phone Number: " << user.phoneNumber << endl;
            cout << "Email: " << user.email << endl;
            cout << "Bank Number: " << user.bankNumber << endl;
            cout << "Name: " << user.name << endl;
            cout << "Surname: " << user.surname << endl;
            cout << "ID Number: " << user.idNumber << endl << endl;
            return;
        }
    }
    cout << "User not found." << endl << endl;
}

int mainUser() {
    while (true) {
        cout << "Welcome to User Management System!" << endl;
        cout << "1. Login" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            // Authenticate user
            if (AuthenticateUser(username, password)) {
                if (IsAdmin(username)) {
                    cout << "Admin authenticated successfully!" << endl << endl;
                    // Admin Menu
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
                        int adminChoice;
                        cin >> adminChoice;
                        cout << endl;

                        if (adminChoice == 1) {
                            AddUser(true); // Admin user
                        } else if (adminChoice == 2) {
                            AddUser(false); // Regular user
                        } else if (adminChoice == 3) {
                            RemoveUser(); // Remove user
                        } else if (adminChoice == 4) {
                            ViewUsers(); // View all users
                        } else if (adminChoice == 5) {
                            EditUser(); // Edit user
                        } else if (adminChoice == 6) {
                            SearchUser(); // Search user by username
                        } else if (adminChoice == 7) {
                            cout << "Logging out." << endl << endl;
                            break; // Logout
                        } else {
                            cout << "Invalid choice." << endl << endl;
                        }
                    }
                } else {
                    cout << "\n\n\t\t\t  !!!Login Successful!!!" << endl << endl;
                    // Regular User Menu (Add user-specific functionalities here)
                }
            } else {
                cout << "\n\n\t\t\t!!!INVALID CREDENTIALS!!!" << endl << endl;
            }
        } else if (choice == 2) {
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Invalid choice." << endl << endl;
        }
    }

    return 0;
}

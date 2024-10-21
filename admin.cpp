#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Username.cpp"
using namespace std;
/*
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

void create_admin_file() {
    // Sample admin user data
    User admin = {
        "adminuser",          // username
        "adminpassword",      // password
        true,                 // isAdmin
        "1234567890",         // phoneNumber
        "admin@example.com", // email
        "987654321",         // bankNumber
        "Admin",             // name
        "User",              // surname
        "ID123456"           // idNumber
    };

    // Create and write to the admin.dat file
    ofstream file("user_data/admin.dat", ios::binary);
    if (file.is_open()) {
        // Write each field in binary format
        size_t usernameSize = admin.username.size();
        size_t passwordSize = admin.password.size();
        size_t phoneNumberSize = admin.phoneNumber.size();
        size_t emailSize = admin.email.size();
        size_t bankNumberSize = admin.bankNumber.size();
        size_t nameSize = admin.name.size();
        size_t surnameSize = admin.surname.size();
        size_t idNumberSize = admin.idNumber.size();

        file.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
        file.write(admin.username.c_str(), usernameSize);

        file.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
        file.write(admin.password.c_str(), passwordSize);

        file.write(reinterpret_cast<const char*>(&admin.isAdmin), sizeof(admin.isAdmin));

        file.write(reinterpret_cast<const char*>(&phoneNumberSize), sizeof(phoneNumberSize));
        file.write(admin.phoneNumber.c_str(), phoneNumberSize);

        file.write(reinterpret_cast<const char*>(&emailSize), sizeof(emailSize));
        file.write(admin.email.c_str(), emailSize);

        file.write(reinterpret_cast<const char*>(&bankNumberSize), sizeof(bankNumberSize));
        file.write(admin.bankNumber.c_str(), bankNumberSize);

        file.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
        file.write(admin.name.c_str(), nameSize);

        file.write(reinterpret_cast<const char*>(&surnameSize), sizeof(surnameSize));
        file.write(admin.surname.c_str(), surnameSize);

        file.write(reinterpret_cast<const char*>(&idNumberSize), sizeof(idNumberSize));
        file.write(admin.idNumber.c_str(), idNumberSize);

        file.close();
        cout << "Admin data written to admin.dat" << endl;
    } else {
        cerr << "Error opening file for writing." << endl;
    }
}

int main() {
    create_admin_file();
    return 0;
}*/
void DebugPrintUsers() {
    vector<User> users = ReadUsers();
    for (const User& user : users) {
        cout << "Username: " << user.username << endl;
        cout << "Password: " << user.password << endl;
        cout << "Is Admin: " << (user.isAdmin ? "Yes" : "No") << endl;
        cout << "===================================" << endl;
    }
}

int main() {
    DebugPrintUsers(); // Call this to print the loaded user data for debugging
    // Rest of your main function...
}

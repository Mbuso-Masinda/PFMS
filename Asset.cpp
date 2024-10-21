#include "Asset.h"
#include <iostream>
#include <iomanip>
using namespace std;

Asset::Asset(double amount, const string& description, const string& date)
    : Transaction(amount, description,date) {}

void Asset::displayTransaction() const {
    cout << date << setw(10) << "Asset" << fixed << setw(10) << "R" << amount << setw(10) << "-" << setw(20) << description << endl;
}

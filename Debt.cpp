#include "Debt.h"
#include <iostream>
#include <iomanip>
using namespace std;

Debt::Debt(double amount, const string& description, const string& date)
    : Transaction(amount, description, date) {}

void Debt::displayTransaction() const {
    cout << date << setw(10) << "Debt" << fixed << setw(10) << "R" << amount << setw(10) << "-" << setw(20) << description << endl;
}

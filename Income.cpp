#include "Income.h"
#include <iostream>
#include <iomanip>
using namespace std;
Income::Income(double amount, const string& type, const string& description, const string& date)
    : Transaction(amount, description,date), type(type) {}

void Income::displayTransaction() const {
    cout <<date <<setw(10) << "Income" << fixed << setprecision(2) << setw(10) << "R" << amount << setw(10) << type << setw(20) << description << endl;
}

const string& Income::getType() const {
    return type;
}

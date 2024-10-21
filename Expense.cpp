#include "Expense.h"
#include <iostream>
#include <iomanip>
using namespace std;
Expense::Expense(double amount, const string& category, const string& description, const string& date)
    : Transaction(amount, description,date), category(category) {}

void Expense::displayTransaction() const {
    cout <<date <<setw(10) << "Expense" << fixed << setw(10) << "R" << amount << setw(10) << category << setw(20) << description << endl;
}

const string& Expense::getCategory() const {
    return category;
}

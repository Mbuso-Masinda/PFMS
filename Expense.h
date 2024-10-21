// Expense.h

#ifndef EXPENSE_H
#define EXPENSE_H

#include "Transaction.h"
#include <string>
using namespace std;

class Expense : public Transaction {
private:
    string category;

public:
    Expense(double amount, const string& category, const string& description,const string& date);

    void displayTransaction() const override;
    const string& getCategory() const;
};

#endif

// Income.h

#ifndef INCOME_H
#define INCOME_H
using namespace std;
#include "Transaction.h"
#include <string>

class Income : public Transaction {
private:
    string type;

public:
    Income(double amount, const string& type, const string& description, const string& date);

    void displayTransaction() const override;
    const string& getType() const;
};

#endif

// Transaction.h

#ifndef TRANSACTION_H
#define TRANSACTION_H
using namespace std;
#include <string>

class Transaction {
protected:
    double amount;
    string description;
    string date;

public:
    Transaction(double amount, const string& description, const string& date);

    virtual void displayTransaction() const = 0;
    double getAmount() const;
    const string& getDescription() const;
    const string& getDate() const;
};

#endif

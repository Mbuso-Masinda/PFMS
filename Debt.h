// Debt.h

#ifndef DEBT_H
#define DEBT_H
using namespace std;
#include "Transaction.h"

class Debt : public Transaction {
public:
    Debt(double amount, const string& description, const string& date);

    void displayTransaction() const override;
};

#endif

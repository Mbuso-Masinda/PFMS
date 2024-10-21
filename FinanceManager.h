// FinanceManager.h

#ifndef FINANCEMANAGER_H
#define FINANCEMANAGER_H
using namespace std;
#include "Transaction.h"
#include <vector>

class FinanceManager {
protected:
    vector<Transaction*> transactions;

public:
    virtual ~FinanceManager();

    virtual void addIncome(double amount, const string& type, const string& description, const string& date) = 0;
    virtual void addExpense(double amount, const string& category, const string& description, const string& date) = 0;
    virtual void displaySummary() const = 0;
};

#endif

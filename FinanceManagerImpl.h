#ifndef FINANCEMANAGERIMPL_H
#define FINANCEMANAGERIMPL_H

#include "FinanceManager.h"
#include "Debt.h"
#include "Asset.h"
#include <vector>
#include <string>

using namespace std;

class FinanceManagerImpl : public FinanceManager {
private:
    vector<Transaction*> debts;
    vector<Transaction*> assets;
    vector<Transaction*> transactions;
    string userFilePath;

public:
    FinanceManagerImpl(const string& userFilePath);

    void addDebt(double amount, const string& description, const string& date);
    void removeDebt(int index);
    void addAsset(double amount, const string& description, const string& date);
    void removeAsset(int index);
    void addIncome(double amount, const string& type, const string& description, const string& date) override;
    void addExpense(double amount, const string& category, const string& description, const string& date) override;
    void displaySummary() const override;
    void loadTransactions();
    void saveTransactions() const;

private:
    void saveTransaction(const Transaction* transaction) const;
    void loadTransaction(const string& line);
};

#endif


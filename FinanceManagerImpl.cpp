#include "FinanceManagerImpl.h"
#include "Income.h"
#include "Expense.h"
#include "Debt.h"
#include "Asset.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std;

FinanceManagerImpl::FinanceManagerImpl(const string& userFilePath)
    : userFilePath(userFilePath) {
    loadTransactions();
}

void FinanceManagerImpl::addDebt(double amount, const string& description, const string& date) {
    debts.push_back(new Debt(amount, description, date));
    cout << "Debt added successfully." << endl;
    saveTransaction(debts.back());
}

void FinanceManagerImpl::removeDebt(int index) {
    if (index >= 0 && index < debts.size()) {
        delete debts[index];
        debts.erase(debts.begin() + index);
        cout << "Debt removed successfully." << endl;
    } else {
        cout << "Invalid debt index." << endl;
    }
}

void FinanceManagerImpl::addAsset(double amount, const string& description, const string& date) {
    assets.push_back(new Asset(amount, description, date));
    cout << "Asset added successfully." << endl;
    saveTransaction(assets.back());
}

void FinanceManagerImpl::removeAsset(int index) {
    if (index >= 0 && index < assets.size()) {
        delete assets[index];
        assets.erase(assets.begin() + index);
        cout << "Asset removed successfully." << endl;
    } else {
        cout << "Invalid asset index." << endl;
    }
}

void FinanceManagerImpl::addIncome(double amount, const string& type, const string& description, const string& date) {
    transactions.push_back(new Income(amount, type, description, date));
    cout << "Income added successfully." << endl;
    saveTransaction(transactions.back());
}

void FinanceManagerImpl::addExpense(double amount, const string& category, const string& description, const string& date) {
    transactions.push_back(new Expense(amount, category, description, date));
    cout << "Expense added successfully." << endl;
    saveTransaction(transactions.back());
}

void FinanceManagerImpl::displaySummary() const {
    cout << "================================================================================" << endl;
    cout << "Date" << setw(10) << "Type" << setw(10) << "Amount" << setw(10) << "Category/Type" << setw(20) << "Description" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    double totalIncome = 0.0;
    double totalExpense = 0.0;
    double totalDebt = 0.0;
    double totalAsset = 0.0;
    double totalWorth = 0.0;
    double totalProfit = 0.0;
    double totalLoss = 0.0;

    for (const Transaction* transaction : transactions) {
        transaction->displayTransaction();
        if (const Income* income = dynamic_cast<const Income*>(transaction)) {
            totalIncome += income->getAmount();
        } else if (const Expense* expense = dynamic_cast<const Expense*>(transaction)) {
            totalExpense += expense->getAmount();
        }
    }

    totalWorth = (totalAsset + totalIncome) - (totalDebt + totalExpense);
    totalProfit = totalIncome;
    totalLoss = totalExpense;

    cout << "================================================================================" << endl;
    cout << "Total Income: R" << totalIncome << endl;
    cout << "Total Expense: R" << totalExpense << endl;
    cout << "Net Balance: R" << totalIncome - totalExpense << endl;
    cout << "================================================================================" << endl;
    cout << "================================================================================" << endl;

    cout << "Debts:" << endl;
    for (const Transaction* debt : debts) {
        debt->displayTransaction();
        if (const Debt* d = dynamic_cast<const Debt*>(debt)) {
            totalDebt += d->getAmount();
        }
    }
    cout << "--------------------------------------------------------------------------------" << endl;

    cout << "Assets:" << endl;
    for (const Transaction* asset : assets) {
        asset->displayTransaction();
        if (const Asset* a = dynamic_cast<const Asset*>(asset)) {
            totalAsset += a->getAmount();
        }
    }

    cout << "================================================================================" << endl;
    cout << "Net Debt: R" << totalDebt << endl;
    cout << "Net Asset Value: R" << totalAsset << endl;
    cout << "================================================================================" << endl;
    cout << "Net Worth: R" << totalWorth << endl;
    cout << "Net Profit: R" << totalProfit << endl;
    cout << "Net Loss: R" << totalLoss << endl;
}

void FinanceManagerImpl::saveTransaction(const Transaction* transaction) const {
    ofstream file(userFilePath, ios::app);
    if (file.is_open()) {
        if (file.tellp() == 0) {
            file << "Date,Amount,Description,Type,Category" << endl;
        }
        file << transaction->getDate() << "," << transaction->getAmount() << "," << transaction->getDescription() << ",";
        if (const Income* income = dynamic_cast<const Income*>(transaction)) {
            file << "Income," << income->getType();
        } else if (const Expense* expense = dynamic_cast<const Expense*>(transaction)) {
            file << "Expense," << expense->getCategory();
        } else if (dynamic_cast<const Debt*>(transaction)) {
            file << "Debt,";
        } else if (dynamic_cast<const Asset*>(transaction)) {
            file << "Asset,";
        }
        file << endl;
        file.close();
    } else {
        cerr << "Error opening file for writing." << endl;
    }
}

void FinanceManagerImpl::loadTransactions() {
    ifstream file(userFilePath);
    if (file.is_open()) {
        string line;
        getline(file, line); // Skip the header
        while (getline(file, line)) {
            loadTransaction(line);
        }
        file.close();
    } else {
        cerr << "Error opening file for reading." << endl;
    }
}

void FinanceManagerImpl::loadTransaction(const string& line) {
    istringstream iss(line);
    string date, amountStr, description, type, category;
    getline(iss, date, ',');
    getline(iss, amountStr, ',');
    getline(iss, description, ',');
    getline(iss, type, ',');
    getline(iss, category);

    double amount = stod(amountStr);

    if (type == "Income") {
        transactions.push_back(new Income(amount, category, description, date));
    } else if (type == "Expense") {
        transactions.push_back(new Expense(amount, category, description, date));
    } else if (type == "Debt") {
        debts.push_back(new Debt(amount, description, date));
    } else if (type == "Asset") {
        assets.push_back(new Asset(amount, description, date));
    }
}

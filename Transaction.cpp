using namespace std;
#include "Transaction.h"

Transaction::Transaction(double amount, const string& description, const string& date)
    : date(date),amount(amount), description(description) {}

double Transaction::getAmount() const {
    return amount;
}

const string& Transaction::getDescription() const {
    return description;
}
const string& Transaction::getDate() const {
    return date;
}

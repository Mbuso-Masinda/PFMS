// Asset.h

#ifndef ASSET_H
#define ASSET_H
using namespace std;
#include "Transaction.h"

class Asset : public Transaction {
public:
    Asset(double amount, const string& description, const string& date);

    void displayTransaction() const override;
};

#endif

#include "FinanceManager.h"

FinanceManager::~FinanceManager() {
    for (Transaction* transaction : transactions) {
        delete transaction;
    }
}

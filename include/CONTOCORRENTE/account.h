#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transaction.h"
#include <vector>
#include <memory>
#include <string>

class Account {
private:
    std::vector<std::unique_ptr<Transaction>> transactions;
public:
    void addIncome(const std::string& date, const std::string& desc, double amt);
    void addExpense(const std::string& date, const std::string& desc, double amt);
    double getBalance() const;
    void printAll() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};

#endif
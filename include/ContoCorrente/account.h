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
    
    void addTransaction(const std::string& date, const std::string& desc, 
        TransactionType type, double amt);
    void addTransaction(const std::string& date, const std::string& desc, 
        std::string type, double amt);
    double getBalance() const;
    //TODO TO String
    void printAll() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};

#endif
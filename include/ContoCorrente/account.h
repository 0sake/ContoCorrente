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
    //print lasciato solamente per facilitare il debug
    void printAll() const;
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);     
    int getTransactionCount() const { return transactions.size(); }
    Transaction getTransaction(int index) const;
    bool removeTransaction(int index);
    bool modifyTransaction(int index, const std::string& date, const std::string& desc, 
        TransactionType type, double amt);
    std::vector<Transaction*> getTransactionsbyDate(const std::string& date) const;
    std::vector<Transaction*> getTransactionsbyDateTypeFiltered(const std::string& date, 
        TransactionType type) const;
    std::vector<Transaction*> getTransactionsbyDescription(const std::string& desc) const;
};

#endif
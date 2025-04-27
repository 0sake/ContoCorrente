#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <sstream>

class Transaction {
protected:
    std::string date;        
    std::string description; 
    double amount;           
public:
    Transaction(const std::string& d, const std::string& desc, double amt);
    
    virtual ~Transaction() = default;

    virtual char getType() const = 0;

    virtual double getAmount() const { return amount; }

    virtual std::string toCSV() const;

    virtual void print() const;
};

class IncomeTransaction : public Transaction {
public:
    IncomeTransaction(const std::string& d, const std::string& desc, double amt);
    
    char getType() const override;
};

class ExpenseTransaction : public Transaction {
public:
    ExpenseTransaction(const std::string& d, const std::string& desc, double amt);
    
    char getType() const override;
};

#endif
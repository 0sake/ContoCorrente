#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <sstream>


enum class TransactionType {
    Income,   // Entrata
    Expense   // Uscita
};


class Transaction {
protected:
    std::string date;        
    std::string description; 
    double amount;    
    TransactionType type;     
public:
    Transaction(const std::string& d, const std::string& desc, TransactionType type, double amt);
    
    virtual ~Transaction() = default;

    virtual TransactionType getType() const;
    
    virtual std::string getDate() const { return date; }

    virtual std::string getDescription() const { return description; }

    virtual char getTypetoString() const;

    virtual double getAmount() const { return amount; }

    virtual std::string toCSV() const;
    
    virtual void print() const;

    virtual std::string toString() const;
};


#endif
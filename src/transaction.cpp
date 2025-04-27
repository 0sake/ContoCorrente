#include "../include/ContoCorrente/transaction.h"
#include <iostream>

Transaction::Transaction(const std::string& d, const std::string& desc, double amt)
    : date(d), description(desc), amount(amt) {}

std::string Transaction::toCSV() const {
    std::ostringstream oss;
    oss << getType() << "," << date << "," << amount << "," << description;
    return oss.str();
}

void Transaction::print() const {
    std::cout << "[" << getType() << "] "
              << date << " | "
              << (getType()=='I'?"+":"-") << amount
              << " | " << description << std::endl;
}

IncomeTransaction::IncomeTransaction(const std::string& d, const std::string& desc, double amt)
    : Transaction(d, desc, amt) {}
char IncomeTransaction::getType() const { return 'I'; }

ExpenseTransaction::ExpenseTransaction(const std::string& d, const std::string& desc, double amt)
    : Transaction(d, desc, amt) {}
char ExpenseTransaction::getType() const { return 'E'; }

#include "account.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Account::addIncome(const std::string& date, const std::string& desc, double amt) {
    transactions.emplace_back(std::make_unique<IncomeTransaction>(date, desc, amt));
}

void Account::addExpense(const std::string& date, const std::string& desc, double amt) {
    transactions.emplace_back(std::make_unique<ExpenseTransaction>(date, desc, amt));
}

double Account::getBalance() const {
    double balance = 0.0;
    for (const auto& tr : transactions) {
        if (tr->getType() == 'I') balance += tr->getAmount();
        else if (tr->getType() == 'E') balance -= tr->getAmount();
    }
    return balance;
}

void Account::printAll() const {
    for (const auto& tr : transactions) tr->print();
    std::cout << "Saldo: " << getBalance() << std::endl;
}

bool Account::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) return false;
    ofs << "Type,Date,Amount,Description\n";
    for (const auto& tr : transactions) {
        ofs << tr->toCSV() << "\n";
    }
    return true;
}

bool Account::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) return false;
    transactions.clear();
    std::string line;
    std::getline(ifs, line); // salta intestazione
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string type, date, amtStr, desc;
        if (!std::getline(iss, type, ',')) continue;
        std::getline(iss, date, ',');
        std::getline(iss, amtStr, ',');
        std::getline(iss, desc);
        double amt = std::stod(amtStr);
        if (type == "I") addIncome(date, desc, amt);
        else if (type == "E") addExpense(date, desc, amt);
    }
    return true;
}

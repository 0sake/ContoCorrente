#include "../include/ContoCorrente/account.h"
#include <fstream>
#include <sstream>
#include <iostream>



void Account::addTransaction(const std::string& date, const std::string& desc, TransactionType type, double amt) {
    transactions.emplace_back(std::make_unique<Transaction>(date, desc, type, amt));
}

void Account::addTransaction(const std::string& date, const std::string& desc, std::string type, double amt) {
    TransactionType transactionType = (type == "I") ? TransactionType::Income : TransactionType::Expense;
    transactions.emplace_back(std::make_unique<Transaction>(date, desc, transactionType, amt));
}

double Account::getBalance() const {
    double balance = 0.0;
    for (const auto& tr : transactions) {
        if (tr->getTypetoString() == 'I') balance += tr->getAmount();
        else if (tr->getTypetoString() == 'E') balance -= tr->getAmount();
    }
    return balance;
}

//TODO rimuovere print (lasciato per debuggare con più facilità)
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
        TransactionType transactionType;
        if (!std::getline(iss, type, ',')) continue;
        std::getline(iss, date, ',');
        std::getline(iss, amtStr, ',');
        std::getline(iss, desc);
        double amt = std::stod(amtStr);
        addTransaction(date, desc, type, amt);
    }
    return true;
}

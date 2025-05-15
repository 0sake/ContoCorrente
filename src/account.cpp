#include "../include/ContoCorrente/account.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <regex>


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


Transaction Account::getTransaction(int index) const {
    if (index < 0 || index >= transactions.size()) throw std::out_of_range("Index out of range");
    return *transactions[index];
}


bool Account::removeTransaction(int index)  {
    if (index < 0 || index >= transactions.size()) return false;
    transactions.erase(transactions.begin() + index);
    return true;
}

bool Account::modifyTransaction(int index, const std::string& date, const std::string& desc, TransactionType type, double amt) {
    if (index < 0 || index >= transactions.size()) return false;
    transactions[index] = std::make_unique<Transaction>(date, desc, type, amt);
    return true;
}

std::vector<Transaction*> Account::getTransactionsbyDate(const std::string& date) const {
    std::vector<Transaction*> transactionsByDate;
    for (const auto& tr : transactions) {
        if (tr->getDate() == date) {
            transactionsByDate.push_back(tr.get());
        }
    }
    if(transactionsByDate.empty()) {
        std::cout << "Nessuna transazione trovata per la data specificata." << std::endl;
    }
    return transactionsByDate;
}

std::vector<Transaction*> Account::getTransactionsbyDateTypeFiltered(const std::string& date, TransactionType type) const {
    std::vector<Transaction*> transactionsByDate;
    for (const auto& tr : transactions) {
        if (tr->getDate() == date && tr->getType() == type) {
            transactionsByDate.push_back(tr.get());
        }
    }
    if(transactionsByDate.empty()) {
        std::cout << "Nessuna transazione trovata per la data e il tipo specificati." << std::endl;
    }
    return transactionsByDate;
}

bool contieneParola(const std::string& descrizione, const std::string& parola) {
    // Costruisci il pattern con confini di parola
    std::string pat = R"(\b)" + parola + R"(\b)";
    std::regex re(pat, std::regex_constants::icase);

    // Cerca la parola
    return std::regex_search(descrizione, re);
}

std::vector<Transaction*> Account::getTransactionsbyDescription(const std::string& desc) const {
    std::vector<Transaction*> transactionsByDesc;
    for (const auto& tr : transactions) {
        if (contieneParola(tr->getDescription(), desc)) {
            transactionsByDesc.push_back(tr.get());
        }
    }
    if(transactionsByDesc.empty()) {
        std::cout << "Nessuna transazione trovata per la descrizione specificata." << std::endl;
    }
    return transactionsByDesc;
}
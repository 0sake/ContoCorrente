#include "../include/ContoCorrente/transaction.h"
#include <iostream>
#include <regex>



bool isLeap(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool isValidDate(int d, int m, int y) {
    if (y < 1 || y > 9999) return false;
    if (m < 1 || m > 12)    return false;
    if (d < 1 || d > 31)    return false;

    static const int daysInMonth[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    int dim = daysInMonth[m];
    if (m == 2 && isLeap(y)) dim = 29;
    return d <= dim;
}

bool isDate(const std::string& date) {
    if (date.empty()) return false;
    std::string date_pattern = R"(^(19|20)\d\d[-\/\.](0[1-9]|1[0-2])[-\/\.](0[1-9]|[12][0-9]|3[01])$)";
    std::regex pattern(date_pattern);
    if (!std::regex_match(date, pattern)) return false;

    int d = std::stoi(date.substr(8, 2));
    int m = std::stoi(date.substr(5, 2));
    int y = std::stoi(date.substr(0, 4));

    return isValidDate(d, m, y);
}

Transaction::Transaction(const std::string& d, const std::string& desc, 
    TransactionType type, double amt)
    : date(d), description(desc), amount(amt) {
        if (amt < 0) {
            throw std::invalid_argument("Amount cannot be negative");}
        
        if (!isDate(d)) {
            throw std::invalid_argument("Invalid date format");}

        
    }

std::string Transaction::toCSV() const {
    std::ostringstream oss;
    oss << getTypetoString() << "," << date << "," << amount << "," << description;
    return oss.str();
}

std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "[" << getTypetoString() << "] "
        << date << " | "
        << (getTypetoString()=='I'?"+":"-") << amount
        << " | " << description;
    return oss.str();
}

void Transaction::print() const {
    std::cout << "[" << getTypetoString() << "] "
              << date << " | "
              << (getTypetoString()=='I'?"+":"-") << amount
              << " | " << description << std::endl;
}

TransactionType Transaction::getType() const {
    return type;
}

char Transaction::getTypetoString() const {
    return type == TransactionType::Income ? 'I' : 'E';
}




#include <iostream>
#include "../include/ContoCorrente/account.h"

using namespace std;

int main() {
    Account account;
    const std::string filename = "transazioni.csv";
    if (account.loadFromFile(filename))
        std::cout << "Dati caricati da " << filename << std::endl;
    else
        std::cout << "Nessun file trovato, inizializzo nuovo conto." << std::endl;

    // Esempio di transazioni
    account.addTransaction("2025-03-01", "Stipendio", TransactionType::Income, 2500.00);
    account.addTransaction("2025-03-03", "Affitto", TransactionType::Expense, 800.00);
    account.addTransaction("2025-03-05", "Spesa alimentare", TransactionType::Expense, 120.50);
    account.addTransaction("2025-03-10", "Rimborso spese", TransactionType::Income, 200.00);
    account.addTransaction("2025-03-15", "Bollette", "E", 150.00);
    account.addTransaction("2025-03-20", "Dividendi", "I", 300.00);
    

    account.printAll();
    if (account.saveToFile(filename))
        std::cout << "Dati salvati su " << filename << std::endl;
    else
        std::cerr << "Errore salvataggio su file." << std::endl;

    return 0;
}

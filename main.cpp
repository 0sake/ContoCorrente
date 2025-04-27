#include <iostream>
#include "account.h"

using namespace std;

int main() {
    Account account;
    const std::string filename = "transazioni.csv";
    if (account.loadFromFile(filename))
        std::cout << "Dati caricati da " << filename << std::endl;
    else
        std::cout << "Nessun file trovato, inizializzo nuovo conto." << std::endl;

    // Esempio di transazioni
    account.addIncome("2025-04-01", "Stipendio", 2500.00);
    account.addExpense("2025-04-03", "Affitto", 800.00);
    account.addExpense("2025-04-05", "Spesa alimentare", 120.50);

    account.printAll();
    if (account.saveToFile(filename))
        std::cout << "Dati salvati su " << filename << std::endl;
    else
        std::cerr << "Errore salvataggio su file." << std::endl;

    return 0;
}

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
    account.addTransaction("2025-03-20", "Tasse", "E", 150.00);
    account.addTransaction("2025-03-20", "Ancora tasse", "E", 150.00);
    account.addTransaction("2025-03-20", "Tassazione", "E", 150.00);
    account.addTransaction("2025-03-20", "Dividendi", "I", 300.00);
    

    // Numero di transazioni totali
    std::cout << "Numero di transazioni: " << account.getTransactionCount() << std::endl;

    // i-esima transazione
    int i = 2; // esempio: Spesa alimentare
    std::cout << "Terza transazione: " << account.getTransaction(i).toString()<< std::endl;
    // Cancella i-esima transazione
    account.removeTransaction(i);


    // Modifica i-esima transazione
    i = 1; // esempio: Affitto
    account.modifyTransaction(i, "2024-04-04", "Affitto seconda casa", TransactionType::Expense, 850.00);


    
    std::cout << "Transazioni del 2025-03-20:" << std::endl;
    std::vector<Transaction*> transactionsByDate = account.getTransactionsbyDate("2025-03-20");
    for(int j = 0; j < transactionsByDate.size(); ++j) {
        std::cout << transactionsByDate[j]->toString() << std::endl;
    }

    std::cout << "Transazioni del 2025-03-20 in entrata:" << std::endl;
    std::vector<Transaction*> transactionsByDateAndType = account.getTransactionsbyDateTypeFiltered("2025-03-20", TransactionType::Expense);
    for(int j = 0; j < transactionsByDateAndType.size(); ++j) {
        std::cout << transactionsByDateAndType[j]->toString() << std::endl;
    }

    std::cout << "Transazioni con descrizione 'Tasse' (case insensitive):" << std::endl;
    std::vector<Transaction*> transactionsByDesc = account.getTransactionsbyDescription("Tasse");
    for(int j = 0; j < transactionsByDesc.size(); ++j) {
        std::cout << transactionsByDesc[j]->toString() << std::endl;
    }


    if (account.saveToFile(filename))
        std::cout << "Dati salvati su " << filename << std::endl;
    else
        std::cerr << "Errore salvataggio su file." << std::endl;

    return 0;

}

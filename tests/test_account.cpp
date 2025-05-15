// tests/test_account.cpp
#include <gtest/gtest.h>
#include <cstdio>              // per std::remove
#include "../include/ContoCorrente/account.h"

class AccountTest : public ::testing::Test {
protected:
    Account acc;                          // usa costruttore di default
    const std::string filename = "test.csv";

    // Dopo ogni test rimuove il file creato
    void TearDown() override {
        std::remove(filename.c_str());
    }
};

// 1. Saldo iniziale a zero
TEST_F(AccountTest, InitialBalanceZero) {
    EXPECT_DOUBLE_EQ(acc.getBalance(), 0.0);
}

// 2. Aggiunta di un ingresso modifica il saldo
TEST_F(AccountTest, AddIncome) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 1500.0);
}

// 3. Aggiunta di un'uscita decrementa il saldo
TEST_F(AccountTest, AddExpense) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-02", "Affitto", TransactionType::Expense, 700.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 800.0);
}

// 4. Salvataggio e caricamento da file
TEST_F(AccountTest, SaveLoadFromFile) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-02", "Affitto", TransactionType::Expense, 700.0);

    // Salva su 'test.csv'
    ASSERT_TRUE(acc.saveToFile(filename));

    // Carica in nuovo oggetto
    Account acc2;
    ASSERT_TRUE(acc2.loadFromFile(filename));
    EXPECT_DOUBLE_EQ(acc2.getBalance(), 800.0);
}

//todo test su costruttore con allocazione dimanica
TEST_F(AccountTest, DynamicAllocation) {
    Account* accPtr = new Account();
    accPtr->addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    EXPECT_DOUBLE_EQ(accPtr->getBalance(), 1500.0);
    delete accPtr; // Assicurati di deallocare la memoria
}
//todo test per rimozione transa fuori index
TEST_F(AccountTest, RemoveTransactionOutOfIndex) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    EXPECT_FALSE(acc.removeTransaction(12)); // Indice fuori range
}

// Test per il numero di transazioni
TEST_F(AccountTest, TransactionCount) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-02", "Affitto", TransactionType::Expense, 700.0);
    EXPECT_EQ(acc.getTransactionCount(), 2);
}

// Test per ottenere la i-esima transazione
TEST_F(AccountTest, GetTransaction) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-02", "Affitto", TransactionType::Expense, 700.0);
    Transaction t = acc.getTransaction(1);
    EXPECT_EQ(t.getDate(), "2025-05-02");
    EXPECT_EQ(t.getDescription(), "Affitto");
    EXPECT_EQ(t.getAmount(), 700.0);
    EXPECT_EQ(t.getType(), TransactionType::Expense);
}

// Test per la cancellazione di una transazione
TEST_F(AccountTest, RemoveTransaction) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-02", "Affitto", TransactionType::Expense, 700.0);
    EXPECT_TRUE(acc.removeTransaction(0));
    EXPECT_EQ(acc.getTransactionCount(), 1);
    Transaction t = acc.getTransaction(0);
    EXPECT_EQ(t.getDescription(), "Affitto");
}

// Test per la modifica di una transazione
TEST_F(AccountTest, ModifyTransaction) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    EXPECT_TRUE(acc.modifyTransaction(0, "2025-05-03", "Bonus", TransactionType::Income, 2000.0));
    Transaction t = acc.getTransaction(0);
    EXPECT_EQ(t.getDate(), "2025-05-03");
    EXPECT_EQ(t.getDescription(), "Bonus");
    EXPECT_EQ(t.getAmount(), 2000.0);
    EXPECT_EQ(t.getType(), TransactionType::Income);
}

// Test per ottenere transazioni per data
TEST_F(AccountTest, GetTransactionsByDate) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-01", "Bonus", TransactionType::Income, 500.0);
    acc.addTransaction("2025-05-02", "Affitto", TransactionType::Expense, 700.0);
    auto transactions = acc.getTransactionsbyDate("2025-05-01");
    ASSERT_EQ(transactions.size(), 2);
    EXPECT_EQ(transactions[0]->getDescription(), "Stipendio");
    EXPECT_EQ(transactions[1]->getDescription(), "Bonus");
}

// Test per ottenere transazioni per data filtrate per tipo
TEST_F(AccountTest, GetTransactionsByDateTypeFiltered) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-01", "Bonus", TransactionType::Income, 500.0);
    acc.addTransaction("2025-05-01", "Affitto", TransactionType::Expense, 700.0);
    auto transactions = acc.getTransactionsbyDateTypeFiltered("2025-05-01", TransactionType::Income);
    ASSERT_EQ(transactions.size(), 2);
    EXPECT_EQ(transactions[0]->getDescription(), "Stipendio");
    EXPECT_EQ(transactions[1]->getDescription(), "Bonus");
}

// Test per ottenere transazioni per parola nella descrizione
TEST_F(AccountTest, GetTransactionsByDescription) {
    acc.addTransaction("2025-05-01", "Stipendio", TransactionType::Income, 1500.0);
    acc.addTransaction("2025-05-02", "Affitto", TransactionType::Expense, 700.0);
    acc.addTransaction("2025-05-03", "Stipendio Bonus", TransactionType::Income, 500.0);
    auto transactions = acc.getTransactionsbyDescription("Stipendio");
    ASSERT_EQ(transactions.size(), 2);
    EXPECT_EQ(transactions[0]->getDescription(), "Stipendio");
    EXPECT_EQ(transactions[1]->getDescription(), "Stipendio Bonus");
}



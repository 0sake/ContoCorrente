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



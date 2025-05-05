#include <gtest/gtest.h>
#include "../include/ContoCorrente/transaction.h"

// Test di base per IncomeTransaction
TEST(TransactionTest, IncomeToCSV) {
    Transaction inc("2025-04-27", "Stipendio", TransactionType::Income, 1000.0);
    // EXPECT_EQ verifica uguaglianza; continua il test anche se fallisce :contentReference[oaicite:0]{index=0}
    EXPECT_EQ(inc.toCSV(), "I,2025-04-27,1000,Stipendio");
}

TEST(TransactionTest, IncomeGetType) {
    Transaction inc("2025-04-27", "Bonus", TransactionType::Income, 200.0);
    EXPECT_EQ(inc.getType(), TransactionType::Income);
}

// Test di base per ExpenseTransaction
TEST(TransactionTest, ExpenseToCSV) {
    Transaction exp("2025-04-28", "Affitto", TransactionType::Expense, 750.5);
    EXPECT_EQ(exp.toCSV(), "E,2025-04-28,750.5,Affitto");
}

TEST(TransactionTest, ExpenseGetType) {
    Transaction exp("2025-04-28", "Bolletta", TransactionType::Expense, 60.0);
    EXPECT_EQ(exp.getType(), TransactionType::Expense);
}

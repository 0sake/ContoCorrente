#include <gtest/gtest.h>
#include "../include/ContoCorrente/transaction.h"

// Test di base per IncomeTransaction
TEST(TransactionTest, IncomeToCSV) {
    IncomeTransaction inc("2025-04-27", "Stipendio", 1000.0);
    // EXPECT_EQ verifica uguaglianza; continua il test anche se fallisce :contentReference[oaicite:0]{index=0}
    EXPECT_EQ(inc.toCSV(), "I,2025-04-27,1000,Stipendio");
}

TEST(TransactionTest, IncomeGetType) {
    IncomeTransaction inc("2025-04-27", "Bonus", 200.0);
    EXPECT_EQ(inc.getType(), 'I');
}

// Test di base per ExpenseTransaction
TEST(TransactionTest, ExpenseToCSV) {
    ExpenseTransaction exp("2025-04-28", "Affitto", 750.5);
    EXPECT_EQ(exp.toCSV(), "E,2025-04-28,750.5,Affitto");
}

TEST(TransactionTest, ExpenseGetType) {
    ExpenseTransaction exp("2025-04-28", "Bolletta", 60.0);
    EXPECT_EQ(exp.getType(), 'E');
}

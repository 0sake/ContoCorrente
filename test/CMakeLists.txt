cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)


enable_testing()


find_package(GTest CONFIG REQUIRED)


add_executable(my_tests
    tests/test_transaction.cpp
    tests/test_account.cpp
)


target_link_libraries(my_tests PRIVATE GTest::gtest_main)

add_test(NAME MyTests COMMAND my_tests)

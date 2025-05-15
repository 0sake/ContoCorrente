cmake_minimum_required(VERSION 3.15)
project(ContoCorrente VERSION 1.0 LANGUAGES CXX)
include(FetchContent)

# --- Impostazioni C++ ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Percorsi header ---
include_directories(${PROJECT_SOURCE_DIR}/include)

# --- Libreria core ---
add_library(${PROJECT_NAME}_lib
    src/transaction.cpp
    src/account.cpp
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# --- Eseguibile principale ---
add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${PROJECT_NAME}_lib
)

# --- Test unitari ---
enable_testing()



FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.16.0    
)
# Scarica e rende disponibile googletest
FetchContent_MakeAvailable(googletest)


# Eseguibile di test
add_executable(test_runner
    tests/test_transaction.cpp
    tests/test_account.cpp
)

target_link_libraries(test_runner
    PRIVATE ${PROJECT_NAME}_lib
            gtest_main
)

target_include_directories(test_runner
    PRIVATE ${PROJECT_SOURCE_DIR}/include      
)

# Registra i test per ctest
add_test(NAME AllTests COMMAND test_runner)

#pollo
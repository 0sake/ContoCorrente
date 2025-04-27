cmake_minimum_required(VERSION 3.15)                # Specifica la versione minima di CMake :contentReference[oaicite:8]{index=8}
project(ProjectName                             # Nome del progetto
        VERSION 1.0                             # Versione del progetto
        LANGUAGES CXX)                          # Linguaggi usati :contentReference[oaicite:9]{index=9}

# ------------------------------------------------------------
# Impostazioni del C++ standard
set(CMAKE_CXX_STANDARD 17)                       # Standard C++17 :contentReference[oaicite:10]{index=10}
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------
# Aggiunta della directory include come percorso di ricerca
# per tutti i target che la useranno (public interface)
include_directories(${PROJECT_SOURCE_DIR}/include)  :contentReference[oaicite:11]{index=11}

# ------------------------------------------------------------
# Definizione della libreria core
add_library(${PROJECT_NAME}_lib                 # Crea la libreria project_name_lib
    src/transaction.cpp
    src/account.cpp
)

# Associa l'include path ai target che linkano la libreria
target_include_directories(${PROJECT_NAME}_lib
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# ------------------------------------------------------------
# Definizione dell'eseguibile principale
add_executable(${PROJECT_NAME}                   # Crea l'eseguibile ProjectName
    src/main.cpp
)

# Link fra eseguibile e libreria core
target_link_libraries(${PROJECT_NAME}
    PRIVATE ${PROJECT_NAME}_lib
)

# ------------------------------------------------------------
# Configurazione dei test con GoogleTest
enable_testing()                                 # Abilita il framework di test :contentReference[oaicite:12]{index=12}

# Se usi googletest come subproject:
add_subdirectory(third_party/googletest)         :contentReference[oaicite:13]{index=13}
add_executable(test_runner
    tests/test_transaction.cpp
    tests/test_account.cpp
)
target_link_libraries(test_runner
    PRIVATE ${PROJECT_NAME}_lib
            gtest_main
)
add_test(NAME AllTests COMMAND test_runner)      :contentReference[oaicite:14]{index=14}

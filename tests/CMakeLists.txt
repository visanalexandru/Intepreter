set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(SOURCES "${SOURCE_DIR}/AST/SymbolTable.cpp")
add_executable(tests tests.cpp ${SOURCES})

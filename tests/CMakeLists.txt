set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(SOURCES "${SOURCE_DIR}/AST/Value/Value.cpp"
            "${SOURCE_DIR}/AST/Context.cpp"
            "${SOURCE_DIR}/AST/Function/Function.cpp"
            "${SOURCE_DIR}/AST/Function/CoreFunction/PrintFunc.cpp"
            "${SOURCE_DIR}/AST/SymbolTable.cpp"
        )
add_executable(tests tests.cpp ${SOURCES})

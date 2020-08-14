set(SOURCES "${PROJECT_SOURCE_DIR}/src")
add_executable(tests tests.cpp "${SOURCES}/AST/Value/Value.cpp" "${SOURCES}/AST/Context.cpp")

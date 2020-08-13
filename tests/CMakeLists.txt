set(SOURCES "${PROJECT_SOURCE_DIR}/src")
add_executable(tests tests.cpp "${SOURCES}/Value.cpp" "${SOURCES}/Context.cpp")
target_include_directories(tests PRIVATE "${PROJECT_SOURCE_DIR}/include")
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
project(Interpreter)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

bison_target(Parser src/parser.yy "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp")
flex_target(Scanner src/scanner.ll "${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp")

add_flex_bison_dependency(Scanner Parser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(interpreter src/main.cpp src/Driver.cpp src/Value.cpp ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} include/Type.h include/ExpNode.h include/Operator.h src/BinaryOpExp.cpp include/BinaryOpExp.h src/UnaryOpExp.cpp include/UnaryOpExp.h src/LiteralExp.cpp include/LiteralExp.h src/Context.cpp include/Context.h src/AssignmentExp.cpp include/AssignmentExp.h src/StmtNode.cpp include/StmtNode.h src/DeclarationStmt.cpp include/DeclarationStmt.h)
target_include_directories(interpreter PRIVATE include)

add_subdirectory(tests)



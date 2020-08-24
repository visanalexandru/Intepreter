cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
project(Interpreter)

find_package(FLEX 2.6.4 REQUIRED)
find_package(BISON 3.7.1 REQUIRED )

bison_target(Parser src/parser.yy "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp")
flex_target(Scanner src/scanner.ll "${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp")

add_flex_bison_dependency(Scanner Parser)
include_directories(${CMAKE_CURRENT_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(interpreter src/main.cpp src/Driver.cpp src/AST/Value/Value.cpp ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} src/AST/Value/Type.h src/AST/Expression/ExpNode.h src/AST/Expression/Operator.h src/AST/Expression/BinaryOpExp.cpp src/AST/Expression/BinaryOpExp.h src/AST/Expression/UnaryOpExp.cpp src/AST/Expression/UnaryOpExp.h src/AST/Expression/LiteralExp.cpp src/AST/Expression/LiteralExp.h src/AST/Context.cpp src/AST/Context.h src/AST/Expression/AssignmentExp.cpp src/AST/Expression/AssignmentExp.h src/AST/Statement/StmtNode.cpp src/AST/Statement/StmtNode.h src/AST/Statement/VarDeclarationStmt.cpp src/AST/Statement/VarDeclarationStmt.h src/AST/Expression/VariableExp.cpp src/AST/Expression/VariableExp.h src/AST/Statement/ExpressionStmt.cpp src/AST/Statement/ExpressionStmt.h src/AST/Function/Function.cpp src/AST/Function/Function.h src/AST/Function/CoreFunction/PrintFunc.cpp src/AST/Function/CoreFunction/PrintFunc.h src/AST/Expression/FuncCallExp.cpp src/AST/Expression/FuncCallExp.h src/AST/Function/DefinedFunction.cpp src/AST/Function/DefinedFunction.h src/AST/Statement/FuncDeclarationStmt.cpp src/AST/Statement/FuncDeclarationStmt.h src/AST/Statement/ReturnStmt.cpp src/AST/Statement/ReturnStmt.h src/AST/Preprocess/FlowState.cpp src/AST/Preprocess/FlowState.h src/Error.cpp src/Error.h src/AST/Statement/IfElseStmt.cpp src/AST/Statement/IfElseStmt.h src/AST/SymbolTable.cpp src/AST/SymbolTable.h src/AST/Symbol.h src/AST/Preprocess/DeclarationStack.cpp src/AST/Preprocess/DeclarationStack.h src/AST/Expression/ExpNode.cpp src/AST/Preprocess/VariableLocation.h)
target_compile_options(interpreter PRIVATE -O3)
add_subdirectory(tests)



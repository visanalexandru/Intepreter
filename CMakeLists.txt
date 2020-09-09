cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
project(Interpreter)

find_package(FLEX 2.6.4 REQUIRED)
find_package(BISON 3.7.1 REQUIRED )

bison_target(Parser src/parser.yy "${CMAKE_CURRENT_BINARY_DIR}/parser.cpp")
flex_target(Scanner src/scanner.ll "${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp")

add_flex_bison_dependency(Scanner Parser)
include_directories(${CMAKE_CURRENT_BINARY_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/src")
add_executable(interpreter src/main.cpp src/Driver.cpp ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} src/VM/Value/Type.h src/AST/Expression/ExpNode.h src/AST/Expression/Operator.h src/AST/Expression/BinaryOpExp.cpp src/AST/Expression/BinaryOpExp.h src/AST/Expression/UnaryOpExp.cpp src/AST/Expression/UnaryOpExp.h src/AST/Expression/LiteralExp.cpp src/AST/Expression/LiteralExp.h  src/AST/Statement/StmtNode.cpp src/AST/Statement/StmtNode.h src/AST/Statement/VarDeclarationStmt.cpp src/AST/Statement/VarDeclarationStmt.h src/AST/Expression/VariableExp.cpp src/AST/Expression/VariableExp.h src/AST/Statement/ExpressionStmt.cpp src/AST/Statement/ExpressionStmt.h src/VM/Preprocess/FlowState.cpp src/VM/Preprocess/FlowState.h src/Error.cpp src/Error.h src/AST/Statement/IfElseStmt.cpp src/AST/Statement/IfElseStmt.h src/VM/SymbolTable/SymbolTable.cpp src/VM/SymbolTable/SymbolTable.h src/VM/SymbolTable/Symbol.h src/VM/Preprocess/DeclarationStack.cpp src/VM/Preprocess/DeclarationStack.h src/AST/Expression/ExpNode.cpp src/VM/Preprocess/VariableLocation.h src/AST/Statement/WhileStmt.cpp src/AST/Statement/WhileStmt.h src/VM/VirtualMachine.cpp src/VM/VirtualMachine.h src/VM/Opcode.h src/AST/Statement/CompoundStmt.h src/AST/Statement/CompoundStmt.cpp src/VM/BytecodeChunk.cpp src/VM/BytecodeChunk.h src/VM/Value/Object.h src/GC/GarbageCollector.h src/GC/GarbageCollector.cpp src/AST/Expression/FunctionCallExp.cpp src/AST/Expression/FunctionCallExp.h src/VM/CoreFunction/CoreFunction.cpp src/VM/CoreFunction/CoreFunction.h src/AST/Statement/FuncDeclarationStmt.cpp src/AST/Statement/FuncDeclarationStmt.h src/AST/Statement/ReturnStmt.cpp src/AST/Statement/ReturnStmt.h src/VM/Utils.h src/VM/Value/Arithmetic.h)
target_compile_options(interpreter PRIVATE -O3 -flto)
add_subdirectory(tests)



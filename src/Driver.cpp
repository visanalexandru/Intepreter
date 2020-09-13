#include "Driver.h"


int Driver::parse(const std::string &f) {
    current_file = f;
    location.initialize(&current_file);
    scan_begin();
    yy::parser parser(*this);
    int res = parser();
    scan_end();
    return res;
}

void Driver::preprocess() {
    semanticAnalysis();
}


void Driver::start() {
    if (errors.empty()) {
        preprocess();
    }
    if (!errors.empty()) {
        std::cerr<<"Errors:"<<std::endl;
        for (const Error &err:errors)
            err.log();
        return;
    }

    std::cout << "Parsing successful" << std::endl;
    VM::VirtualMachine vm;
    VM::BytecodeChunk main;
    for (const auto &stmt :result)
        stmt->emitBytecode(vm, main);
    main.pushOpcode(VM::Opcode::RETURN_VALUE);
    vm.disassembleChunk(main, "");
    float a = clock();
    vm.executeChunk(main);
    std::cout << "Took " << (clock() - a) / CLOCKS_PER_SEC;
}

void Driver::semanticAnalysis() {
    VM::FlowState state;
    for (const auto &stmt:result)
        stmt->checkControlFlow(state, errors);

    for (const auto &stmt:result)
        stmt->solveDeclarations(virtual_machine.getDeclarationStack(), errors);
}



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

void Driver::init() {

}

void Driver::start() {
    init();
    preprocess();
    if (errors.empty()) {
        std::cout << "Parsing successful" << std::endl;
        VM::VirtualMachine vm;
        for (const auto &stmt :result)
            stmt->emitBytecode(vm,vm.getChunk());
        vm.disassemble();
        float a=clock();
        vm.run();
        std::cout<<"Took "<<(clock()-a)/CLOCKS_PER_SEC;
    } else {
        std::cerr << "Errors:" << std::endl;
        for (const Error &error:errors)
            error.log();
    }
}

void Driver::semanticAnalysis() {
    VM::FlowState state;
    for (const auto &stmt:result)
        stmt->checkControlFlow(state, errors);

    for(const auto&stmt:result)
        stmt->solveDeclarations(virtual_machine.getDeclarationStack(),errors);
}



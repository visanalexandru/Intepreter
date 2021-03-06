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
    AST::Symbol print_sym=AST::globalSymtable.addSymbol("print");

    AST::globalContext.declareFunc(print_sym,std::make_unique<AST::PrintFunc>());
    declaration_stack.addFunction(print_sym);
}

void Driver::start() {
    init();
    preprocess();
    if (errors.empty()) {
        std::cout << "Parsing successful" << std::endl;
        float a = clock();
        for (const auto &stmt :result)
            stmt->execute();
        std::cout << "Took " << (clock() - a) / CLOCKS_PER_SEC << std::endl;
    } else {
        std::cerr << "Errors:" << std::endl;
        for (const Error &error:errors)
            error.log();
    }
}

void Driver::semanticAnalysis() {
    AST::FlowState state;
    for (const auto &stmt:result)
        stmt->checkControlFlow(state, errors);

    for(const auto&stmt:result)
        stmt->solveDeclarations(declaration_stack,errors);
}



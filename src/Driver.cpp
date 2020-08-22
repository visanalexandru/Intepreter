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
    AST::globalContext.declareFunc(AST::globalSymtable.addSymbol("print"), std::make_unique<AST::PrintFunc>());
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
    AST::DeclarationStack stack;
    stack.addFunction(AST::globalSymtable.getSymbolIndex("print"));
    for (const auto &stmt:result)
        stmt->checkControlFlow(state, errors);

    for(const auto&stmt:result)
        stmt->checkDeclarations(stack,errors);
}



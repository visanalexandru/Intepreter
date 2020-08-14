//
// Created by gvisan on 14.08.2020.
//

#ifndef INTERPRETER_FUNCCALLEXP_H
#define INTERPRETER_FUNCCALLEXP_H

#include"ExpNode.h"
#include"AST/Context.h"

namespace AST {
    /*This class represents a function call. The evaluate() function will evaluate the parameter expressions,
     *and then run the function that has that name with the corresponding values*/
    class FuncCallExp : public ExpNode {
    private:
        const std::string name;
        /*These must be evaluated */
        const std::vector<std::shared_ptr<ExpNode>> parameters;
    public:
        FuncCallExp(std::string id, std::vector<std::shared_ptr<ExpNode>> params);

        Value evaluate() const override;


    };

}


#endif //INTERPRETER_FUNCCALLEXP_H

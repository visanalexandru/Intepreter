//
// Created by gvisan on 14.08.2020.
//

#include "StmtNode.h"

namespace AST {

    StmtNode::StmtNode(yy::location loc) : return_value(), has_returned(false),location(loc) {

    }


    void StmtNode::setReturnValue(const Value &value) {
        return_value = value;
        has_returned = true;
    }

    bool StmtNode::hasReturned() const {
        return has_returned;
    }

    Value StmtNode::getReturnValue() const {
        return return_value;
    }

    void StmtNode::resetReturnValue() {
        has_returned=false;
        return_value=Value();
    }

}

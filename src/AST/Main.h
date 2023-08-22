#pragma once

#include "../Forward.h"
#include "../Interpreter/Interpreter.h"
#include "Value.h"

class ASTNode {
  public:
    virtual std::string class_name() { return "AST Node"; }

    virtual Value execute();

};

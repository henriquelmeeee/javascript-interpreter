#pragma once

#include "../Forward.h"
class Scope;
class Value{};
#include "../Interpreter/Interpreter.h"

//#include "Value.h"

class ASTNode {
  public:
    virtual std::string class_name() { return "ASTNode"; }

    virtual Value execute(Scope* s);
};

class Identifier {
  public:
};

class VariableDeclaration;

class Scope {
  public:
    Scope* child;
    std::vector<VariableDeclaration*> s_variables;

    virtual Value execute(Scope* s);
};

class VariableDeclaration : public ASTNode {
  public:
    virtual std::string class_name() { return "VariableDeclaration"; }
    
    Identifier name;
    Value value;

    VariableDeclaration(Identifier _name, Value _value) : name(_name), value(_value) {
    }

    virtual Value execute(Scope* s);


};

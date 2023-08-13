#pragma once

#ifndef VARIABLE
#define VARIABLE

#include "Forward.h"
#include "AST.h"

class Scope;

class Variable : public ASTNode, public ForwardVariable {
  public:
    virtual std::string class_name() const { return "Variable"; }
    std::string identifier;
    Value init;

    virtual ValueType get_type() const override {
      return init.type;
    };

    Variable(Value _init, std::string _identifier="default") : init(_init), identifier(_identifier){
      cout << "Variable initialized with value " << _init.as_string() << endl;
    }

    virtual Value execute(ForwardScope* context) {
      cout << "Variable init: " << init.as_string() << endl;
      context->append_variable(this);
      return init;
    }
};

#endif

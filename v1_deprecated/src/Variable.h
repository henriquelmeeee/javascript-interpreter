#pragma once

#ifndef VARIABLE
#define VARIABLE

#include "Forward.h"
#include "AST.h"

class Scope;

class Variable : public ASTNode, public ForwardVariable {
  public:
    virtual std::string class_name() const { return "Variable"; }
    ForwardIdentifier* identifier;
    Value init;

    virtual ValueType get_type() {
      return init.type;
    };

    Variable(Value _init, ForwardIdentifier* _identifier) : init(_init){
      identifier = _identifier;
      cout << "[INIT] Variable initialized with value " << _init.as_string() << endl;
    }

    virtual Value execute(ForwardScope* context) {
      cout << "[Variable->execute()] Value type: " << init.as_string() << endl;
      return init;
    }
};

#endif

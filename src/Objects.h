#pragma once

#ifndef OBJECTS
#define OBJECTS

#include "Forward.h"
/*class Block : public ASTNode {
  public:
    virtual std::string class_name() const { return "Block"; }
    
    Block() {

    }
};*/


#include "AST.h"

class Literal : public ASTNode {
  public:
    virtual std::string class_name() const { return "Literal"; }
    Value literal_value;

    virtual Value get_literal() const {
      return literal_value;
    }

    Literal(Value _literal_value) : literal_value(_literal_value) {
      cout << "Literal value initialized as " << _literal_value.as_string() << endl;
    }

    virtual Value execute(Scope* context) {
      return literal_value;
    }

    Literal();
};
#endif

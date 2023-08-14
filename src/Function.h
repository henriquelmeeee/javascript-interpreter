#pragma once

#ifndef FUNCTION
#define FUNCTION

#include "Forward.h"
#include "AST.h"

class Function : public ASTNode, public ForwardFunction {
  public:
    virtual std::string class_name() const { return "Function"; }
    Identifier* identifier;
    std::vector<ASTNode*> body;

    Function(Identifier* i) : identifier(i) {
    }

    virtual Value execute(ForwardScope* context) {
      for(auto element : this->body) {
        cout << "[" << identifier->get() << "()->execute()] Executing elements in " << identifier->get() << endl;
        if(element->class_name() == "Return") // TODO criar um ObjectType no nó ASTNode pra checar isso 
          return element->execute(context);
        return element->execute(context); // TODO remove "return" in this instruction
      }
      return Value(UNDEFINED);
    }

    virtual bool append(ASTNode* node) {
      body.push_back(node);
      return true;
    }
};

#endif

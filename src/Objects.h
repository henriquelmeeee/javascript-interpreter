#pragma once

#ifndef OBJECTS
#define OBJECTS

#include "Forward.h"
#include "Breakpoint.h"

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

class Object : public ASTNode {
  public:
    virtual std::string class_name() const { return "Object"; }

    std::vector<ForwardVariable*> m_public_variables;
    std::vector<ForwardFunction*> m_public_functions;

    Object() {}

    bool append_variable(ForwardVariable* variable) {
      this->m_public_variables.push_back(variable);
      cout << "Variable added into an object" << endl;
      return true;
    }

    bool append_function(ForwardFunction* function) {
      this->m_public_functions.push_back(function);
      cout << "Function add into an object" << endl;
      return true;
    } 
};

class Member : public ASTNode {
  public:
    virtual std::string class_name() const { return "Member"; }
    Object* object;
    ASTNode* rhs;

    Member(Object* _object, ASTNode* _rhs) : object(_object), rhs(_rhs) {}

    Value execute(ForwardScope* context) {
      if(rhs->class_name() == "Variable") {
        cout << "rhs->class_name() == \"Variable\"" << endl;
        ForwardVariable* _rhs = (ForwardVariable*)rhs;
        for(auto var : object->m_public_variables) {
          cout << "checking var in object" << endl;
          if(true) {
            cout << "var identified" << endl;
            return var->execute(context);
          }
        }
      } else if (rhs->class_name() == "Function") {
        cout << "rhs->class_name() == \"Function\"" << endl;
        ForwardFunction* _rhs = (ForwardFunction*)rhs;
        for(auto func : object->m_public_functions) {
          cout << "checking function in object" << endl;
          if(true) {
            return func->execute(context);
          }
        }
      } else {
        cout << "Runtime error: invalid type of RHS member" << endl;
        exit(1);
      }

      return Value(UNDEFINED);
    }
};

#endif

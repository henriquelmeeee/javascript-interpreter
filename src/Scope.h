#pragma once

#ifndef SCOPE
#define SCOPE

#include "Forward.h"
#include "AST.h"

class Variable;
class ForwardScope;

bool has_string_variable(ForwardScope* context, std::string identifier) {
  for(auto variable : context->m_string_variables) {
    if(variable->identifier == identifier) {
      return true;
    }
  }
  return false;
}

class Scope : public ASTNode, public ForwardScope {
  public:
    
    std::vector<ASTNode*> elements;

    std::vector<ForwardVariable*> m_string_variables = {};
    std::vector<ForwardVariable*> m_boolean_variables = {};
    std::vector<ForwardVariable*> m_number_variables = {};

    Scope(std::vector<ASTNode*> _elements) : elements(_elements) {

    }

    ~Scope() {
      for(auto element : elements) {
        delete element;
      }
    }

    virtual Value execute(ForwardScope* context) {
      Value last_value(UNDEFINED);
      for(auto element : elements) {
        last_value = element->execute(this);
        delete element;
      }
      cout << "Scope execution returned last value as " << last_value.as_string() << endl;
      return last_value;
    }

    //virtual Value execute(ForwardScope* context);

    virtual bool append_variable(ForwardVariable* _variable) {
      switch(_variable->get_type()) {
        case STRING:
          {
            if(has_string_variable(this, _variable->identifier)) {
              throw_nonfatal_error(VARIABLE_ALREADY_EXISTS, (ASTNode*)_variable);
              return false;
              break;
            }
            m_string_variables.push_back(_variable);
            cout << "String variable successfully mapped" << endl;
            break;
          };
        case BOOLEAN:
          {
            m_boolean_variables.push_back(_variable);
            cout << "Boolean variable successfully mapped" << endl;
            break;
          };
        case NUMBER:
          {
            m_number_variables.push_back(_variable);
            cout << "Number variable successfully mapped" << endl;
            break;
          };
        default: 
          {
            // TODO throw fatal runtime error while trying to decode type of an variable
            break;
          }
      }
      return true;
    }
    
    //virtual bool append_variable(Variable* _variable);

};

#endif

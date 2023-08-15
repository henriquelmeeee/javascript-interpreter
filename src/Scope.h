#pragma once

#ifndef SCOPE
#define SCOPE

#include "Forward.h"
#include "AST.h"

class Variable;
class ForwardScope;

bool has_string_variable(ForwardScope* context, ForwardIdentifier* identifier) {
  for(auto variable : context->m_string_variables) {
    if(variable->identifier->get() == identifier->get()) {
      return true;
    }
  }
  return false;
}

class Scope : public ASTNode, public ForwardScope {
  public:
    
    std::vector<ASTNode*> elements;
    ForwardScope* parent;

    std::vector<ForwardVariable*> m_string_variables = {};
    std::vector<ForwardVariable*> m_boolean_variables = {};
    std::vector<ForwardVariable*> m_number_variables = {};

    Scope(std::vector<ASTNode*> _elements, ForwardScope* _parent) : elements(_elements), parent(_parent) {

    }

    ~Scope() {
      for(auto element : elements) {
        delete element;
      }
    }

    virtual Value execute(ForwardScope* context) {
      Value last_value(UNDEFINED);
      for(auto element : elements) {
        cout << "[Scope->execute()] Executing element typed as " << element->class_name() << endl;
        Value returned_value = element->execute(context);
        cout << "[Scope->execute()] Returned " << returned_value.as_string() << endl;
        delete element;
        
      }
      //cout << "Scope execution returned last value as " << last_value.as_string() << endl;
      return Value(UNDEFINED);
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

    virtual Value get_variable(std::string name) {
      // TODO fazer iteração sobre todos tipos possiveis de variaveis no escopo atual
      return Value(1);
    }

    virtual Value get_string_variable(std::string name) {
      // TODO esse é pra strings em especifico
      return Value(1);
    }
    
    //virtual bool append_variable(Variable* _variable);

};

#endif

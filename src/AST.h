#pragma once

#ifndef AST
#define AST

#include "Forward.h"

class Variable;
class Scope;
class Identifier;

enum ValueType {
  STRING,
  BOOLEAN,
  _NULL,
  UNDEFINED,
  NUMBER,
  DOUBLE,
};

class Value;

class ASTNode;
class ForwardScope;

class ForwardIdentifier {
  public:
    bool bp;
    std::string value;

    virtual Value execute(ForwardScope* context) = 0;
    virtual std::string get() = 0;
};

class ForwardVariable {
  public:
    bool bp;
    ForwardIdentifier* identifier = 0;
    virtual ValueType get_type() = 0;
    virtual Value execute(ForwardScope* context) = 0;
};

class ForwardFunction {
  public:
    bool bp;
    ForwardIdentifier* identifier;

    virtual Value execute(ForwardScope* context) = 0;
    virtual bool append(ASTNode* node) = 0;
};

class ForwardScope {
  public:
    bool bp;
    std::vector<ForwardVariable*> m_string_variables;
    virtual bool append_variable(ForwardVariable* _variable) = 0;
    virtual Value execute(ForwardScope* context) = 0;
    virtual Value get_variable(std::string _value) = 0;
};

enum NonfatalErrorType {
  VARIABLE_ALREADY_EXISTS,
  UNKNOWN,
};

void throw_nonfatal_error(NonfatalErrorType error, ASTNode* node) {
  switch(error) {
    case VARIABLE_ALREADY_EXISTS:
      {
        std::cerr << "Non-fatal error: Variable " << ((ForwardVariable*)node)->identifier << " already declared, ignoring." << endl;
        break;
      };
    default:
      {
        std::cerr << "Non-fatal unknown error. Continuing." << endl;
      };
  };
}

class Value {
  private:
    union Data {
      std::string stringValue;
      bool boolValue;
      int intValue;
      double doubleValue;

      Data() {}
      ~Data() {}
    } data;

  public:
    std::string as_string() const {
      switch(type) {
        case STRING:        return "String"; break;
        case BOOLEAN:       return "Boolean"; break;
        case _NULL:         return "null"; break;
        case UNDEFINED:     return "undefined"; break;
        case NUMBER:        return "Number"; break;
        case DOUBLE:        return "Double"; break;
        default:            return "Unknown"; break;
      };
    };

    ValueType type;

    Value(const std::string& value) : type(STRING) {
      //cout << "STRING VALUE CONSTRUCTOR CALLED" << endl;
      new(&data.stringValue) std::string(value);
    }

    Value(bool value) : type(BOOLEAN) {
      //cout << "BOOLEAN VALUE CONSTRUCTOR CALLED" << endl;
      data.boolValue = value;
    }

    Value(int value) : type(NUMBER) {
      //cout << "NUMBER VALUE CONSTRUCTOR CALLED" << endl;
      data.intValue = value;
    }

    Value(double value) : type(DOUBLE) {
      //cout << "DOUBLE VALUE CONSTRUCTOR CALLED" << endl;
      data.doubleValue = value;
      type = DOUBLE;
    }

    Value(const Value& other) : type(other.type) {
      switch(type) {
        case STRING:        new(&data.stringValue) std::string(other.data.stringValue); type=STRING; break;
        case BOOLEAN:       data.boolValue = other.data.boolValue; type=BOOLEAN; break;
        case NUMBER:        data.intValue = other.data.intValue; type=NUMBER; break;
        case DOUBLE:        data.doubleValue = other.data.doubleValue; type=DOUBLE; break;
        default:            break;
      }
    }

    Value& operator=(const Value& other) {
      if(this == &other) return *this;

      if(type == STRING) {
        data.stringValue.~basic_string();
      }

      type = other.type;

      switch(type) {
        case STRING:        new(&data.stringValue) std::string(other.data.stringValue); break;
        case BOOLEAN:       data.boolValue = other.data.boolValue; break;
        case NUMBER:        data.intValue = other.data.intValue; break;
        case DOUBLE:        data.doubleValue = other.data.doubleValue; break;
        default:            break;
      };

      return *this;
    }

    ~Value() {
      if(type == STRING) {
        data.stringValue.~basic_string();
      };
    }

    virtual Value execute(ForwardScope* context) {

      return *this;
    }

    virtual std::string class_name() const { return as_string(); }
};


class ASTNode {
  public:
    bool bp;
    virtual std::string class_name() const { return "Generic AST Node"; }

    ASTNode() {

    }
    virtual Value execute(ForwardScope* context) {
      return Value(_NULL);
    }
};

#include "Breakpoint.h"

class Program : public ASTNode {
  public:
    bool bp;

    virtual std::string class_name() const { return "Main Program"; }
    std::vector<ASTNode*> body;

    Program() {

    }

    virtual bool append(ASTNode* node) {
      this->body.push_back(node);
      return true;
    }
};

class Identifier : public ASTNode, public ForwardIdentifier {
  public:
    bool bp;
    virtual std::string class_name() const { return "Identifier"; }
    std::string value;

    Identifier(std::string _value) : value(_value) {

    }

    virtual Value execute(ForwardScope* context) {
      //if(bp)
        //Breakpoint((ASTNode*)this, context);
      return Value(1);
      // TODO variable execution by identifier
    }

    virtual std::string get() {
      return this->value;
    }
};

#include "Objects.h"


#endif

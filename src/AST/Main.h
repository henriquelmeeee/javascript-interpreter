#pragma once

#include "../Forward.h"

class Scope;
class Value;

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
    
    Identifier* name;
    Value* value;

    VariableDeclaration(Identifier _name, Value _value);/* : name(_name), value(_value) {
    }*/

    virtual Value execute(Scope* s);
};

enum ValueType {
  String,
  Boolean,
  Null,
  Undefined,
  Number,
  Double,
};
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
        case String:        return "String"; break;
        case Boolean:       return "Boolean"; break;
        case Null:         return "null"; break;
        case Undefined:     return "undefined"; break;
        case Number:        return "Number"; break;
        case Double:        return "Double"; break;
        default:            return "Unknown"; break;
      };
    };

    ValueType type;

    /*Value(const std::string& value) : type(String) {
      //cout << "STRING VALUE CONSTRUCTOR CALLED" << endl;
      new(&data.stringValue) std::string(value);
    }

    Value(bool value) : type(Boolean) {
      //cout << "BOOLEAN VALUE CONSTRUCTOR CALLED" << endl;
      data.boolValue = value;
    }

    Value(int value) : type(Number) {
      //cout << "NUMBER VALUE CONSTRUCTOR CALLED" << endl;
      data.intValue = value;
    }

    Value(double value) : type(Double) {
      //cout << "DOUBLE VALUE CONSTRUCTOR CALLED" << endl;
      data.doubleValue = value;
      //type = Double;
    }*/

    Value(const Value& other) : type(other.type) {
      switch(type) {
        case String:        new(&data.stringValue) std::string(other.data.stringValue); type=String; break;
        case Boolean:       data.boolValue = other.data.boolValue; type=Boolean; break;
        case Number:        data.intValue = other.data.intValue; type=Number; break;
        case Double:        data.doubleValue = other.data.doubleValue; type=Double; break;
        default:            break;
      }
    }

    /*Value& operator=(const Value& other) {
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
    }*/

    ~Value() {
      if(type == String) {
        data.stringValue.~basic_string();
      };
    }

    virtual Value execute(Scope* context) {
      return *this;
    }

    virtual std::string class_name() const { return "Value"; }
};


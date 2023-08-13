#ifndef AST
#define AST

#include "Forward.h"

class Scope;

enum ValueType {
  STRING,
  BOOLEAN,
  _NULL,
  UNDEFINED,
  NUMBER,
  DOUBLE,
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
        case STRING:        return "String";
        case BOOLEAN:       return "Boolean";
        case _NULL:         return "null";
        case UNDEFINED:     return "undefined";
        case NUMBER:        return "Number";
        case DOUBLE:        return "Double";
        default:            return "Unknown";
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

    virtual Value execute() {
      return *this;
    }

    virtual std::string class_name() const { return as_string(); }
};

class ASTNode {
  public:

    virtual std::string class_name() const { return "Generic AST Node"; }

    ASTNode() {

    }
    virtual Value execute(Scope* context) {
      return Value(_NULL);
    }
};

class Program : public ASTNode {
  public:

    virtual std::string class_name() const { return "Program"; }
    std::vector<ASTNode*> body;

    Program() {

    }

    virtual bool append(ASTNode* node) {
      this->body.push_back(node);
      return true;
    }
};

#endif
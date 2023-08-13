#include "Forward.h"
#include "AST.h"

/*class Block : public ASTNode {
  public:
    virtual std::string class_name() const { return "Block"; }
    
    Block() {

    }
};*/

class Variable;

class Scope : public ASTNode {
  public:
    
    std::vector<ASTNode*> elements;

    Scope(std::vector<ASTNode*> _elements) : elements(_elements) {

    }

    ~Scope() {
      for(auto element : elements) {
        delete element;
      }
    }

    virtual Value execute(Scope* context) {
      Value last_value(UNDEFINED);
      for(auto element : elements) {
        last_value = element->execute(this);
        delete element;
      }
      cout << "Scope execution returned last value as " << last_value.as_string() << endl;
      return last_value;
    }

};

class Variable : public ASTNode {
  public:
    virtual std::string class_name() const { return "Variable"; }
    std::string identifier;
    Value init;

    Variable(Value _init, std::string _identifier="default") : init(_init), identifier(_identifier){
      cout << "Variable initialized with value " << _init.as_string() << endl;
    }

    virtual Value execute(Scope* context) {
      cout << "Variable init: " << init.as_string() << endl;
      return init;
    }
};

class Literal : public Scope {
  public:
    Literal();
};

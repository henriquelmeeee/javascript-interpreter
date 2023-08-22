#include "Forward.h"
#include "AST.h"
#include "Objects.h"
#include "Variable.h"
#include "Scope.h"
#include "Function.h"

#include "Lexer.h"
#include "Parser.h"

std::vector<char> special_chars = {'=', ' ', ';'};
std::vector<ASTNode*> g_stack = {};

void print_indent(int indent) {
  for(int i = 0; i<indent; i++) {
    cout << ' ';
  }
}

void dump_stack() {
  int indent = 0;
  for(int i = 0; i<g_stack.size(); i++) {
    ASTNode* node = g_stack[i];
    if(node == nullptr)
      continue;

    if(node->class_name() == "Function") {
      ForwardFunction* func = (ForwardFunction*)node;
      print_indent(indent);

      cout << "Function " << func->identifier->value << "() called;" << endl;

      indent+=2;
    }
    
  }
}

int main() {

  Program* ast = new Program();

  Object* main_object = new Object();
  Object* second_object = new Object();

  Variable* main_var = new Variable(Value(5), new Identifier("a"));
  Function* func = new Function(new Identifier("b"));

  func->append(new Variable(Value(true), new Identifier("c")));

  main_object->append_variable(main_var);
  second_object->append_function(func);

  Member* main_member = new Member(
    main_object,
    (ASTNode*)main_var
  );

  Member* second_member = new Member(
    second_object,
    (ASTNode*)func
  );

  Scope* main_scope = new Scope({}, nullptr);
  main_scope->append(main_member);
  main_scope->append(second_member);
  ast->append(main_scope);

  main_scope->execute(main_scope);
  cout << "Stack dump:" << endl;
  dump_stack();

}

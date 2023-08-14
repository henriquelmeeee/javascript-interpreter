#include "Forward.h"
#include "AST.h"
#include "Objects.h"
#include "Variable.h"
#include "Scope.h"
#include "Function.h"

int main() {
  Program* ast = new Program();

  Variable* var_main = new Variable(Value(true), new Identifier("a"));
  Function* func_main = new Function(new Identifier("foo"));

  func_main->append(var_main);
  //Variable* var_second = new Variable(Value(true), new ForwardIdentifier("a"));

  Scope* main_scope = new Scope({func_main});

  ast->append(main_scope);
  main_scope->execute(main_scope);
}

#include "Forward.h"
#include "AST.h"
#include "Objects.h"
#include "Variable.h"
#include "Scope.h"

int main() {
  Program* ast = new Program();

  Variable* var_main = new Variable(Value(5));
  Variable* var_second = new Variable(Value(true));

  Scope* main_scope = new Scope({var_main, var_second});

  ast->append(main_scope);
  main_scope->execute(main_scope);
}

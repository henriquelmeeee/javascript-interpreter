#include "Forward.h"
#include "AST.h"
#include "Objects.h"
#include "Variable.h"
#include "Scope.h"
#include "Function.h"
#include "Lexer.h"

std::vector<char> special_chars = {'=', ' ', ';'};

int main() {

  Lexer lex(reinterpret_cast<const char*>("let a = 5;"), special_chars);
  while(lex.NextToken());

  Program* ast = new Program();
  Identifier* of_varmain = new Identifier("a");
  of_varmain->bp = true;

  Variable* var_main = new Variable(Value(true), of_varmain);
  Function* func_main = new Function(new Identifier("foo"));

  func_main->append(var_main);
  //Variable* var_second = new Variable(Value(true), new ForwardIdentifier("a"));

  Scope* main_scope = new Scope({func_main}, nullptr);

  ast->append(main_scope);
  main_scope->execute(main_scope);
}

#include "Forward.h"
#include "AST.h"
#include "Objects.h"
#include "Variable.h"
#include "Scope.h"
#include "Function.h"

#include "Lexer.h"
#include "Parser.h"

std::vector<char> special_chars = {'=', ' ', ';'};

int main() {

  Program* ast = new Program();

  Object* main_object = new Object();
  Object* second_object = new Object();

  Variable* main_var = new Variable(Value(5), new Identifier("a"));
  Variable* second_var = new Variable(Value(true), new Identifier("b"));

  main_object->append_variable(main_var);
  second_object->append_variable(second_var);

  Member* main_member = new Member(
    main_object,
    (ASTNode*)main_var
  );

  Member* second_member = new Member(
    second_object,
    (ASTNode*)second_var
  );

  Scope* main_scope = new Scope({}, nullptr);
  main_scope->append(main_member);
  main_scope->append(second_member);
  ast->append(main_scope);

  main_scope->execute(main_scope);

}

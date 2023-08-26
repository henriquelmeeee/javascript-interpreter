#include "Interpreter.h"

Value Interpreter::execute() {
  for(int i = 0; i<i_scopes.size()-1; i++)
    i_scopes[i]->execute(i_scopes[i]);
  return Value(false);
}

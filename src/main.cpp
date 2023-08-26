#include "Forward.h"

#include <iostream>
#include <stdlib.h>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

//#include "Interpreter/Interpreter.h"

//#include "AST/Main.h"

int main() {
  Lexer lexer("var a = 5;");
  lexer.run();
}

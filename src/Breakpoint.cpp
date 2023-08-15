#include "Forward.h"
#include "Breakpoint.h"

void Breakpoint(ASTNode* who, ForwardScope* context) {
  cout << "Breakpoint at " << who->class_name() << "execution" << endl;
  return;
}

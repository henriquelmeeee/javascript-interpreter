#pragma once

#ifndef INTERP
#define INTERP

#include "../Forward.h"

#include "../AST/Main.h"

#include <stdlib.h>
#include <vector>
#include <map>

class Interpreter {
  public:
    std::vector<Scope*> scopes;

    virtual Value execute();
      /*{Value last_value;
      for(int i = 0; i<scopes.size()-1; i++) {
        last_value = scopes[i]->execute(scopes[i]);
      }
      return last_value;
      }*/
};




#endif

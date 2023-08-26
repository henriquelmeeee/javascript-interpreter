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
    std::vector<Scope*> i_scopes;

    virtual Value execute();
};

#endif

#include "Forward.h"

#include <iostream>

void throw_err(const char* msg, ActionAfterError action) {
  std::cout << msg << "\n";
  if(action == Crash)
    exit(1);
  return;
}

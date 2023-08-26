#pragma once

enum ActionAfterError {
  Crash,
  Ignore,
};

void throw_err(const char* msg, ActionAfterError action = Crash);


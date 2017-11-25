#include "aash.h"

void builtin_cd(const char *argument) {
  char *home = getenv("HOME");

  if (! (argument || home) ) {
    return;
  }

  if (chdir(argument? argument : home)) {
    errno_handler(errno);
  }
}


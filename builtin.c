#include "aash.h"

void builtin_cd(const char *argument) {
  char *home = getenv("HOME");
  int e = 0;

  if (! (argument || home) ) {
    return;
  }

  if (chdir(argument? argument : home)) {
    e = errno;
    printf("Error %d: %s\n", e, strerror(e));
  }
}


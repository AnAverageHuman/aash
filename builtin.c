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

_Noreturn void builtin_exit(const char *argument) {
  if (argument) {
    exit((int) strtol(argument, NULL, 0));
  }

  exit(WIFEXITED(last_wstatus) ? WEXITSTATUS(last_wstatus) : 1);
}


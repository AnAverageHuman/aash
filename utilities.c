#include "aash.h"

void errno_handler(int en) {
  fprintf(stderr, "%sError %d: %s%s\n", CRED, en, strerror(en), CRESET);
}


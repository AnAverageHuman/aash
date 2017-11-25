#include "aash.h"

void errno_handler(int en) {
  fprintf(stderr, "### Error %d: %s ###\n", en, strerror(en));
}


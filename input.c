#include "aash.h"

char *get_input() {
  char *input = NULL;
  scanf("%m[^\n]%*c", &input);
  return input;
}


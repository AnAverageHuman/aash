#include "aash.h"

char *get_input() {
  char *input = NULL;
  print_prompt();
  scanf("%m[^\n]%*c", &input);
  return input;
}


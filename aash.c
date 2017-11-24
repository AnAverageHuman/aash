#include "aash.h"

void print_prompt() {
  char *prompt = "$ ";
  printf("%s", prompt);
  fflush(stdout);
}

int main() {
  char *input;
  do {
    input = get_input();
  } while (input);
}


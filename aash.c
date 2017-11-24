#include "aash.h"

void print_prompt() {
  char *prompt = "$ ";
  printf("%s", prompt);
  fflush(stdout);
}

int main() {
  char *input;
  char *freeme;
  char **to_run;
  while ((input = get_input())) {
    freeme = input;
    to_run = tokenizer_whitespace(input);
    free(freeme);
    free(to_run);
  }
}


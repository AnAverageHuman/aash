#include "aash.h"

#define SPACE " "

char **tokenizer_whitespace(char *string) {
  unsigned long a = 1;
  char **tokens = malloc(sizeof(char *));
  while (string) {
    tokens[a - 1] = strsep(&string, SPACE);
    tokens = (char **) realloc(tokens, sizeof(char *) * ++a);
  }
  tokens[a - 1] = (char *) NULL;
  return tokens;
}

char *get_input() {
  char *input = NULL;
  while (! input) {
    print_prompt();
    if (scanf("%m[^\n]", &input) == EOF) {
      return NULL;
    }
    scanf("%*c");
  }

  return input;
}


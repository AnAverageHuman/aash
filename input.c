#include "aash.h"

#define SPACE " \t"

char **tokenizer_whitespace(char *string) {
  unsigned long a = 1;
  char **tokens = malloc(sizeof(char *));
  char *tmpbuffer = NULL;
  while (string) {
    tmpbuffer = strsep(&string, SPACE);
    if (strlen(tmpbuffer)) {
      tokens[a - 1] = tmpbuffer;
      tokens = (char **) realloc(tokens, sizeof(char *) * ++a);
    }
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


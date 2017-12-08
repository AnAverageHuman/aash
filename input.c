#include "aash.h"

struct array tokenizer(char *string, const char *delim) {
  struct array ret = {malloc(sizeof(char *)), 1};
  char *tmpbuffer = NULL;
  while (string) {
    tmpbuffer = strsep(&string, delim);
    if (strlen(tmpbuffer)) {
      ret.items[ret.numitems - 1] = tmpbuffer;
      ret.items = (char **) realloc(ret.items, sizeof(char *) * ++ret.numitems);
    }
  }
  ret.items[ret.numitems - 1] = (char *) NULL;
  return ret;
}

struct array tokenizer_whitespace(char *string) {
  return tokenizer(string, SPACE);
}

struct array tokenizer_semicolon(char *string) {
  return tokenizer(string, ";");
}

char *get_input() {
  char *input = NULL;
  while (! input) {
    if (isatty(STDIN_FILENO)) {
      print_prompt();
    }
    if (scanf("%m[^\n]", &input) == EOF) {
      return NULL;
    }
    scanf("%*c");
  }

  return input;
}


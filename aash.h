#ifndef AASH_H
#define AASH_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CRED     isatty(STDOUT_FILENO) ? "\x1b[31m" : ""
#define CGREEN   isatty(STDOUT_FILENO) ? "\x1b[32m" : ""
#define CYELLOW  isatty(STDOUT_FILENO) ? "\x1b[33m" : ""
#define CBLUE    isatty(STDOUT_FILENO) ? "\x1b[34m" : ""
#define CMAGENTA isatty(STDOUT_FILENO) ? "\x1b[35m" : ""
#define CCYAN    isatty(STDOUT_FILENO) ? "\x1b[36m" : ""
#define CRESET   isatty(STDOUT_FILENO) ? "\x1b[0m"  : ""

extern pid_t cpid;
extern int last_wstatus;


char *get_input(void);
char **tokenizer_whitespace(char *string);

void print_prompt(void);

char execute_command(char **to_run);
void builtin_cd(const char *argument);
void builtin_exit(const char *argument);

struct functiontable {
  const char *name;
  void (*func)(const char *argument);
};

void errno_handler(int en);
char *cwd_basename(void);

#endif /* _AASH_H */


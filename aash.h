#ifndef AASH_H
#define AASH_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern pid_t cpid;
extern int last_wstatus;


char *get_input(void);
char **tokenizer_whitespace(char *string);

void execute_command(char **to_run);

void print_prompt(void);

void builtin_cd(const char *argument);
void builtin_exit(const char *argument);

void errno_handler(int en);
char *cwd_basename(void);

#endif /* _AASH_H */


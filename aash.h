#ifndef AASH_H
#define AASH_H

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

#endif /* _AASH_H */


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

#define SPACE " \t"

extern pid_t cpid;
extern int last_wstatus;

struct array {
  char **items;
  unsigned long numitems;
};

struct fd {
  int stdin;
  int stdout;
  int stderr;
};

struct redir_stats {
  char *filename;
  char append;
};

char *get_input(void);
struct array tokenizer(char *string, const char *delim);
struct array tokenizer_whitespace(char *string);
struct array tokenizer_semicolon(char *string);

void print_prompt(void);

char execute_command(char **to_run);
void builtin_cd(const char *argument);
void builtin_exit(const char *argument);

struct redir_stats get_redir_stats(char **command, char *redirection);
int redirect_stdin(struct redir_stats r, struct fd *fds);
int redirect_stdout(struct redir_stats r, struct fd *fds);
int redirect_stderr(struct redir_stats r, struct fd *fds);
int redirect_pipe(char **command);
void process_redirects(char **command, struct fd *fds);
void reset_redirects(struct fd *fds);

void errno_handler(int en);
char *cwd_basename(void);

#endif /* _AASH_H */


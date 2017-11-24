#include <errno.h>
#include <sys/wait.h>

#include "aash.h"

pid_t cpid;
int last_wstatus = 0;

void print_prompt() {
  char *prompt = "$ ";
  printf("%s", prompt);
  fflush(stdout);
}

void execute_command(char **to_run) {
  if ((cpid = fork())) {
    waitpid(cpid, &last_wstatus, 0);
  } else {
    execvp(to_run[0], to_run);
    int e = errno;
    printf("Error %d: %s\n", e, strerror(e));
  }
}

int main() {
  char *input;
  char *freeme;
  char **to_run;
  while ((input = get_input())) {
    cpid = 0;
    freeme = input;
    to_run = tokenizer_whitespace(input);
    execute_command(to_run);
    free(freeme);
    free(to_run);

    if (! cpid) {
      return(1);
    }
  }
}


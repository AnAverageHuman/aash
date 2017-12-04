#include <libgen.h>
#include <signal.h>
#include <sys/wait.h>

#include "aash.h"


const static struct {
  const char *name;
  void (*func)(const char *argument);
} functions[] = {
  {"cd",   &builtin_cd},
  {"exit", &builtin_exit}
};

pid_t cpid;
int last_wstatus = 0;

static void sighandler(int signo) {
  if (signo == SIGINT && cpid) {
    kill(cpid, SIGINT);
  }
}

void print_prompt() {
  if (WIFEXITED(last_wstatus) && WEXITSTATUS(last_wstatus)) {
    // exit status of last command
    printf("%s%d%s ", CRED, WEXITSTATUS(last_wstatus), CRESET);
  }

  char *cwd = NULL;
  cwd = getcwd(cwd, 0);
  printf("%s%s%s ", CGREEN, basename(cwd), CRESET); // basename of cwd
  free(cwd);

  printf("%s ", "$"); // the actual prompt
  fflush(stdout);
}

char execute_command(char **to_run) {
  unsigned int i;
  for (i = 0; i < (sizeof(functions) / sizeof(functions[0])); i++) {
    if (! strcmp(functions[i].name, to_run[0])) {
      functions[i].func(to_run[1]);
      return 1;
    }
  }

  if ((cpid = fork())) {
    waitpid(cpid, &last_wstatus, 0);
  } else if (execvp(to_run[0], to_run)) {
    errno_handler(errno);
  }
  return 0;
}

int main() {
  signal(SIGINT, sighandler);

  unsigned long i;
  char *input;
  char *freeme;
  struct array to_run;
  struct array command;
  struct fd fds = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
  char builtin = 0;
  while ((input = get_input())) {
    cpid = 0;
    freeme = input;

    to_run = tokenizer_semicolon(input);
    for (i = 0; i < to_run.numitems - 1; i++) {
      process_redirects(&to_run.items[i], &fds);
      command = tokenizer_whitespace(to_run.items[i]);
      if (command.items[0]) {
        builtin = execute_command(command.items);
        if (! (cpid || builtin) ) {
          builtin_exit(NULL);
        }
      }
      reset_redirects(&fds);
      free(command.items);
    }

    free(freeme);
    free(to_run.items);
  }
}


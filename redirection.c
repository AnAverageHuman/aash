#include <ctype.h>
#include <fcntl.h>

#include "aash.h"

struct redir_stats get_redir_stats(char **command, char *redirection) {
  char *pos = strstr(*command, redirection);
  char *c;
  struct redir_stats ret = {NULL, 0};

  if ((c = pos + strlen(redirection)) && *c == '>') {
    ret.append = 1;
    c += 1;
  }

  while (c && isspace(*c)) {
    c++;
  }

  ret.filename = strsep(&c, SPACE);
  if (pos) {
    strcpy(pos, c ? c : "");
  }

  return ret;
}

int redirect_stdin(struct redir_stats r, struct fd *fds) {
  fds->stdin = dup(STDIN_FILENO);
  int tmp_fd = open(r.filename, O_RDONLY);
  return dup2(tmp_fd, STDIN_FILENO);
}

int redirect_stdout(struct redir_stats r, struct fd *fds) {
  fds->stdout = dup(STDOUT_FILENO);
  int tmp_fd = STDOUT_FILENO;
  if (r.append) {
    tmp_fd = open(r.filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
  } else {
    tmp_fd = open(r.filename, O_CREAT | O_WRONLY | O_TRUNC,  0644);
  }
  return dup2(tmp_fd, STDOUT_FILENO);
}

int redirect_stderr(struct redir_stats r, struct fd *fds) {
  fds->stderr = dup(STDERR_FILENO);
  int tmp_fd = open(r.filename, O_CREAT | O_WRONLY |
      r.append? O_APPEND : O_TRUNC, 0644);
  return dup2(tmp_fd, STDERR_FILENO);
}

void process_redirects(char **command, struct fd *fds) {
  struct redir_stats r;
  char *pip;
  char *out;
  if (strstr(*command, "&>")) {
    r = get_redir_stats(command, "&>");
    redirect_stdout(r, fds);
    redirect_stderr(r, fds);
  } else {
    if (strstr(*command, "2>")) {
      r = get_redir_stats(command, "2>");
      redirect_stderr(r, fds);
    }

    if (strstr(*command, "<")) {
      r = get_redir_stats(command, "<");
      redirect_stdin(r, fds);
    }

    pip = strstr(*command, ">");
    out = strstr(*command, "|");

    if (pip - *command > out - *command) {
      dup2(fileno(popen(*command, "r")), STDIN_FILENO);
    } else if (out) {
      r = get_redir_stats(command, ">");
      redirect_stdout(r, fds);
    }
  }
}

void reset_redirects(struct fd *fds) {
  if (STDIN_FILENO != fds->stdin) { close(STDIN_FILENO); }
  dup2(fds->stdin, STDIN_FILENO);
  if (STDOUT_FILENO != fds->stdout) { close(STDOUT_FILENO); }
  dup2(fds->stdout, STDOUT_FILENO);
  if (STDERR_FILENO != fds->stderr) { close(STDERR_FILENO); }
  dup2(fds->stderr, STDERR_FILENO);
}


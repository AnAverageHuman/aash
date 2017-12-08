# aash
An Average Shell

## Features

- Executes commands.
- Has the ability to change the working directory with `cd`.
- Shows the current working directory in the prompt.
- Shows the exit status of the last command in the prompt if it is not 0.
- Supports color terminals.
- Passes on the SIGINT signal to the foreground child.
- Supports multiple commands on one line separated with `;`.
- Allows redirecting stdout and stderr using `>`, `2>`, `&>`, and their
  appending counterparts.
- Allows redirecting stdin using `<`.

## Function Headers

### aash.c

#### `static void sighandler(int signo)`

Passes SIGINT on to foreground child process, if one is currently running.

#### `void print_prompt()`

Prints a prompt to stdout if we are running interactively.

#### `char execute_command(char **to_run)`

Forks, with the child executing a command and the parent waiting for it.  
Returns 1 if the command executed is a builtin function, 0 otherwise.

#### `int main()`

The core of the shell.

### input.c

#### `struct array tokenizer(char *string, const char *delim)`

Converts a string delimited by specific characters to a character array.

#### `struct array tokenizer_whitespace(char *string)`

Converts a given string separated by spaces into an array of strings.

#### `struct array tokenizer_semicolon(char *string)`

Converts a given string separated by semicolons into an array of strings.

#### `char *get_input()`

Returns dynamically allocated input read from stdin.

### builtin.c

#### `int builtin_cd(const char *argument)`

A partial implementation of the `cd` utility, as specified by POSIX.

#### `_Noreturn void builtin_exit(const char *argument)`

A partial implementation of the `exit` utility, as specified by POSIX.

### utilities.c

#### `void errno_handler(int en)`

A default handler for errno that prints error messages to stderr.

### redirection.c

#### `struct redir_stats get_redir_stats(char **command, char *redirection)`

Given the string to work with and a redirection token to look for, it "cuts" the
filename out, returning that and a flag representing if we are appending to a
file.

#### `int redirect_stdin(struct redir_stats r, struct fd *fds)`

Processes redirection for stdin, returning the new file descriptor.

#### `int redirect_stdout(struct redir_stats r, struct fd *fds)`

Processes redirection for stdout, returning the new file descriptor.

#### `int redirect_stderr(struct redir_stats r, struct fd *fds)`

Processes redirection for stderr, returning the new file descriptor.

#### `void process_redirects(char **command, struct fd *fds)`

Handles redirection by calling the proper helper function(s).

#### `void reset_redirects(struct fd *fds)`

Resets redirection to the default behavior (i.e., the state of streams before
redirections were processed).

## Bugs

- Does not interpret "quoted strings" as a single token.

- Not all *alloc'd memory is freed before exiting in `builtin_exit()`.
This is negligible.

- Exits with status 0 if EOF is read, regardless of the exit status of the last
  command.


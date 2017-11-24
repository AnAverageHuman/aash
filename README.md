# aash
An Average Shell

## Features

- Executes commands.

## Function Headers

### aash.c

#### `void print_prompt()`

Prints a prompt to stdout.

#### `void execute_command(char **to_run)`

Forks, with the child executing a command and the parent waiting for it.

#### `int main()`

The core of the shell.

### input.c

#### `char **tokenizer_whitespace(char *string)`

Converts a given string separated by spaces into an array of strings.

#### `char *get_input()`

Returns dynamically allocated input read from stdin.

## Bugs

- Exits when input is empty (i.e. only a newline).

- Does not properly process lines with extra spaces.

- Does not interpret "quoted strings" as a single token.


# MiniSHELL

@42-Born2Code

## About

This project is about creating a simple shell.
It is our own minishell.

## Common Instructions

- Must be written in C
- Should not quit unexpectedly
- No leaks will be tolerated.
- Makefile width flags -Wall -Wextra -Werroe
- Makefile: all clean fclean re

## Mandatory
- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the `PATH` variable or using a relative or an absolute path).
- Not use more than one global variable.
- Not interpret unclosed quotes or special characters as `\` or `;`.
- Handle `’` which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- Handle `"` which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$`.
- Implement redirections:
    - `<` redirect input.
    - `>` redirect output.
    - `<<` heredoc.
    - `>>` redirect output in append mode.
- Implement pipes.
- Handle environment variables.
- Handle $?.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- Implement the following builtins:
    - `echo` with option `-n`.
    - `cd` with only a relative or absolute path.
    - `pwd` with no options.
    - `export` with no options.
    - `unset` with no options.
    - `env` with no options or arguments.
    - `exit` with no options.

The readline() function can cause memory leaks.

## Installation && Usage

### Requirements
The only Requirements are:
- GNU make
- CC

### Building the program
1. Download/Clone this repo

```bash
  git clone https://github.com/suhovhan/minishell.git
```
2. `cd` into the root directory
```bash
cd minishell
```
3. run `make`
```bash
make
```

### Running the program
After building the source, run `./minishell` from the project root.

## Usage/Examples

```bash
ls
/bin/ls
ls > ls.txt
cat ls.txt
ls | cat
sleep 2 | sleep 2 | sleep 2 | sleep 2
export key=value
echo $key
unset key
```
Use your imagination within the limits of the project requirements.

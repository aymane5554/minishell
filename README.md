# minishell

A minimal Unix shell written in C, built as part of the **42 School** curriculum. It replicates core Bash behaviour — pipelines, redirections, variable expansion, heredocs, quote handling, and a set of built-in commands — while managing its own environment and signal handling.

---

## Table of Contents

- [Features](#features)
- [Built-in Commands](#built-in-commands)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Authors](#authors)

---

## Features

| Category | Details |
|---|---|
| **Interactive prompt** | `minishell>` prompt with readline history |
| **Pipelines** | Arbitrary chains of commands connected with `\|` |
| **Redirections** | `<` input, `>` output (truncate), `>>` output (append) |
| **Heredoc** | `<<` delimiter — reads until the limiter line is matched |
| **Variable expansion** | `$VAR` and `$?` (last exit status) |
| **Quote handling** | Single quotes prevent all expansion; double quotes allow `$` expansion |
| **Signal handling** | `Ctrl+C` prints a new prompt; `Ctrl+\` is ignored (as in Bash) |
| **Environment** | Full linked-list environment that is inherited and modifiable at runtime |
| **Exit codes** | Accurate propagation of exit statuses from child processes and built-ins |

---

## Built-in Commands

| Command | Description |
|---|---|
| `echo [-n]` | Print arguments to stdout; `-n` suppresses the trailing newline |
| `cd [path]` | Change the working directory; updates `PWD` and `OLDPWD` |
| `pwd` | Print the current working directory |
| `export [KEY=VALUE ...]` | Set or display exported environment variables |
| `unset [KEY ...]` | Remove variables from the environment |
| `env` | Print all environment variables |
| `exit [n]` | Exit the shell with optional exit code |

---

## Getting Started

### Prerequisites

- GCC or Clang
- GNU `make`
- `readline` development library

```bash
# Debian / Ubuntu
sudo apt install libreadline-dev

# macOS (Homebrew)
brew install readline
```

### Build

```bash
git clone <repo-url> minishell
cd minishell
make
```

This compiles the bundled `libft` and links everything into a single `minishell` executable.

### Clean

```bash
make clean    # remove object files
make fclean   # remove object files + binary
make re       # fclean then build
```

---

## Usage

```bash
./minishell
```

You will see the `minishell>` prompt. Type any command just as you would in Bash:

```bash
minishell> echo "Hello, World!"
Hello, World!

minishell> ls -la | grep ".c" | wc -l
4

minishell> cat << EOF
> line one
> line two
> EOF
line one
line two

minishell> export GREETING="hi"
minishell> echo $GREETING
hi

minishell> echo $?
0

minishell> exit
```

---

## Project Structure

```
minishell/
├── main.c                   # Entry point and REPL loop
├── minishell.h              # Shared types and prototypes
├── Makefile
├── signal_handler.c         # SIGINT / SIGQUIT handlers
├── sep_redirection.c        # Tokeniser: separates redirection operators
├── insert.c                 # Input insertion helpers
│
├── syntax/                  # Syntax validation (quotes, operators)
├── split_input/             # Splits a raw line into tokens
├── pipe_split/              # Splits a token array on pipe operators
├── remove_quotes/           # Strips quotes after expansion
│
├── expanding/               # Variable and heredoc expansion
│   ├── expanding.c
│   ├── expand_parse.c
│   ├── extract_dollar.c
│   ├── heredoc_limiter.c
│   └── expand_utils.c
│
├── export/                  # export / unset / env implementation
│   ├── export.c
│   ├── chenv.c / chenv2.c   # Environment mutation helpers
│   ├── sortenv.c            # Sorted display for `export`
│   └── unset.c
│
├── execution/               # Command execution engine
│   ├── execute.c            # Top-level executor (fork / pipe loop)
│   ├── built_ins/           # echo, cd, pwd, exit
│   ├── execute_builtins/    # Routing layer for built-ins
│   ├── execute_cmds/        # External command resolution and exec
│   └── open_redirections/   # Opens files for I/O redirection
│
├── main_utils/              # Helpers used in main (env init, status)
└── libft/                   # Custom C standard-library subset
```

---

## Authors

| Login | GitHub |
|---|---|
| **ayel-arr** | [@ayel-arr](https://github.com/ayel-arr) |
| **tibarike** | [@tibarike](https://github.com/tibarike) |

---

> *42 School — minishell project*

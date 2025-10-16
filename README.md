# Minishell 🐚

A simple yet powerful Unix shell implementation written in C, inspired by Bash. This project is part of the 42 school curriculum and aims to provide a deeper understanding of processes, file descriptors, and system calls.

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Supported Features](#supported-features)
- [Project Structure](#project-structure)
- [Technical Details](#technical-details)
- [Authors](#authors)

## 🎯 About

Minishell is a minimalist shell implementation that recreates the basic functionality of a Unix shell. It provides an interactive command-line interface where users can execute commands, manage processes, and handle input/output redirections.

This project demonstrates:
- Process creation and management
- File descriptor manipulation
- Signal handling
- Parsing and tokenization
- Environment variable management

## ✨ Features

- **Interactive Prompt**: Clean and intuitive command-line interface
- **Command Execution**: Execute system commands with arguments
- **Built-in Commands**: Implementation of essential shell built-ins
- **Pipes**: Support for command chaining with pipes (`|`)
- **Redirections**: Input/output redirection operators
- **Environment Variables**: Full environment variable support with expansion
- **Signal Handling**: Proper handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\`
- **Quote Handling**: Support for single (`'`) and double (`"`) quotes
- **History**: Command history functionality using readline
- **Heredoc**: Support for heredoc input (`<<`)

## 🚀 Installation

### Prerequisites

- GCC compiler
- GNU Make
- GNU Readline library

For Ubuntu/Debian:
```bash
sudo apt-get update
sudo apt-get install build-essential libreadline-dev
```

For macOS:
```bash
brew install readline
```

### Build

1. Clone the repository:
```bash
git clone https://github.com/oishchen42/mshell_ubuntu.git
cd mshell_ubuntu
```

2. Compile the project:
```bash
make
```

3. The executable `minishell` will be created in the root directory.

### Clean Build

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything from scratch
```

## 💻 Usage

Start the shell:
```bash
./minishell
```

You'll see the prompt:
```
Minishell-1.0$
```

### Basic Examples

Execute a simple command:
```bash
Minishell-1.0$ ls -la
```

Use pipes to chain commands:
```bash
Minishell-1.0$ cat file.txt | grep "pattern" | wc -l
```

Redirect output to a file:
```bash
Minishell-1.0$ echo "Hello World" > output.txt
Minishell-1.0$ cat < input.txt > output.txt
```

Use heredoc:
```bash
Minishell-1.0$ cat << EOF
> Hello
> World
> EOF
```

Environment variable expansion:
```bash
Minishell-1.0$ echo $HOME
Minishell-1.0$ echo "User: $USER, Path: $PATH"
```

## 🔧 Built-in Commands

Minishell implements the following built-in commands:

### `echo`
Print arguments to standard output
```bash
echo [options] [arguments]
```
Options:
- `-n`: Do not output trailing newline

### `cd`
Change the current directory
```bash
cd [directory]
```
- Without arguments: Changes to HOME directory
- With path: Changes to specified directory

### `pwd`
Print the current working directory
```bash
pwd
```

### `env`
Display environment variables
```bash
env
```

### `export`
Set environment variables
```bash
export VAR=value
export VAR="value with spaces"
```

### `unset`
Remove environment variables
```bash
unset VAR
```

### `exit`
Exit the shell
```bash
exit [exit_code]
```

## 🎨 Supported Features

### Redirections

- `<` : Input redirection
- `>` : Output redirection (overwrite)
- `>>` : Output redirection (append)
- `<<` : Heredoc (read until delimiter)

### Operators

- `|` : Pipe operator for command chaining

### Quotes

- Single quotes (`'`): Preserve literal value of all characters
- Double quotes (`"`): Preserve literal value, but allow variable expansion

### Special Characters

- `$VAR` : Environment variable expansion
- `$?` : Exit status of last command

## 📁 Project Structure

```
mshell_ubuntu/
├── Makefile              # Build configuration
├── include/              # Header files
│   ├── minishell.h      # Main header
│   ├── struct.h         # Data structures
│   └── tokenize.h       # Tokenizer declarations
├── src/                  # Source files
│   ├── main.c           # Entry point and main loop
│   ├── builtin_*.c      # Built-in command implementations
│   ├── tokenize_*.c     # Tokenization and parsing
│   ├── create_cmd*.c    # Command structure creation
│   ├── run_cmd.c        # Command execution
│   ├── redir_*.c        # Redirection handling
│   ├── heredoc_utils.c  # Heredoc implementation
│   ├── var_expansion.c  # Variable expansion
│   ├── signals.c        # Signal handling
│   └── find_executable.c # Command path resolution
├── libft/               # Custom C library
└── get_next_line/       # Line reading utility
```

## 🔬 Technical Details

### Memory Management
- Proper allocation and deallocation of all dynamically allocated memory
- No memory leaks (verified with valgrind)

### Process Management
- Fork and exec for external command execution
- Proper handling of child processes
- Exit status propagation

### Signal Handling
- `Ctrl-C` (SIGINT): Displays new prompt
- `Ctrl-D` (EOF): Exits the shell
- `Ctrl-\` (SIGQUIT): Does nothing

### Readline Integration
- Command history with up/down arrow keys
- Line editing capabilities
- Suppression of memory leaks from readline library

## 👥 Authors

- **nmikuka** - [42 Heilbronn](mailto:nmikuka@student.42heilbronn.de)
- **oishchen** - [GitHub](https://github.com/oishchen42)

## 📝 Notes

This project is part of the 42 school curriculum. It adheres to the 42 coding standards (Norminette) and project requirements.

### Limitations

This is an educational project and does not implement all features of a full-fledged shell like Bash. Some advanced features are not supported:
- Logical operators (`&&`, `||`)
- Wildcards (`*`)
- Subshells
- Job control
- Background processes (`&`)

## 🙏 Acknowledgments

- 42 School for the project subject
- The developers of GNU Readline
- The Unix/Linux shell community

---

*Made with ☕ at 42 School*

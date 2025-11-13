# Minishell

A small Unix-like shell implemented in C that reproduces core bash features: parsing, execution, redirections, heredoc, pipes, and a selection of builtins.

## Goals
- Display interactive prompt with history.
- Handle quoted strings (single & double quotes).
- Support input/output redirections and heredoc.
- Support pipes between commands.
- Expand environment variables.
- Provide builtin commands executed in the parent where required.
- Basic signal handling to avoid unwanted termination.

## Quick start

Build:
```sh
make
```

Run:
```sh
./minishell
```

Run tests (simple script included):
```sh
./test_minishell.sh
# or the checker:
./github_checker_checker.sh
```

## Project layout (important files)
- Entry point: [main.c](main.c) (`main`)
- Core loop: [src/minishell.c](src/minishell.c) (`minishell`) — reads prompt, history, calls parser and executor.
- Parser & helpers: `src/parse/*` (see files under `src/parse/aux/`) — tokenization and argument handling.
  - Heredoc: [src/parse/aux/heredoc.c](src/parse/aux/heredoc.c) (`heredoc`) — creates temporary heredoc files and collects input.
  - File handling: [src/parse/aux/handle_file.c](src/parse/aux/handle_file.c)
- Execution: `src/execute/*` — process management, redirection, builtins.
  - Interfaces: [include/execute.h](include/execute.h)
- Verification & shutdown: [src/verify/end.c](src/verify/end.c) (`end`)
- Data types & globals: [include/structs.h](include/structs.h)
- Public API and macros: [include/minishell.h](include/minishell.h)
- Build: [Makefile](Makefile)

## Features & behavior
- Prompt and history via GNU readline (linked by Makefile).
- Built-in commands implemented in `src/builtin/*` (examples: `ft_cd`, `ft_pwd`, `ft_export`, `ft_unset`, `ft_env`, `ft_echo`, `ft_exit`).
- Redirections:
  - `<` (ARROW_LEFT), `<<` (DOUBLE_ARROW_LEFT/heredoc), `>` (ARROW_RIGHT), `>>` (DOUBLE_ARROW_RIGHT).
- Heredoc: temporary file `.heredoc_<n>` created by [`heredoc`](src/parse/aux/heredoc.c).
- Process management: pipes and forks handled under `src/execute/` (see [include/execute.h](include/execute.h)).
- Errors: reported using `end` in [src/verify/end.c](src/verify/end.c).

## Development notes
- The project depends on a local libft (see `Makefile` LIBFT_PATH).
- Compiler flags: `-Werror -Wextra -Wall -g`.
- Object files are placed under `.build/` as configured in the `Makefile`.

## Running / debugging tips
- Use `make` to compile with debug symbols (`-g`).
- Use the included test scripts:
  - [test_minishell.sh](test_minishell.sh)
  - [github_checker_checker.sh](github_checker_checker.sh)
- For investigating heredoc behavior inspect [`heredoc`](src/parse/aux/heredoc.c) and [`handle_file`](src/parse/aux/handle_file.c).

## Contributing
- Follow coding style and tests already present.
- Add unit tests or integration tests under `minishell_tester/` or via new scripts.

## License & credits
- Libft helper library required: clone or build as defined in `Makefile` (`LIBFT_URL`).
- See `Makefile` for build and test targets.

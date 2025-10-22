#!/bin/bash

# Colors
GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
RESET="\033[0m"

# Path to your minishell binary
MINISHELL=./minishell

# Temporary files
OUT_MINI=out_minishell.txt
OUT_BASH=out_bash.txt

# Array of test commands
tests=(
	"ls"
#	"ls -l"
	"ls | echo oi"
	"ls | wc"
	"ls | wc -l"
	"ls | wc | wc -l"
	"echo hello world"
	"< Makefile wc"
	"< Makefile wc | wc -l"
	"pwd"
	"cat Makefile | wc | wc -l"
	"echo "banana" > a > b | ls"
	"< Makefile wc | ls"	
	"< Makefile cat | wc | cat -e | cat -e | cat -e | cat -e"
#  "echo -n hello && echo world"
#  "cd .. && pwd"
#  "echo test > tmpfile && cat tmpfile"
#  "echo test >> tmpfile && cat tmpfile"
#  "cat < tmpfile"
#  "echo \$HOME"
#  "echo \"   spaced   \""
#  "export VAR=42 && echo \$VAR"
#  "unset VAR && echo \$VAR"
#  "echo \$?"
#  "exit"
)

run_test() {
    CMD="$1"

    # Run in minishell
    echo "$CMD" | $MINISHELL 2>/dev/null >"$OUT_MINI"
    STATUS_MINI=$?

    # Run in bash
    echo "$CMD" | bash 2>/dev/null >"$OUT_BASH"
    STATUS_BASH=$?

    # Remove minishell output first and last lines
    sed -i '1d;$d' "$OUT_MINI"

    DIFF=$(diff "$OUT_MINI" "$OUT_BASH")

    if [ "$STATUS_MINI" -eq "$STATUS_BASH" ] && [ -z "$DIFF" ]; then
        echo -e "${GREEN}[OK]${RESET} $CMD"
    else
        echo -e "${RED}[KO]${RESET} $CMD"
    fi
        echo -e "${YELLOW}--- minishell ---${RESET}"
#        cat -e "$OUT_MINI"
        echo -e "${YELLOW}--- bash ---${RESET}"
#        cat -e "$OUT_BASH"
        echo -e "${YELLOW}--- status ---${RESET}"
        echo -e "status mini: $STATUS_MINI"
        echo -e "status bash: $STATUS_BASH"
        echo

}

echo -e "${YELLOW}Running Minishell tests...${RESET}"
for t in "${tests[@]}"; do
    run_test "$t"
done

rm -f "$OUT_MINI" "$OUT_BASH" tmpfile


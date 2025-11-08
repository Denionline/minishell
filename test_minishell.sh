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

	# Simple
	"echo hello"
	"/bin/echo hello world"
	"ls"
#	"ls -l"
	"pwd"
	"whoami"

	# Pipes
	"ls | wc -l"
	"echo hello | cat"
	"echo hello | cat | cat"
#	"echo one two three | tr ' ' '\n' | sort | uniq"
	"cat /etc/passwd | grep root | wc -l"

	# Redirections
	"echo hello > out.txt"
	"echo one >> test.txt"
	"echo two >> test.txt"
	"cat < test.txt"
	"wc -l < test.txt"
	"cat < test.txt | grep o > result.txt"

	# Combinations
	"cat < /etc/passwd | grep root > roots.txt"
	"grep bash < /etc/passwd | sort | uniq > bash_users.txt"

	# Quotes and expansions
#	"echo "hello world""
	"echo 'single quotes'"
#	"echo "mix 'inside' double""
	"echo $HOME"
	"echo $USER"
#	"echo "user: $USER, home: $HOME""

	# Exit codes ----> in progress
#	"/bin/false"
#	echo $?
#	"/bin/true"
#	echo $?
#	"ls non_existent"
#	echo $?
#	"nosuchcommand"
#	"/bin/ls no_such_file"
#	"cat no_such_file"
#	"echo > /no_permission"
#	"< echo"

	# Super duper tests
	"seq 1 10 | grep 5 | cat | grep 1 | wc -l"
#	"echo hi > a | cat < a | grep hi > b"
	"export a | ls"
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
#        echo -e "${YELLOW}--- minishell ---${RESET}"
#        cat -e "$OUT_MINI"
#        echo -e "${YELLOW}--- bash ---${RESET}"
#        cat -e "$OUT_BASH"
#        echo -e "${YELLOW}--- status ---${RESET}"
#        echo -e "status mini: $STATUS_MINI"
#        echo -e "status bash: $STATUS_BASH"
#        echo

}

echo -e "${YELLOW}Running Minishell tests...${RESET}"
for t in "${tests[@]}"; do
    run_test "$t"
done

rm -f "$OUT_MINI" "$OUT_BASH" tmpfile out.txt "test.txt" result.txt roots.txt bash_users.txt a b


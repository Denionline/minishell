#!/usr/bin/env bash
set -euo pipefail

# This script:
# - builds the project (assumes `make` at repo root)
# - runs a set of simple commands through /bin/bash and ./minishell
# - compares outputs and exits non-zero if any test differs

cd "$(git rev-parse --show-toplevel 2>/dev/null || echo .)"

# Build
echo "Building project with make..."
if ! make; then
  echo "Build failed"
  exit 1
fi

BINARY="./minishell"
if [ ! -x "$BINARY" ]; then
  echo "Error: '$BINARY' not found or not executable after build"
  exit 1
fi

TIMEOUT="5s"
TMPDIR=$(mktemp -d)
trap 'rm -rf "$TMPDIR"' EXIT

# Tests: each entry is a shell script fed to both shells (supports multi-line tests)
tests=(
$'echo hello'
$'echo "multiple   spaces"'
$'printf "no newline"'
$'env | sort'
$'ls -1'
$'cat <<EOF\nline1\nline2\nEOF'
)

fail=0
i=0

for t in "${tests[@]}"; do
  i=$((i+1))
  printf '\n=== Test %d ===\n' "$i"
  printf '%s\n' "$t"
  printf '%s\n' "$t" > "$TMPDIR/input.txt"

  # Run bash
  timeout "$TIMEOUT" bash < "$TMPDIR/input.txt" > "$TMPDIR/bash.out" 2>&1 || true

  # Run minishell
  # Some minishell implementations print prompts only when interactive; running with stdin from file should not produce a prompt,
  # but if your implementation prints a prompt, you might need to adjust the script to strip it.
  timeout "$TIMEOUT" "$BINARY" < "$TMPDIR/input.txt" > "$TMPDIR/minishell.out" 2>&1 || true

  # Normalize line endings
  sed -i 's/\r$//' "$TMPDIR/"*.out

  if ! diff -u "$TMPDIR/bash.out" "$TMPDIR/minishell.out" > "$TMPDIR/diff"; then
    echo "Mismatch on test $i:"
    cat "$TMPDIR/diff"
    fail=1
  else
    echo "OK"
  fi
done

if [ "$fail" -ne 0 ]; then
  echo
  echo "Some tests failed."
  exit 1
else
  echo
  echo "All tests passed."
  exit 0
fi
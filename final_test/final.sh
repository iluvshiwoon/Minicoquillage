#!/usr/bin/env bash

# Define color codes
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
BLUE=$(tput setaf 4)
RESET=$(tput sgr0)

# Define a function to run a test case
run_test() {
  local line="$1"
  local bash_output
  local mini_output

  bash_output=$(bash --posix 2>&1 <<< "$(printf '%s\n' "$line")")
  bash_exit=$?
  bash_output=$(echo "$bash_output" | sed  's/bash: line [0-9]*: /minicoquillage: /')
if [ -n "$bash_output" ]; then
    pattern="minicoquillage: \`$line'"
  bash_output=$(echo "$bash_output" | grep -v -F "$pattern")
fi
mini_output=$(timeout 1 ./m_test "$line")
  # mini_output=$(./m_test "$line")
  mini_exit=$?
  mini_output=$(echo "$mini_output" | sed '/^exit$/d')
  # Compare the outputs
  if [ "$mini_output" != "$bash_output" ]; then
    printf "%sTest %d: Failed: '%s'%s\n" "$RED" "$TEST_COUNT" "$line" "$RESET"
    printf "  Expected: %s\n" "$bash_output"
    printf "  Got:      "
    diff_output=""
    for ((i=0; i<${#mini_output}; i++)); do
      if [ "${mini_output:i:1}" != "${bash_output:i:1}" ]; then
        diff_output+=$(tput setaf 1)
      else
        diff_output+=$(tput sgr0)
      fi
      diff_output+="${mini_output:i:1}"
    done
    printf "%s%s\n" "$diff_output" "$RESET"
    printf "\n"
    ((FAILED_TESTS++))
  elif [ "$bash_exit" -ne "$mini_exit" ]; then
    printf "%sTest %d: Failed: '%s'%s\n" "$RED" "$TEST_COUNT" "$line" "$RESET"
    printf "  Expected: %s\n" "$bash_exit"
    printf "  Got:      %s\n" "$mini_exit"
    ((FAILED_TESTS++))
    return 1
  fi 
  # Increment the test count
  ((TEST_COUNT++))
  return 0
}

# Define a function to print the test summary
print_summary() {
  printf "%s------------%s\n" "$BLUE" "$RESET"
  printf "%sTest Summary: Syntax%s\n" "$BLUE" "$RESET"
  printf "  Total Tests:  %d\n" "$TEST_COUNT"
  printf "  %sFailed Tests: %d%s\n" "$RED" "$FAILED_TESTS" "$RESET"
  printf "  %sPassed Tests: %d%s\n" "$GREEN" "$((TEST_COUNT - FAILED_TESTS))" "$RESET"
  printf "%s\n" "$RESET"
}

# Check if the input file is provided
if [ $# -ne 1 ]; then
  printf "Error: Input file not provided\n"
  exit 1
fi

# Check if the input file exists and can be read
if [ ! -f "$1" ] || [ ! -r "$1" ]; then
  printf "Error: Input file '%s' does not exist or cannot be read\n" "$1"
  exit 1
fi
# Initialize test counters
TEST_COUNT=0
FAILED_TESTS=0

mapfile -t lines < "$1"
for line in "${lines[@]}"; do
    run_test "$line"
    if [ $FAILED_TESTS -gt 0 ]; then
        break
    fi
done

# Run the test cases
# while IFS= read -r line; do
#   run_test "$line"
#   if [ $FAILED_TESTS -gt 0 ]; then
#     break
#   fi
# done < "$1"

# Print the test summary
print_summary

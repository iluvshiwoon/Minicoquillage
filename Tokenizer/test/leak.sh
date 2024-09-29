#!/usr/bin/env bash

# Set the path to your C program
PROGRAM="$2"
FILE="$1"

# Initialize a counter for the number of tests
TEST_COUNT=0
# Initialize a counter for the number of failed tests
FAILED_TESTS=0

echo ""
# Iterate over each row in the csv file
while IFS="," read -r input
do

    # Increment the test count
    ((TEST_COUNT++))

    # Execute your C program with the input
    
    # Compare the output with the expected output
    #
    if ! valgrind --quiet --leak-check=full --error-exitcode=1 \
        --exit-on-first-error=yes "$PROGRAM" "$input" 1> /dev/null; then
        # Increment the failed tests count
        ((FAILED_TESTS++))
        echo -e "\033[91mTest $TEST_COUNT: Memory leak detected!\033[0m"
        echo "  Input:    $input"
        echo
    fi
done < "$FILE"

# Print a summary
echo -e "\033[94m------------\033[0m"
echo -e "\033[94mTest Summary:\033[0m"
echo -e "  Total Tests:  $TEST_COUNT"
echo -e "  \033[91mFailed Tests: $FAILED_TESTS\033[0m"
echo -e "  \033[92mPassed Tests: $((TEST_COUNT - FAILED_TESTS))\033[0m"

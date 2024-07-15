#!/bin/bash

# Set the path to your C program
PROGRAM="$2"
FILE="$1"

# Initialize a counter for the number of tests
TEST_COUNT=0
# Initialize a counter for the number of failed tests
FAILED_TESTS=0

# Print a header
echo "Test Results:"
echo "------------"

# Iterate over each row in the csv file
while IFS="," read -r input
do

    # Increment the test count
    ((TEST_COUNT++))

    # Execute your C program with the input
    valgrind --quiet --leak-check=full --error-exitcode=1 "$PROGRAM" "$input" > /dev/null 2>&1
    
    # Compare the output with the expected output
    #
    if [ $? -ne 0 ]; then
        # Increment the failed tests count
        ((FAILED_TESTS++))
        echo -e "\033[91mTest $TEST_COUNT: Memory leak detected!\033[0m"
        echo "  Input:    $input"
        echo
    else
        echo -e "\033[92mTest $TEST_COUNT: Passed\033[0m"
    fi
done < "$FILE"

# Print a summary
echo -e "\033[94m------------\033[0m"
echo -e "\033[94mTest Summary:\033[0m"
echo -e "  Total Tests:  $TEST_COUNT"
echo -e "  \033[91mFailed Tests: $FAILED_TESTS\033[0m"
echo -e "  \033[92mPassed Tests: $((TEST_COUNT - FAILED_TESTS))\033[0m"

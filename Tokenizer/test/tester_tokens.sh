#!/bin/bash

# Set the path to your C program
PROGRAM="$2"
FILE="$1"

# Initialize a counter for the number of tests
TEST_COUNT=0
# Initialize a counter for the number of failed tests
FAILED_TESTS=0

# Print a header
# echo "Test Results:"
# echo "------------"
echo ""
# Iterate over each row in the csv file
while IFS="," read -r input expected_output
do

    # Increment the test count
    ((TEST_COUNT++))

    # Execute your C program with the input
    output=$("$PROGRAM" "$input")

    # Compare the output with the expected output
    if [ "\"$output\"" != "$expected_output" ]; then
        # Increment the failed tests count
        ((FAILED_TESTS++))
        printf "\033[91mTest %3d: Failed\033[0m\n" "$TEST_COUNT"
        echo "  Input:    $input"
        echo "  Expected: $expected_output"
        # echo "  Got:      '$output'"
        # echo
        echo -n "  Got:      "
        diff_output=""
        for ((i=0; i<${#output}; i++)); do
            if [ "${output:i:1}" != "${expected_output:i:1}" ]; then
                diff_output+='\033[91m'
            else
                diff_output+='\033[0m'
            fi
            diff_output+="${output:i:1}"
        done
        echo -e "$diff_output\033[0m"
        echo
    # else
    #     printf "\033[92mTest %3d: Passed\033[0m\n" "$TEST_COUNT"
    fi
done < "$FILE"

# Print a summary
echo -e "\033[94m------------\033[0m"
echo -e "\033[94mTest Summary: Tokens\033[0m"
echo -e "  Total Tests:  $TEST_COUNT"
echo -e "  \033[91mFailed Tests: $FAILED_TESTS\033[0m"
echo -e "  \033[92mPassed Tests: $((TEST_COUNT - FAILED_TESTS))\033[0m"


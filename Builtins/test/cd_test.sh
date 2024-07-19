#!/bin/bash

# Define a test directory and a backup for the current directory
TEST_DIR= 
ORIGINAL_DIR=$(pwd)
echo $(TEST_DIR)

# Creating the test directory if it doesn't exist
mkdir -p $TEST_DIR

# Environment setup
export PWD=$ORIGINAL_DIR
export CD_ERR="Change directory failed"

# Compiling the C program
gcc ../cd.c ../env.c -o test_cd -L../../42_MyLibC -lft

# Running the program with the test directory
./test_cd $TEST_DIR

# Check if the current directory changed to $TEST_DIR
if [[ $(pwd) != "$TEST_DIR" ]]; then
    echo "Directory change test failed."
else
    echo "Directory change test succeeded."
fi

# Check if PWD environment variable is set correctly
if [[ $PWD != "$TEST_DIR" ]]; then
    echo "Environment variable PWD was not updated correctly."
else
    echo "Environment variable PWD updated successfully."
fi

# Clean up
cd $ORIGINAL_DIR
rm -rf $TEST_DIR
rm -f test_cd

# Exit
exit 0

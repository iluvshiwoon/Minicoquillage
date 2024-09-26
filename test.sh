# Read the output from stdin
OUTPUT=$(cat)

# Check if any tests failed
FAILED_TESTS=$(echo "$OUTPUT" | grep -A 2 "Test [0-9]\+: Failed")

# If any tests failed, print the failed tests and the two following lines
if [ -n "$FAILED_TESTS" ]; then
    echo "$FAILED_TESTS"
else
    # If no tests failed, print the total summary
    SUMMARY=$(echo "$OUTPUT" | grep -A 3 "Test Summary")
    echo "$SUMMARY"
fi

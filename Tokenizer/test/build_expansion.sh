#!/bin/bash

# Set the output file
OUTPUT_FILE="$2"
INPUT_FILE="$1"

: > "$OUTPUT_FILE"
# Read the list of commands from a file (one command per line)
while IFS= read -r line; do
  # Run the command and capture the output
  output=$(eval echo "$line" 2>&1)

  # Store the command and output in the CSV file
  echo "$line,$output" >> "$OUTPUT_FILE"
done < "$INPUT_FILE"

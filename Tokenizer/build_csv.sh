#!/bin/bash

# Set the output file
OUTPUT_FILE="test.csv"
INPUT_FILE="command.txt"

> $OUTPUT_FILE
# Read the list of commands from a file (one command per line)
while IFS= read -r line; do
  # Run the command and capture the output
  output=$(eval "$line" 2>&1)

  # Store the command and output in the CSV file
  echo "$line,$output" >> "$OUTPUT_FILE"
done < $INPUT_FILE

# Replace every occurrence of "bash" with "Minicoquillage" in the output file
sed -i 's/,.*:/,Minicoquillage:/g' "$OUTPUT_FILE"
sed -i '2~2d' "$OUTPUT_FILE"

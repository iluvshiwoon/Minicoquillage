#!/bin/bash

# Set the input file and output CSV file
INPUT_FILE="$1"
OUTPUT_CSV="$2"

# Create the CSV header
: > "$OUTPUT_CSV"

# Read the input file line by line
while IFS= read -r line; do
  # Run your shell program with the input line and capture the output
  output=$(../../Minicoquillage "$line")

  # Create the CSV row
  csv_row="$line,\"$output\""
  echo "$csv_row" >> "$OUTPUT_CSV"
done < "$INPUT_FILE"

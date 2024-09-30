#!/usr/bin/env bash

# Set the output file
OUTPUT_FILE="$2"
INPUT_FILE="$1"

: > "$OUTPUT_FILE"
# Read the list of commands from a file (one command per line)
while IFS= read -r line; do
  # Run the command and capture the output
  line2bash=$(bash --posix 2>&1 <<EOF
$line 
EOF
)
  parser=$(./Minicoquillage "$line")
  parser2bash=$(bash --posix 2>&1 <<EOF
$parser 
EOF
)
# output=$(echo "$output" | sed '2d' | sed -r 's/^bash: line 1: (.*)$/Minicoquillage: \1/') 

  # Store the command and output in the CSV file
  echo "$parser2bash,$line2bash" >> "$OUTPUT_FILE"
done < "$INPUT_FILE"

# Replace every occurrence of "bash" with "Minicoquillage" in the output file
# sed -i 's/,.*:/,Minicoquillage:/g' "$OUTPUT_FILE"

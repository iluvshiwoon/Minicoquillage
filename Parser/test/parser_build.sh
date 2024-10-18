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
rm -f output.txt
# printf "%s" "$line2bash"
  parser=$(./Minicoquillage "$line")
  # printf "%s\n" "$parser"
  parser2bash=$(bash --posix 2>&1 <<EOF
$parser 
EOF
)
rm -f output.txt
# printf "%s" "$parser2bash"
# output=$(echo "$output" | sed '2d' | sed -r 's/^bash: line 1: (.*)$/Minicoquillage: \1/') 

  # Store the command and output in the CSV file
  echo "$(echo "$parser2bash" | tr -d '\n'),$(echo "$line2bash" | tr -d '\n')" >> "$OUTPUT_FILE"
done < "$INPUT_FILE"

# printf "%s\n" "$line2bash"
# printf "%s\n" "$parser2bash"
# Replace every occurrence of "bash" with "Minicoquillage" in the output file
# sed -i 's/,.*:/,Minicoquillage:/g' "$OUTPUT_FILE"

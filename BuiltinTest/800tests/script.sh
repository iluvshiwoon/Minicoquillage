#!/bin/bash --posix

INPUT_CSV="input.csv"
OUTPUT_TXT="output.txt"

# Vider le fichier de sortie s'il existe déjà
> "$OUTPUT_TXT"

# Lire le fichier CSV ligne par ligne
while IFS=, read -r first_column _; do
    # Écrire la première colonne dans le fichier de sortie
    echo "$first_column" >> "$OUTPUT_TXT"
done < "$INPUT_CSV"

echo "Les informations de la première colonne ont été stockées dans $OUTPUT_TXT"
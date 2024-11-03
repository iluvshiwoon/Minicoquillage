#!/bin/bash --posix

gcc -o ft_echo ./main.c ./../../Builtins/echo.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

INPUT_FILE="text_to_print.txt"


# Lire le fichier et affiche avec echo
while IFS= read line; do
# Run the command and capture the output
    echo $line  >>echo.txt
done < "$INPUT_FILE"

# Lire le fichier et affiche avec ft_echo
while IFS= read line; do
# Run the command and capture the output
    ./ft_echo "$line" >>ft_echo.txt
done < "$INPUT_FILE"


# Comparer les deux fichiers
diff echo.txt ft_echo.txt

# Supprimer les fichiers temporaires
rm echo.txt
rm ft_echo.txt

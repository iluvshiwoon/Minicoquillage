#!/bin/bash --posix

gcc -o ft_echo ./main.c ./../../Builtins/echo.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

INPUT_FILE="text_to_print.txt"

# Lire le fichier et affiche avec echo et option -n
while IFS= read line; do
# Run the command and capture the output
    echo "-n $line"  >>echo_option_n.txt
done < "$INPUT_FILE"

# Lire le fichier et affiche avec echo sans option -n
while IFS= read line; do
# Run the command and capture the output
    echo "$line"  >>echo.txt
done < "$INPUT_FILE"


# Lire le fichier et affiche avec ft_echo avec option -n
while IFS= read line; do
# Run the command and capture the output
    ./ft_echo "$line" 0 >>ft_echo.txt
done < "$INPUT_FILE"

# Lire le fichier et affiche avec ft_echo avec option -n
while IFS= read line; do
# Run the command and capture the output
    ./ft_echo "$line" 1 >>ft_echo_option_n.txt
done < "$INPUT_FILE"

# Comparer les deux fichiers
diff echo.txt ft_echo.txt
diff echo_option_n.txt ft_echo_option_n.txt

# Supprimer les fichiers temporaires
rm echo.txt
rm echo_option_n.txt
rm ft_echo.txt
rm ft_echo_option_n.txt

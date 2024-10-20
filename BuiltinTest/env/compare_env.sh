#!/bin/bash --posix

gcc -o my_env ./main.c ./../../Builtins/env.c ./../../Builtins/utils.c -L../../42_MyLibC -lft

# Exécutez la commande env et votre programme, en redirigeant les sorties
env | sort > original_env.txt
./my_env | sort > custom_env.txt

# Filtrer les lignes commençant par "_=" et comparer les sorties
grep -v '^_=' original_env.txt > filtered_original_env.txt
grep -v '^_=' custom_env.txt > filtered_custom_env.txt

# Comparez les fichiers filtrés
diff filtered_original_env.txt filtered_custom_env.txt

# Nettoyage des fichiers temporaires
rm original_env.txt custom_env.txt filtered_original_env.txt filtered_custom_env.txt

#!/bin/bash --posix

gcc -o my_env ./main.c ./../../Builtins/env.c ./../../Builtins/utils.c -L../../42_MyLibC -lft

# Exécutez la commande env et votre programme, en redirigeant les sorties
env | sort > original_env.txt
./my_env | sort > custom_env.txt

#Trier les fichier avant de les comparer
sort original_env.txt > original_env_sorted.txt
sort custom_env.txt > custom_env_sorted.txt

# Comparez les sorties
# diff original_env_sorted.txt custom_env_sorted.txt

#Comparer les sortie en omettant l variables "_="
diff <(grep -v '^_=' original_env_sorted.txt) <(grep -v '^_=' custom_env_sorted.txt)


#Comparaison des codes de retour

# Nettoyage des fichiers temporaires
rm original_env.txt custom_env.txt original_env_sorted.txt custom_env_sorted.txt

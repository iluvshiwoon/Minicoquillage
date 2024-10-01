#!/bin/bash

gcc -o my_env ./../../env.c -L../../../42_MyLibC -lft

# Exécutez la commande env et votre programme, en redirigeant les sorties
env | sort > original_env.txt
./my_env | sort > custom_env.txt

# Comparez les sorties
diff original_env.txt custom_env.txt

# Nettoyage des fichiers temporaires
rm original_env.txt custom_env.txt


# TODO
# chmod +x compare_env.sh
# ./compare_env.sh

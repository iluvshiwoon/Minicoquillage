#!/bin/bash --posix

gcc -o my_pwd ./main.c ./../../Builtins/pwd.c ./../../Builtins/utils.c -L../../42_MyLibC -lft

# Exécutez la commande env et votre programme, en redirigeant les sorties
pwd | sort > original_pwd.txt
./my_pwd | sort > custom_pwd.txt

# Comparez les sorties
diff original_pwd.txt custom_pwd.txt

# Nettoyage des fichiers temporaires
rm original_pwd.txt custom_pwd.txt


# TODO
# chmod +x compare_pwd.sh
# ./compare_pwd.sh

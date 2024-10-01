#!/bin/bash

gcc -o ft_export ./../../export.c  ./../../env.c -L../../../42_MyLibC -lft

# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS='=' read -r var val; do
    export "$var"="$val"
done < variables.txt

# Afficher les variables après export (Bash)
echo "Après export (Bash):"
env | grep 'VAR' > original_export.txt

# Réinitialiser les variables d'environnement
unset VAR1 VAR2 VAR3

# Utiliser votre programme C pour exécuter ft_export
# Assurez-vous que votre programme C est compilé et accessible sous le nom ft_export
while IFS='=' read -r var val; do
    ./ft_export "$var=$val"
done < variables.txt

# Afficher les variables après ft_export (C)
echo "Après ft_export (C):"
grep 'VAR' > custom_export.txt


diff original_export.txt custom_export.txt

# Nettoyage des fichiers temporaires
# rm original_export.txt custom_export.txt

# TODO
# chmod +x compare_env.sh
# ./compare_export.sh

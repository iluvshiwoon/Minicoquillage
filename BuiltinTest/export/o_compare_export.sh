#!/bin/bash

gcc -o ft_export ./main.c ./../../Builtins/export.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS='=' read -r var val; do
    export "$var"="$val" && env
done < variables.txt
# while IFS='=' read -r var val; do
#     # Supprimer les espaces en début et fin de chaîne
#     var=$(echo "$var" | xargs)
#     val=$(echo "$val" | xargs)

#     # Vérifier que var n'est pas vide et ne commence pas par un caractère non valide
#     if [[ -n "$var" && "$var" =~ ^[a-zA-Z_][a-zA-Z0-9_]*$ ]]; then
#         export "$var=$val"
#     else
#         echo "Ignoré : $var=$val"
#     fi
# done < variables.txt


# Afficher les variables après export (Bash)
echo "Après export (Bash):"
env | grep 'VAR' > original_export.txt
# cat original_export.txt

# Réinitialiser les variables d'environnement
unset VAR1 VAR2 VAR3

# Utiliser votre programme C pour exécuter ft_export
# Assurez-vous que votre programme C est compilé et accessible sous le nom ft_export
while IFS='=' read -r var val; do
    ./ft_export "$var=$val" > my_export.txt
    grep $var < my_export.txt >> custom_export.txt
done < variables.txt



# Afficher les variables après ft_export (C)
echo "Après ft_export (C):"
# cat custom_export.txt

# Trie les fichiers pour comparer les sorties
sort original_export.txt > sort_original_export.txt
sort custom_export.txt > sort_custom_export.txt

diff sort_original_export.txt sort_custom_export.txt

# Nettoyage des fichiers temporaires
rm original_export.txt custom_export.txt my_export.txt sort_original_export.txt sort_custom_export.txt

# TODO
# chmod +x compare_env.sh
# ./compare_export.sh

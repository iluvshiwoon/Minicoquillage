#!/bin/bash

gcc -g3 -o ft_export ./main.c ./../../Builtins/export.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

# Parcourir un fichier et ajouter les variables d'environnement avec export
# while IFS='=' read -r var val; do
# 	export "$var"="$val" && env
# done < variables.txt

# Spécifiez le nom du fichier
file_name="variables.txt"


# Lire chaque ligne du fichier
while IFS=' ' read -ra elements; do
    # Exécuter un export pour chaque élément splitté
    for element in "${elements[@]}"; do
        IFS='=' read -r var val <<< "$element"
        export "$var=$val"
    done
done < "$file_name"

env > original_export.txt

while IFS=' ' read -ra elements; do
	for element in "${elements[@]}"; do
		IFS='=' read -r var val <<< "$element"
		set -e "$var" > my_export.txt
	done
done < original_export.txt

env | sort > original_env.txt

./ft_export > custom_export.txt

cat original_env.txt | sort > sort_original_env.txt
cat original_export.txt | sort > sort_original_export.txt
cat custom_export.txt | sort > sort_custom_export.txt

diff sort_original_export.txt sort_custom_export.txt

rm original_export.txt custom_export.txt my_export.txt sort_original_export.txt sort_custom_export.txt
rm original_env.txt


#!/bin/bash

gcc -o ft_export ./main.c ./../../Builtins/export.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

# Parcourir un fichier et ajouter les variables d'environnement avec export
# while IFS='=' read -r var val; do
# 	export "$var"="$val" && env
# done < variables.txt

# Spécifiez le nom du fichier
file_name="variables.txt"

env > original_env.txt

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

original_env.txt > sort_original_env.txt
original_export.txt > sort_original_export.txt

diff sort_original_env.txt sort_original_export.txt


#!/bin/bash



gcc -o ft_unset ./main.c ./../../unset.c  ./../../env.c -L../../../42_MyLibC -lft

env | sort > original_env.txt
# cat original_env.txt | sort > cpy_original_env.txt

# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS=' ' read -r export_val unset_val; do
    export $export_val && env > env_update.txt
done < variables.txt
# cat env_update.txt

# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS=' ' read -r export_val unset_val; do
    unset $unset_val && env > env_unset.txt
done < variables.txt
# cat env_unset.txt

# Comparer les variables d'environnement avant et après l'exécution de unset
diff env_update.txt env_unset.txt

# # Créer un fichier temporaire pour stocker les résultats
temp_file=$(mktemp)


while IFS=' ' read -r export_val unset_val; do

	# Rechercher la variable dans le fichier
	if grep -q "^$variable=" "$fichier"; then
		# Afficher la variable et sa valeur
		grep "^$variable=" "$fichier" >> env_unset.txt
	fi



# # Créer un fichier temporaire pour stocker les résultats
# temp_file=$(mktemp)

# # Lire chaque ligne du fichier original_file
# while IFS= read -r export_val unset_val; do
#     # Appliquer le programme pgrm sur la ligne
#     result=$(echo "$line" | ./pgrm unset_val)

#     # Ajouter le résultat au fichier temporaire
#     echo "$result" >> "$temp_file"
# done < original_file

# # Remplacer le fichier original_file par le fichier temporaire
# mv "$temp_file" original_file

# # Comparer les variables d'environnement
# diff original_env.txt custom_env.txt

# # Nettoyer les fichiers temporaires
# rm original_env.txt custom_env.txt new_env.txt ft_unset

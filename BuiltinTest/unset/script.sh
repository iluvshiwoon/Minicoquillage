#!/bin/bash

# Vérifiez si le fichier my_commandes.txt existe
if [ ! -f my_commandes.txt ]; then
    echo "Le fichier my_commandes.txt n'existe pas."
    exit 1
fi

gcc -o my_unset ./main.c ./../../unset.c ./../../env.c ./../../utils.c -L../../../42_MyLibC -lft

while IFS= read -r commande; do
    # Exécuter la commande lue
    echo "Exécution de la commande : $commande"
    eval "$commande"

	# Exécutez la commande env et votre programme, en redirigeant les sorties
	env | sort > original_env.txt
	./my_unset $commande | sort > custom_env.txt

	# Filtrer les lignes commençant par "_=" et comparer les sorties
	grep -v '^_=' original_env.txt > filtered_original_env.txt
	grep -v '^_=' custom_env.txt > filtered_custom_env.txt

	# Comparez les fichiers filtrés
	diff filtered_original_env.txt filtered_custom_env.txt

	# Nettoyage des fichiers temporaires
	rm original_env.txt custom_env.txt filtered_original_env.txt filtered_custom_env.txt
done < my_commandes.txt



# !/bin/bash



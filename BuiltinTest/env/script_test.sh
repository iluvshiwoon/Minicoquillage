#!/bin/bash --posix


# Lire chaque ligne du fichier my_commandes.txt, execute la commande et compare les sortie
while IFS='=' read -r var val; do
	export "$var"="$val"
	bash ./compare_env.sh
done < my_commandes.txt


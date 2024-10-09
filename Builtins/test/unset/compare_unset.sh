#!/bin/bash

gcc -o ft_unset ./main.c ./../../unset.c  ./../../env.c -L../../../42_MyLibC -lft

bash --posix
env | sort > original_env.txt

# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS='=' read -r var val; do
    export $var=$val
done < variables.txt

# Pour chaque ligne de my_commandes.txt, extraire la valeur sur la ligne et executer
# la fonction main.c avec pour argument la valeur extraite
while IFS= read -r commande; do
	./ft_unset $command
done < my_variables.txt > new_env.txt
cat new_env.txt | sort > custom_env.txt

# Comparer les variables d'environnement
diff original_env.txt custom_env.txt

# Nettoyer les fichiers temporaires
rm original_env.txt custom_env.txt new_env.txt ft_unset

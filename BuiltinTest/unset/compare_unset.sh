#!/bin/bash



gcc -o ft_unset ./main.c ./../../Builtins/unset.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

# env | sort > original_env.txt
# cat original_env.txt | sort > cpy_original_env.txt

# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS=' ' read -r export_var unset_val; do
    export $export_var
done < variables.txt
#  cat env_update.txt

# Lire le fichier d'entrée et définir les variables d'environnement avec unset
while IFS=' ' read -r export_val unset_val; do
    unset $unset_val && env > env_unset.txt
done < variables.txt
# cat env_unset.txt

# Comparer les variables d'environnement avant et après l'exécution de unset
# diff env_update.txt env_unset.txt

while IFS=' ' read -r export_val unset_val; do
    export $export_val && env > env_update.txt
done < variables.txt
# cat env_update.txt



# Lire le fichier dentree et utiliser la fonction ft_unset
# si ft unset sest bien effectue mettre a jour env
# sinon ecrire un message derreur
while IFS=' ' read -r export_val unset_val; do
	./ft_unset $unset_val | sort > ft_tmp.txt
	# Rechercher la variable dans le fichier
	if grep -q "^$unset_val=" ft_tmp.txt; then
		# Afficher la variable et sa valeur
		echo "ERR:var '$unset_val', NOT unset"
	else
		# Mettre a jour les variables d'environnement pour la prochaine iteration
		unset $unset_val && env > ft_update.txt
	fi
done < variables.txt

# Trier avec sort tout les fichier txt
sort env_update.txt > env_update_sort.txt
sort ft_update.txt > ft_update_sort.txt
sort ft_tmp.txt > ft_tmp_sort.txt

# # Comparer les varaiables d'environnement avant et apres executer ft_unset
diff ft_tmp_sort.txt ft_update_sort.txt


# # Comparer les variables d'environnement
# diff original_env.txt custom_env.txt

# # Nettoyer les fichiers temporaires txt non tries
rm env_update.txt ft_update.txt ft_tmp.txt env_unset.txt

# # Nettoyer les fichiers temporaires txt tries
rm env_update_sort.txt
# rm ft_update_sort.txt ft_tmp_sort.txt

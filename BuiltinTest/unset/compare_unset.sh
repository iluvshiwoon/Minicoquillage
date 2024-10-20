#!/bin/bash --posix

gcc -o ft_unset ./main.c ./../../Builtins/unset_2.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

# # ENV
# Exporter les variables d'environnement dans un fichier
env | sort > original_env.txt

# # EXPORT
# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS=' ' read -r export_var; do
    export $export_var && env > env_update.txt
done < variables_export.txt

# # UNSET
# Lire le fichier d'entrée et définir les variables d'environnement avec unset
while IFS=' ' read -r unset_val; do
    unset $unset_val && env > env_unset.txt
done < variables_unset.txt


# Comparer les variables d'environnement après l'exécution de unset et avant l export
cat original_env.txt | sort > original_env_sort.txt
cat env_unset.txt | sort > env_unset_sort.txt
diff env_unset_sort.txt original_env_sort.txt

# # EXPORT
# Lire le fichier d'entrée et définir les variables d'environnement avec export
while IFS=' ' read -r export_var; do
    export $export_var && env > env_update_2.txt
done < variables_export.txt
# Verifier que les variables d'environnement sont sur le meme condition initial pour unset et ft_unset
diff env_update.txt env_update_2.txt

# # FT_UNSET
# Lire le fichier dentree et utiliser la fonction ft_unset
# si ft unset sest bien effectue mettre a jour env
# sinon ecrire un message derreur dans le fichier ft_unset_fail.txt
while IFS=' ' read -r unset_val; do
	./ft_unset $unset_val | sort > ft_unset_tmp.txt
	# Rechercher la variable dans le fichier
	if grep -q "^$unset_val=" ft_unset_tmp.txt; then
		# Afficher la variable et sa valeur
		echo "ERR:var '$unset_val', unset fails" >> ft_unset_fail.txt
	else
		# Mettre a jour les variables d'environnement pour la prochaine iteration
		unset $unset_val && env > ft_unset_update.txt
	fi
done < variables_unset.txt

# Compare les variables d'environnement original et apres executer ft_unset
rm ft_unset_tmp.txt
cat ft_unset_update.txt | sort > ft_update_sort.txt
diff ft_update_sort.txt env_unset_sort.txt

# # Nettoyer les fichiers temporaires txt non tries
rm original_env.txt
rm env_unset.txt
rm env_update.txt
rm env_update_2.txt
rm ft_unset_update.txt

# Fichier temporaire pour les erreurs
# rm ft_unset_fail.txt

# # Nettoyer les fichiers temporaires txt tries
rm original_env_sort.txt
# rm env_unset_sort.txt
# rm ft_update_sort.txt


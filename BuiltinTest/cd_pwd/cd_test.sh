#!/bin/bash

cc -o ft_cd ./main.c ./../../Builtins/cd.c ./../../Builtins/pwd.c ./../../Builtins/env.c -L../../42_MyLibC -lft

# Créer un lien symbolique et un répertoire
touch path_ft_cd
touch path_cd

# Cree une variable chemin qui contient le chemin du répertoire courant
path_of_fonction="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/cd_pwd"

# utilise les commandes de base en utilisant cd et fd
while IFS= read line; do
	echo $line
	mv path_cd $line
	cd $line
	pwd >> path_cd
	mv path_cd $path_of_fonction
	cd $path_of_fonction
done < my_paths.txt

# Lire chaque ligne du fichier my_paths.txt
while IFS= read line; do
	./ft_cd $line  >> path_ft_cd
done < my_paths.txt

sort path_cd > sort_path_cd.txt
sort path_ft_cd > sort_path_ft_cd.txt

echo "######################################################################################################################################################################################################################################################################"

diff sort_path_cd.txt sort_path_ft_cd.txt


# rm path_cd sort_path_cd.txt
# rm path_ft_cd sort_path_ft_cd.txt

# /home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/cd_pwd/res
# /home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/echo/res
# /home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/env
# ./../../
# ~/Documents
# ~/Documents/..
# ~~/Documents
# ~/~/Documents



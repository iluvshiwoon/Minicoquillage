#!/bin/bash



cc -o ft_cd ./main.c ./../../Builtins/cd.c ./../../Builtins/pwd.c ./../../Builtins/env.c -L../../42_MyLibC -lft


# Cree une variable chemin qui contient le chemin du répertoire courant
# path_of_fonction="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/cd_pwd"
path_of_fonction="/workspaces/Minicoquillage/BuiltinTest/cd_pwd"
path_cd="/workspaces/Minicoquillage/BuiltinTest/cd_pwd/path_cd"


# utilise les commandes de base en utilisant cd et fd
while IFS= read line; do
	if cd "$line" &> /dev/null; then
        echo "$(pwd)" >> $path_cd
    else
        echo "Error Path" >> $path_cd
    fi
done < my_path_dock.txt



# echo "######################################################################################################################################################################################################################################################################"

cd $path_of_fonction
# Lire chaque ligne du fichier my_paths.txt
while IFS= read line; do
	./ft_cd $line  >> path_ft_cd
done < my_path_dock.txt

diff path_ft_cd path_cd

# rm path_ft_cd path_cd






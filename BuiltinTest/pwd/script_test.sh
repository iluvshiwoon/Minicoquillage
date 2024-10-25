#!/bin/bash --posix


gcc -o my_pwd ./main.c ./../../Builtins/pwd.c ./../../Builtins/utils.c -L../../42_MyLibC -lft

# Nom du fichier à lire
fichier="my_commandes.txt"
path_of_fonction="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/pwd"
script="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/pwd/compare_pwd.sh"
binary="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/pwd/my_pwd"


# Vérifiez si le fichier my_commandes.txt existe
if [ ! -f "$fichier" ]; then
    echo "Le fichier my_commandes.txt n'existe pas."
    exit 1
fi


import_script_binary()
{
    # Lire le fichier ligne par ligne
    while IFS=' ' read -r cmd myPath; do
    # Copier le script et le binaire dans le répertoire spécifié
        if [ $path_of_fonction  != $myPath ]; then
            cp $binary $myPath
            cp $script $myPath
        else
            :
        fi
    done < "$fichier"
}


my_test()
{
    # Lire le fichier ligne par ligne
    while IFS=' ' read -r cmd my_path; do
        # # Exécuter la commande lue avec ses arguments
        eval $cmd $my_path

        # Appeler le script compare_pwd.sh
        bash "$script"

    done < "$fichier"

}


import_script_binary
my_test



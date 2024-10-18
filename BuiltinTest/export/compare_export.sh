#!/bin/bash --posix

gcc -g3 -o ft_export ./main.c ./../../Builtins/export.c  ./../../Builtins/env.c -L../../42_MyLibC -lft

# Spécifiez le nom du fichier
file_name="variables.txt"

env | sort > original_env.txt

execute_original_export(){
    # Lire chaque ligne du fichier
    while IFS=' ' read -ra elements; do
        # Exécuter un export pour chaque élément splitté
        for element in "${elements[@]}"; do
            IFS='=' read -r var val <<< "$element"
            export "$var=$val" 2>>error_export.txt
        done
    done < "$file_name"
    env | sort > sort_original_export.txt
    cat sort_original_export.txt
}

remove_original_export()
{
    while IFS=' ' read -ra elements; do
        for element in "${elements[@]}"; do
            IFS='=' read -r var val <<< "$element"
            unset "$var"
        done
    done < "$file_name"
}

execute_ft_export()
{
    ./ft_export >custom_export.txt 2>>error_ft_export.txt
}

execute_original_export
remove_original_export
execute_ft_export

# diff sort_original_export.txt sort_custom_export.txt

# rm -f original_export.txt
# rm -f custom_export.txt
# rm -f sort_original_export.txt
# rm -f sort_custom_export.txt
# rm -f original_env.txt


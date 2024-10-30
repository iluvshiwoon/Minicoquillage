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
            output=$?
            echo "$output" >> return_export.txt
        done
    done < "$file_name"
    env | sort > sort_original_export.txt
}

clean_error_export_file()
{
    while IFS= read -r line; do
        output=$(echo "$line" | sed -r 's/^.\/compare_export.sh: line 16: (.*)$/\1/')
        echo "$output" >> clean_error_export.txt
    done < error_export.txt
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
    output=$?
    echo "$output" >> return_ft_export.txt
    cat "custom_export.txt" | sort > sort_custom_export.txt
}

execute_ft_export
execute_original_export
clean_error_export_file
remove_original_export

diff sort_original_export.txt sort_custom_export.txt
diff clean_error_export.txt error_ft_export.txt

rm original_env.txt
rm sort_original_export.txt
rm error_export.txt
rm clean_error_export.txt
rm custom_export.txt
rm sort_custom_export.txt
rm error_ft_export.txt

rm return_export.txt
rm return_ft_export.txt

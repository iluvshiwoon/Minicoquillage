# #recuperer les valeur de retour de export

file_name="variables.txt"

execute_original_export(){
    # Lire chaque ligne du fichier
    while IFS=' ' read -ra elements; do
        # Exécuter un export pour chaque élément splitté
        for element in "${elements[@]}"; do
            IFS='=' read -r var val <<< "$element"
            export "$var=$val" 2>/dev/null
			my_return=$?
			echo $my_return>>return_export.txt
        done
    done < "$file_name"
}

execute_ft_export()
{
    ./ft_export 2>>error_ft_export.txt
    echo $? >> return_ft_export.txt
}

execute_original_export
execute_ft_export

rm return_export.txt

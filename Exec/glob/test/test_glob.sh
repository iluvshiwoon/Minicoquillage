#!/bin/bash

# compile programme C globbing.c
cc -g3 ../globbing.c  -L../../../42_MyLibC -lft -o globbing

while IFS=' ' read -r str glob; do
    ./globbing "$str" "$glob"
done < tests.txt > results_custom.txt

# Fonction pour tester le globbing
function test_glob {
    local str=$1
    local glob=$2

    if [[ $str == $glob ]]; then
        echo 1
        return 1
    else
        echo 0
        return 0
    fi
}

# Lire les tests à partir du fichier tests.txt
while IFS= read -r line; do
    str=$(echo $line | cut -d' ' -f1)
    glob=$(echo $line | cut -d' ' -f2)
    test_glob "$str" "$glob"
done < tests.txt > results_origin.txt

# Comparer les résultats
diff results_custom.txt results_origin.txt


#!/bin/bash --posix

gcc -o ft_exit ./main.c ./../../Builtins/exit.c ./../../Builtins/utils.c -L../../42_MyLibC -lft

INPUT_FILE="code_exit.txt"

# Fonction pour tester le code de retour de ft_exit
test_ft_exit() {
    ./ft_exit $1
    local exit_code=$?
    # echo "Test avec argument '$1' : Code de retour = $exit_code"
	return $exit_code
}

# Fonction pour tester le code de retour de exit
test_exit() {
    ouput=$(bash --posix -c "exit $1")
    local exit_code=$?
    # echo "Test avec argument '$1' : Code de retour = $exit_code"
	return $exit_code
}

count=0
# Test automatique a partir d'entree issue dun fichier
while IFS= read line; do
	test_exit "$line"
	test1_exit=$?
	test_ft_exit "$line"
	test1_ft_exit=$?
	if [ $test1_ft_exit -eq $test1_exit ]; then
		echo "Test $count réussi : exit argument : '$line'"
	else
		echo "Test $count échoué"
		echo "exit retourne $test1_exit"
		echo "ft_exit retourne $test1_ft_exit"
	fi
	echo
	count=$((count+1))
done < "$INPUT_FILE"

# # Test 1: Appel sans argument
# test_exit
# test1_exit=$?
# test_ft_exit
# test1_ft_exit=$?
# if [ $test1_ft_exit -eq $test1_exit ]; then
#     echo "Test 1 réussi : exit sans argument"
# else
#     echo "Test 1 échoué"
# fi
# echo

# # Test 2: Appel avec un code de retour valide
# test_exit 42
# test2_exit=$?
# if [ $test2_exit -eq 42 ]; then
#     echo "Test 2 réussi : exit avec code 42"
# else
#     echo "Test 2 échoué"
# fi
# echo

# # Test 3: Appel avec un code de retour invalide
# test_exit "invalid"
# test3_exit=$?
# if [ $test3_exit -eq 2 ]; then
#     echo "Test 3 réussi : exit avec argument invalide"
# else
#     echo "Test 3 échoué"
# fi
# echo

# # Test 4: Appel avec un code de retour négatif
# test_exit -1
# test4_exit=$?
# if [ $test4_exit -eq 255 ]; then
#     echo "Test 4 réussi : exit avec code -1"
# else
#     echo "Test 4 échoué"
# fi

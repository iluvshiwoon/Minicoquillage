#!/bin/bash --posix

path_of_fonction="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/pwd"
script="./compare_pwd.sh"
binary="./my_pwd"


# Exécutez la commande env et votre programme, en redirigeant les sorties
pwd | sort > original_pwd.txt
./my_pwd | sort > custom_pwd.txt



# Comparez les sorties
diff original_pwd.txt custom_pwd.txt

# Nettoyage des fichiers temporaires
rm original_pwd.txt custom_pwd.txt

m_path=$(pwd)

if [ $path_of_fonction  == $m_path ]; then
	:
else
	rm $script
	rm $binary
fi

cd "$path_of_fonction"

#!/bin/bash --posix

cc -o ft_cd ./main.c ./../../Builtins/cd.c ./../../Builtins/pwd.c ./../../Builtins/env.c -L../../42_MyLibC -lft

# # SECTION 1
INPUT_FILE=./my_path.txt
# INPUT_FILE= ./my_path_dock.txt

# # SECTION 2
# Cree une variable chemin qui contient le chemin du répertoire courant
#UBUNTU
# path_of_fonction="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/cd_pwd"
# path_cd="/home/bsunda/Documents/projet_1/Minicoquillage/BuiltinTest/cd_pwd/path_cd"
#FEDORA
# path_cd="/home/bsunda/Documents/projet/Minicoquillage/BuiltinTest/cd_pwd/path_cd"
# path_of_fonction="/home/bsunda/Documents/Projet/Minicoquillage/BuiltinTest/cd_pwd"
#DOCKER
path_of_fonction="/workspaces/Minicoquillage/BuiltinTest/cd_pwd"
path_cd="/workspaces/Minicoquillage/BuiltinTest/cd_pwd/path_cd"


# # SECTION 3
# rm path_ft_cd.txt path_cd.txt

# # SECTION 4
# # utilise les commandes de base en utilisant cd
while IFS= read line; do
     # Run the command and capture the output
    output=$(bash --posix 2>&1 <<EOF
cd $line && pwd
EOF
)
output=$(echo "$output" | sed '2d' | sed -r 's/^bash: line 1: (.*)$/\1/')
  # Store the command and output in the CSV file
  echo "$output" >> path_cd.txt
done < "$INPUT_FILE"

# # SECTION 5
# # utilise les commandes de base en utilisant ft_cd
cd "$path_of_fonction"
# Lire chaque ligne du fichier my_paths.txt
while IFS= read line; do
# Run the command and capture the output
    # ./ft_cd $line  >>path_ft_cd.txt 2>>path_ft_cd.txt
    ./ft_cd $line  >>path_ft_cd.txt 2>>path_ft_cd.txt
done < "$INPUT_FILE"


# # SECTION 6
diff path_ft_cd.txt path_cd.txt

# # SECTION 7
rm path_ft_cd.txt path_cd.txt


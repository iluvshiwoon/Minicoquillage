#!/bin/bash

cc -o ft_cd ./main.c ./../../cd.c ./../../pwd.c ./../../env.c -L../../../42_MyLibC -lft

while IFS= read line; do
	echo $line >> path.txt
	# ./ft_cd $line
done < my_paths.txt

# sort path.txt > sort_path.txt
# sort my_cd.txt > sort_my_cd.txt

# diff sort_path.txt sort_my_cd.txt

# rm path.txt my_cd.txt sort_path.txt sort_my_cd.txt

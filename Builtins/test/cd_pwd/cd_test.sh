#!/bin/bash

cc -o ft_cd ./main.c ./../../cd.c ./../../pwd.c ./../../env.c -L../../../42_MyLibC -lft

rm path_cd.txt sort_path_cd.txt sort_my_paths.txt
rm path_ft_cd.txt sort_path_ft_cd.txt
rm ft_cd_link

while IFS= read line; do
	echo $line >> path_cd.txt
	ln -s ft_cd ft_cd_link
	mv ft_cd_link $line
	cd $line
	./ft_cd_link line >> path_ft_cd.txt
done < my_paths.txt

sort path_cd.txt > sort_path_cd.txt
sort my_paths.txt > sort_my_paths.txt
sort path_ft_cd.txt > sort_path_ft_cd.txt

diff sort_path_cd.txt sort_my_paths.txt

rm path_cd.txt sort_path_cd.txt sort_my_paths.txt
rm path_ft_cd.txt sort_path_ft_cd.txt
rm ft_cd_link

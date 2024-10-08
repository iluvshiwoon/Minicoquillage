#!/bin/bash

# Vérifiez si le fichier my_commandes.txt existe
if [ ! -f my_commandes.txt ]; then
    echo "Le fichier my_commandes.txt n'existe pas."
    exit 1
fi

# Lire chaque ligne du fichier my_commandes.txt
while IFS= read -r commande; do
    # Exécuter le script compare_pwd.sh avec la commande lue
    echo "Exécution de la commande : $commande"
    ./compare_pwd.sh "$commande"
done < my_commandes.txt

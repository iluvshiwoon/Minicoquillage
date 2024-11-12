import subprocess
import os

# Nom du script à exécuter
script_name_0 = 'format_0.py'
script_name_1 = 'format_1.py'
script_name_2 = 'format_2.py'

# Exécuter le script format.py
result = subprocess.run(['python3', script_name_0], check=True, text=True, capture_output=True)

# Exécuter le script format.py
result = subprocess.run(['python3', script_name_1], check=True, text=True, capture_output=True)

# Exécuter le script format.py
result = subprocess.run(['python3', script_name_2], check=True, text=True, capture_output=True)

# Ouvrir le fichier input.txt en mode lecture
with open('format.txt', 'r') as infile:
    # Lire toutes les lignes du fichier
    lines = infile.readlines()

# Initialiser une liste pour stocker les lignes modifiées
modified_lines = []

# Parcourir chaque ligne pour supprimer tout après le dernier ';'
for line in lines:
    # Trouver la position du dernier ';'
    last_semicolon_index = line.rfind(';')

    if last_semicolon_index != -1:
        # Garder tout jusqu'au dernier ';'
        modified_line = line[:last_semicolon_index]
    else:
        # Si aucun ';' n'est trouvé, garder la ligne inchangée
        modified_line = line

    # Ajouter la ligne modifiée à la liste
    modified_lines.append(modified_line.strip())  # Utiliser strip() pour enlever les espaces superflus

# Écrire les lignes modifiées dans output.txt
with open('cmds_test.txt', 'w') as outfile:
    for modified_line in modified_lines:
        outfile.write(modified_line + '\n')


####################################################

def supprimer_fichier(nom_fichier):
    """Supprime le fichier spécifié s'il existe."""
    if os.path.exists(nom_fichier):
        os.remove(nom_fichier)  # Supprimer le fichier
        print(f"Le fichier {nom_fichier} a été supprimé.")
    else:
        print(f"Le fichier {nom_fichier} n'existe pas.")

# Exemple d'utilisation de la fonction
supprimer_fichier('output.txt')
supprimer_fichier('formatted_output.txt')
supprimer_fichier('format.txt')

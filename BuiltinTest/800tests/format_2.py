# Ouvrir le fichier input.txt en mode lecture
with open('formatted_output.txt', 'r') as infile:
    # Lire toutes les lignes
    lines = infile.readlines()

# Initialiser une liste pour stocker les lignes concaténées
output_lines = []
current_line = ""

# Parcourir les lignes pour les traiter
for line in lines:
    if line == '\n':
        # Si la ligne est vide, on ajoute la ligne courante à la liste de sortie
        if current_line:
            output_lines.append(current_line)
            current_line = ""  # Réinitialiser pour la prochaine ligne
    else:
        # Concaténer la ligne courante
        current_line += line.strip() + " "  # Ajouter un espace pour séparer les lignes

# Ajouter la dernière ligne si elle existe
if current_line:
    output_lines.append(current_line.strip())

# Écrire le résultat dans output.txt
with open('format.txt', 'w') as outfile:
    for line in output_lines:
        outfile.write(line + '\n')

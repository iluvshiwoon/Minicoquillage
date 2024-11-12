# Nom du fichier à lire
nom_fichier = 'output.txt'

# Lire le fichier et traiter les lignes
with open(nom_fichier, 'r') as fichier:
	lignes = fichier.readlines()

# Créer une nouvelle liste pour stocker les lignes modifiées
lignes_modifiees = []

# Parcourir les lignes et ajouter un ';' si la ligne n'est pas vide
for ligne in lignes:
	ligne = ligne.rstrip('\n')  # Enlever le '\n' à la fin de la ligne
	if ligne:  # Vérifier si la ligne n'est pas vide
		ligne += ';'  # Ajouter ';' à la fin de la ligne
	lignes_modifiees.append(ligne)  # Ajouter la ligne (modifiée ou non) à la liste

# Écrire les lignes modifiées dans un nouveau fichier
with open('formatted_output.txt', 'w') as fichier_modifie:
	for ligne in lignes_modifiees:
		fichier_modifie.write(ligne + '\n')  # Ajouter '\n' à la fin de chaque ligne

print("Le fichier a été modifié et enregistré sous 'formatted_output.txt'.")

import csv

# Nom du fichier CSV à lire
csv_filename = 'input.csv'

# Nom du fichier de sortie
output_filename = 'output.txt'

# Ouvrir le fichier CSV en lecture
with open(csv_filename, 'r') as csvfile:
    csvreader = csv.reader(csvfile)

    # Ouvrir le fichier de sortie en mode ajout
    with open(output_filename, 'a') as outputfile:
        for row in csvreader:
            if row:  # Vérifier que la ligne n'est pas vide
                # Écrire la première colonne dans le fichier de sortie
                outputfile.write(row[0] + '\n')
                # Ajouter une ligne vide
                outputfile.write('\n')

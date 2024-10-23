#!/bin/bash

gcc -o binary redir_heredoc.c -L../../../42_MyLibC -lft





# Définir le délimiteur pour le heredoc
LIMITER="EOF"

# Utiliser le heredoc du Bash pour capturer l'entrée
cat <<$LIMITER > bash_output.txt
Ceci est un test.
Ligne suivante.
$LIMITER

# Utiliser votre programme C pour capturer l'entrée
# Assurez-vous que votre programme C est compilé et accessible sous le nom heredoc
./binary "$LIMITER"


# Comparer les résultats des deux opérations
if diff bash_output.txt /tmp/heredoc > /dev/null; then
    echo "Les résultats sont identiques."
else
    echo "Les résultats sont différents."
    echo "Différences:"
    diff bash_output.txt /tmp/heredoc
fi

# Nettoyer les fichiers temporaires
rm bash_output.txt /tmp/heredoc

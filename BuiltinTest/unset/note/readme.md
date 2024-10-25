SHLVL est une variable d'environnement dans les systèmes Unix et Linux qui indique le niveau de profondeur de l'interpréteur de commandes (shell). Chaque fois qu'un nouveau shell est lancé à partir d'un shell existant, la valeur de SHLVL est incrémentée de 1. Par exemple, si vous ouvrez un terminal et que vous lancez un nouveau shell, SHLVL passera de 1 à 2. Cela permet de savoir combien de niveaux de shell sont imbriqués.

Cette variable peut être utile pour les scripts ou les programmes qui doivent se comporter différemment selon le niveau de profondeur du shell.

#include <stdlib.h>
#include <stdio.h>
#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>

void exit_custom(int status)
{
	// Appeler exit avec le code de sortie
	exit(status);
}

int main()
{
    printf("Ce programme va se terminer.\n");
    exit_custom(0); // Appel de la fonction personnalisée
	printf("Ce message ne sera jamais affiché.\n");
    return 0; // Ce code ne sera jamais atteint
}

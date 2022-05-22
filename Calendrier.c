/*******************************************************************************
* TP1_INF3135
*
* Description: construire un logiciel qui traduit une date du calendrier grégorien
* vers trois (3) des calendriers mayas : compte long, Haab et Tzolk'in.
*
* Author: OUSSAMA EL-FIGHA
* Author: NICOLAS PLANTE
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stddef.h>


int main(int argc, char const *argv[])
{
        //Valider le nombre d'argument saisi par l'utilisateur
    if(argc<=1 && argc > 3) {
        printf("Vous ne m'avez pas nourri d'arguments, ou vous m'avez trops nourri, je vais mourir maintenant :( ...");
        exit(1);
    }

    //transformer les argument de string à des Ints et les afficher
    for (int i = 0; i < argc; i++)
    {
        printf("%i\n", atoi(argv[i]));
    }
    return 0;
}



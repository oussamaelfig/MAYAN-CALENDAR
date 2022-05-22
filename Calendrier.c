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
#define max_yr 4772
#define min_yr -3113
const int true = 1;
const int false = 0;

// Fonction qui verifie si la date est bissextile ou pas
// Si la date est bissextile retourner 1
int estBissextile(int y)
{
    if ((y % 4 == 0) && (y % 100 != 0) && (y % 400 == 0))
        return true;
    else
        return false;
}

// Fonction qui va servir pour verifier si la date est plus petit que la date maximale
int smaller(int d, int m, int y)
{
    if (y <= max_yr)
        return 1; // compare years
    if (y == max_yr && m <= 10)
        return 1; // compare months - but make sure years are equal
    if (y == max_yr && m == 10 && d <= 12)
        return 1; // compare days but make sure years and months are equal
    return 0;
}

// Fonction qui va servir pour verifier si la date est plus grande que la date minimale
int greater(int d, int m, int y)
{
    if (y >= min_yr)
        return 1; // compare years
    if (y == min_yr && m >= 8)
        return 1; // compare months - but make sure years are equal
    if (y == min_yr && m == 8 && d >= 11)
        return 1; // compare days but make sure years and months are equal
    return 0;
}

// Fonction qui valide si la date est valide ou non
int dateValid(int d, int m, int y)
{
    // Valider si la date est entre Max et Min
    if (!greater(d, m, y) || !smaller(d, m, y))
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;
    // On va verifier les mois dépendemment de la date
    if (m == 2)
    {
        if (estBissextile(y))
        {
            if (d <= 29)
                return true;
            else
                return false;
        }
    }
    // Avrile, Juin, Septembre et Novembre ont 30 jours
    if (m == 4 || m == 6 || m == 9 || m == 11)
        if (d <= 30)
            return true;
        else
            return false;
    return true;
}

int main(int argc, char const *argv[])
{
    // Valider le nombre d'argument saisi par l'utilisateur
    if (argc <= 1 && argc > 3)
    {
        printf("Vous ne m'avez pas nourri d'arguments, ou vous m'avez trops nourri, je vais mourir maintenant :( ...");
        exit(1);
    }

    int jours;
    int mois;
    int annee;

    // transformer les argument de string à des Ints et les afficher
    for (int i = 0; i < argc; i++)
    {
        jours = atoi(argv[1]);
        mois = atoi(argv[2]);
        annee = atoi(argv[3]);
    }

    if (dateValid(jours, mois, annee) == true)
    {
        printf("Le jours est :%i\n", jours);
        printf("Le mois est :%i\n", mois);
        printf("L'annee est :%i\n", annee);
    }
    else
    {
        printf("La date n'est pas valide !");
        exit(-1);
    }

    return 0;
}

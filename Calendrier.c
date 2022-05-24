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
const int AN_MAX = 4772;
const int AN_MIN = -3114;
const int true = 1;
const int false = 0;

enum _MOIS
{
    BIDON,
    JANVIER,
    FEVRIER,
    MARS,
    AVRIL,
    MAI,
    JUIN,
    JUILLET,
    AOUT,
    SEPTEMBRE,
    OCTOBRE,
    NOVEMBRE,
    DECEMBRE
};

typedef enum _MOIS MOIS;

// Fonction qui verifie si la date est bissextile ou pas
// Si la date est bissextile retourner 1
int estBissextile(int y)
{
    int result;

    if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
        result = true;
    else
        result = false;

    return result;
}

/*
    Fonction qui calcule le nombre de jour qui est ecoules depuis le 11 aout -3114
    En tenant compte des années bissextiles.
    La valeur retournee est le nombre de jour ecoules (int).
*/
int nbJoursTotal(int jour, int mois, int annee)
{
    int jTotal = 0;
    int boucleAnnee = AN_MIN;
    int boucleMois = AOUT;
    // Boucle qui ajoute le bon nb de jours selon l'année
    while (boucleAnnee < annee - 1)
    {
        if (estBissextile(boucleAnnee))
        {
            jTotal += 366;
        }
        else
        {
            jTotal += 365;
        }
        ++boucleAnnee;
    }
    //car dans le calcul on compte une annee "0". Elle doit etre retiree car elle n'existe pas
    if(annee > 0){
        jTotal -= 365;
    }

    // Boucle qui ajoute le nombre de jours pour chaque mois jusqu'a arriver au mois entre en argument.
    while (boucleMois != mois)
    {
        ++boucleMois;
        if(boucleMois > 12){
            boucleMois = 1;
        }
        switch (boucleMois)
        {
        case JANVIER:
        case MARS:
        case MAI:
        case JUILLET:
        case AOUT:
        case OCTOBRE:
        case DECEMBRE:
            jTotal += 31;
            break;
        case AVRIL:
        case JUIN:
        case SEPTEMBRE:
        case NOVEMBRE:
            jTotal += 30;
            break;
        case FEVRIER:
            if (estBissextile(annee))
            {
                jTotal += 29;
            }
            else
            {
                jTotal += 28;
            }
            break;
        default:
            printf("Le defaut pour le mois.");
            break;
        }
        

    }
    //ajustement car la date de debut est le onze de aout
    jTotal += jour - 11;

    return jTotal;
}

// Fonction qui va servir pour verifier si la date est plus petit que la date maximale
int smaller(int d, int m, int y)
{
    int result = false;

    if (y <= AN_MAX)
        result = true; // compare years
    else if (y == AN_MAX && m <= 10)
        result = true; // compare months - but make sure years are equal
    else if (y == AN_MAX && m == 10 && d <= 12)
        result = true; // compare days but make sure years and months are equal
    return result;
}

// Fonction qui va servir pour verifier si la date est plus grande que la date minimale
int greater(int d, int m, int y)
{
    int result = false;

    if (y >= AN_MIN)
        result = true; // compare years
    else if (y == AN_MIN && m >= 8)
        result = true; // compare months - but make sure years are equal
    else if (y == AN_MIN && m == 8 && d >= 11)
        result = true; // compare days but make sure years and months are equal
    return result;
}

// Fonction qui valide si la date est valide ou non
int dateValid(int d, int m, int y)
{
    int result = true;

    // Valider si la date est entre Max et Min
    if (greater(d, m, y) == false || smaller(d, m, y) == false)
        result = false;
    else if (m < 1 || m > 12)
        result = false;
    else if (d < 1 || d > 31)
        result = false;
    // On va verifier les mois dépendemment de la date
    else if (m == 2)
    {
        if (estBissextile(y))
        {
            if (d <= 29)
                result = true;
            else
                result = false;
        }
    }
    // Avril, Juin, Septembre et Novembre ont 30 jours
    else if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        if (d <= 30)
            result = true;
        else
            result = false;
    }
    // result = true;

    return result;
}

int main(int argc, char const *argv[])
{
    // Valider le nombre d'argument saisi par l'utilisateur
    if (argc <= 1 && argc > 3)
    {
        printf("Vous ne m'avez pas nourri d'arguments, ou vous m'avez trop nourri, je vais mourir maintenant :( ...");
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
        printf("La date n'est pas valide !\n");
        exit(-1);
    }
    printf("test\n");
    int nb = nbJoursTotal(jours, mois, annee);
    printf("%i\n", nb);

    return 0;
}

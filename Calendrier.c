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

enum _HAAB
{
    POP,
    WO,
    SIP,
    SOTZ,
    SEK,
    XUL,
    YAXKIN,
    MOL,
    CHEN,
    YAX,
    SAK,
    KEH,
    MAK,
    KANKIN,
    MUWAN,
    PAX,
    KAYAB,
    KUMKU
};

typedef enum _MOIS MOIS;
typedef enum _HAAB HAAB;

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
    La valeur retournee est le nombre de jour ecoules (int jTotal).
*/
int nbJoursTotal(int jour, int mois, int annee)
{
    int jTotal = 0;
    int boucleAnnee = AN_MIN;
    int boucleMois = AOUT;
    // Boucle qui ajoute le bon nb de jours selon l'année (bissextile ou pas)
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
    // car dans le calcul on compte une annee "0". Elle doit etre retiree car elle n'existe pas
    if (annee > 0)
    {
        jTotal -= 365;
    }

    // Boucle qui ajoute le nombre de jours pour chaque mois jusqu'a arriver au mois entre en argument.
    while (boucleMois != mois)
    {
        ++boucleMois;
        if (boucleMois > 12)
        {
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
    // ajustement car la date de debut est le onze de aout
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


/*
    Fonction qui trouve le numero qui est associe au mois Haab
    a partir du enum _HAAB.
    Prend en argument un int * nbJ afin de pouvoir modifier le nbJ. (nbJ par reference)
    Retourne le numero du mois correspondant.
*/
int trouverMoisHaab(int * nbJ)
{
    int cptMois = 0;
    printf("%d\n", *nbJ);
    while (*nbJ > 20)
    {
        if(cptMois > 18)
        {
            ///L'ajustement pour e Wayeb
            *nbJ -= 5;
            cptMois = 0;
        }
        *nbJ -= 20;
        ++cptMois;
    }
    //Si jamais *nbj tombe dans une valeur negative
    if(*nbJ < 0)
    {
        *nbJ = 0;
    }
    printf("%d\n", *nbJ);
    printf("%d\n", cptMois);

    return cptMois;
}

/*
    Fonction void qui est responsable d'afficher la date convertie en
    format en Haab.
    Prend en argument en int nbJ qui le nombre de jours depuis le 11 aout -3114.
*/
void afficherHaab(int nbJ)
{
    printf("test\n");
    char *nMois = malloc(10 * sizeof(char));
    printf("test\n");

    int numMois = trouverMoisHaab(&nbJ);
    //printf("test\n");

    //On cree un tableau qui contient toutes les noms de mois
    char *tabMois[18];
    tabMois[0] = "Pop";
    tabMois[1] = "Wo";
    tabMois[2] = "Sip";
    tabMois[3] = "Sotz";
    tabMois[4] = "Sek";
    tabMois[5] = "Xul";
    tabMois[6] = "Yaxk'in";
    tabMois[7] = "Mol";
    tabMois[8] = "Ch'en";
    tabMois[9] = "Yax";
    tabMois[10] = "Sak";
    tabMois[11] = "Keh";
    tabMois[12] = "Mak";
    tabMois[13] = "K'ank'in";
    tabMois[14] = "Muwan";
    tabMois[15] = "Pax";
    tabMois[16] = "K'ayab";
    tabMois[17] = "KumK'u";

    nMois = tabMois[numMois];
    printf("Haab : %i %s\n", nbJ, nMois);
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
    int nbJours = nbJoursTotal(jours, mois, annee);
    printf("%i\n", nbJours);
    printf("test\n");
    afficherHaab(nbJours);
    return 0;
}

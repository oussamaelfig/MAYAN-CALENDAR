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

// constantes
const int AN_MAX = 4772;
const int AN_MIN = -3114;
const int true = 1;
const int false = 0;

// Tous les mois dans un enum
enum _MOIS
{
    JANVIER = 1,
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
typedef enum _HAAB HAAB;

/*
    Fonction qui verifie si la date est bissextile ou pas
    Entree = int y qui est l'annee a analyser
    return int result (true si la date est bissextile sinon false)
*/
int estBissextile(int y)
{
    int result;

    if (y < 0)
    {
        y += 1;
    }
    if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0))
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

/*
    Fonction qui calcule le nombre de jour qui est ecoules depuis le 11 aout -3114
    En tenant compte des années bissextiles.
    Entrees => int jour, int mois, int annee (les arguments entres par l'utilisateur)
    return le nombre de jour ecoules (int jTotal).
*/
int nbJoursTotal(int jour, int mois, int annee)
{
    int jTotal = 0;
    int boucleAnnee = AN_MIN;
    int boucleMois = AOUT;

    // ajustement du mois de base selon si le mois entre est plus petit que AOUTs
    if (mois < AOUT)
    {
        boucleMois = JANVIER;
        jTotal += 153;
        boucleAnnee += 1;
    }
    else
    {
        if (estBissextile(annee))
        {
            jTotal += 1;
        }
    }

    if (annee > 1)
    {
        jTotal += 365;
    }

    // Boucle qui ajoute le bon nb de jours selon l'année (bissextile ou pas)
    while (boucleAnnee < annee)
    {
        if (estBissextile(boucleAnnee))
        {
            jTotal += 366;
        }
        else
        {
            jTotal += 365;
        }
        if (boucleAnnee + 1 == 0)
        {
            boucleAnnee += 2;
        }
        ++boucleAnnee;
    }

    // Boucle qui ajoute le nombre de jours pour chaque mois jusqu'a arriver au mois entre en argument.
    while (boucleMois != mois)
    {
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
            fprintf(stderr, "Le defaut pour le mois.");
            break;
        }

        ++boucleMois;

        if (boucleMois > 12)
        {
            boucleMois = 1;
        }
    }

    jTotal += jour - 11;
    return jTotal;
}

/* 
    Fonction qui va servir pour verifier si la date est plus petit que la date maximale
    Entree = int jour, int mois, int annee (qui sont les arguments entres par l'utilisateur)
    return true ou false selon la validite de la date
*/
int plusPetit(int d, int m, int y)
{
    int result = false;

    if (y < AN_MAX)
        result = true;
    else if (y == AN_MAX && m < 10)
        result = true;
    else if (y == AN_MAX && m == 10 && d <= 12)
        result = true;
    return result;
}

/* 
    Fonction qui va servir pour verifier si la date est plus grande que la date minimale
    Entree = int jour, int mois, int annee (qui sont les arguments entres par l'utilisateur)
    return true ou false selon la validite de la date
*/
int plusGrand(int d, int m, int y)
{
    int result = false;

    if (y > AN_MIN)
        result = true;
    else if (y == AN_MIN && m > 8)
        result = true;
    else if (y == AN_MIN && m == 8 && d >= 11)
        result = true;
    return result;
}

/*
    Fonction qui valide si la date est valide ou non
    Entree = int jour, int mois, int annee (qui sont les arguments entres par l'utilisateur)
    return int result (boolean true si valide sinon false)
*/
int dateValid(int d, int m, int y)
{
    int result = true;

    // Valider si la date est entre Max et Min
    if (plusGrand(d, m, y) == false || plusPetit(d, m, y) == false)
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

//*********************************HAAB*************************************

/*
    Fonction qui trouve le numero qui est associe au mois Haab
    a partir du enum _HAAB.
    Prend en argument un int * nbJ afin de pouvoir modifier le nbJ. (nbJ par reference)
    Retourne le numero du mois correspondant.
*/
int trouverMoisHaab(int *nbJ)
{
    // debute au mois Kumk'u
    int cptMois = 17;
    // ajustement selon le 0.0.0.0.0
    *nbJ += 8;

    int estFini = 1;

    while ((*nbJ < 5 && cptMois == 17) || estFini)
    {
        if (cptMois == 18 && *nbJ > 5)
        {
            /// L'ajustement pour le Wayeb
            *nbJ -= 5;
            cptMois = -1;
        }
        else if (cptMois > 18)
        {
            cptMois = -1;
            *nbJ -= 20;
        }
        else if (*nbJ < 20)
        {
            estFini = 0;
        }
        else
        {
            *nbJ -= 20;
        }
        ++cptMois;
    }
    --cptMois;

    return cptMois;
}

/*
    Procedure void qui est responsable d'afficher la date convertie en
    format en Haab.
    Prend en argument en int nbJ qui le nombre de jours depuis le 11 aout -3114.
*/
void afficherHaab(int nbJ)
{
    char *nMois = malloc(10 * sizeof(char));
    // afin de ne pas modifier le vrai nbJours, on fait une copie
    int nbJours = nbJ;
    char *moisCN;
    int numMois = trouverMoisHaab(&nbJours);

    // On cree un tableau qui contient toutes les noms de mois
    char *tabMois[19];
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
    // Periode de 5 jours qui n'est pas un mois (indice 18 du tab)
    tabMois[18] = "Wayeb";

    nMois = tabMois[numMois];
    // ajout char null a la fin
    moisCN = malloc((strlen(nMois) + 1) * sizeof(char));
    strcpy(moisCN, nMois);
    // Affichage
    printf("Haab : %i %s\n", nbJours, nMois);
}

//*********************************COMPTE LONG*************************************
/*
    Procedure void qui est responsable de convertir et d'afficher la date convertie en
    format en compte long.
    Prend en argument en int nbJ qui le nombre de jours depuis le 11 aout -3114.
*/
void compteLong(int nbJourEcoules)
{

    int d, baktun, katun, tun, uinal, kin;
    // pour que le test 29 août 683 et 20 décembre 2012
    // marchent il faut que
    // j'additionne d = nbJourEcoules+365;
    // d+=365;
    d = nbJourEcoules + 365;
    d = nbJourEcoules;
    baktun = d / 144000;
    d %= 144000;
    katun = d / 7200;
    d %= 7200;
    tun = d / 360;
    d %= 360;
    uinal = d / 20;
    kin = d % 20;

    printf("Compte Long : %d.%d.%d.%d.%d\n", baktun, katun, tun, uinal, kin);
}

//*********************************TZOLKIN*************************************
/*
    Procedure void qui est responsable de convertir et d'afficher la date convertie en
    format en Tzolkin.
    Prend en argument en int nbJ qui le nombre de jours depuis le 11 aout -3114.
*/
void tzolkin(int nbJourEcoules)
{
    // Pour que 20 décembre 2012 marche faux travailler avec (nbJourEcoules+366)
    // Pour que 29 août 683 marche faux travailler avec (nbJourEcoules+365)
    // 11 août -3114 et 1 janvier 2000 marchent bien
    int nombre;
    int nom;
    char arr[20][15] = {"Imix", "Ik", "Akbal", "Kan", "Chicchan", "Cimi", "Manik", "Lamat", "Muluc", "Oc", "Chuen", "Eb", "Ben", "Ix", "Men", "Cib",
                        "Caban", "Etznab", "Cauac", "Ahau"};
    nombre = (((nbJourEcoules + 3) % 13) + 1);

    nom = ((nbJourEcoules + 19) % 20);

    printf("Tzolk'in : %d %s\n", nombre, arr[nom]);
}

//MAIN
int main(int argc, char const *argv[])
{
    // Valider le nombre d'argument saisi par l'utilisateur
    if (argc != 4)
    {
        printf("Vous devez rentrer trois arguments seulement! (jj dd aaaa)\n");
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

    if (!dateValid(jours, mois, annee))
    {
        printf("La date n'est pas valide !\n");
        exit(-1);
    }
    int nbJours = nbJoursTotal(jours, mois, annee);
    afficherHaab(nbJours);
    compteLong(nbJours);
    tzolkin(nbJours);
    return 0;
}
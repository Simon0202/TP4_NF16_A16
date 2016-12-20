#ifndef tp4_h
#define tp4_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maxName 50

//********************
//*****Structures*****
//********************
typedef struct Benevole{
    char *nom;
    char *prenom;
    char sexe;
    int carteIdentite;
    int anneeDeNaissance;
    struct Benevole *suivant;
}Benevole;

typedef struct ListBenevoles{
    Benevole *benevole;
    int nbreElement;
}ListBenevoles;

typedef struct Tranche{
    ListBenevoles *listBenevole;
    int borneSup;
    struct Tranche *pere;
    struct Tranche *filsG;
    struct Tranche *filsD;
}Tranche;


//***************************************
//*****Initialisation des structures*****
//***************************************
Benevole *nouveauBen(char *nom, char *prenom, int CIN, char sexe, int annee);
Tranche *nouvelleTranche(int borneSup);
ListBenevoles *nouvelleListe();
#endif /* tp4_h */


//***************
//*****Ajout*****
//***************
Tranche *ajoutTranche(Tranche *racine, int borneSup);
Benevole *insererBen(Tranche *racine, Benevole *benevole);


//Addeed
int calculTranche(Benevole *benevole);
int ajoutBenevole(ListBenevoles* liste,Benevole *benevole);
void ParcoursArbre(Tranche *racine);


//Time
int anneeActuelle();

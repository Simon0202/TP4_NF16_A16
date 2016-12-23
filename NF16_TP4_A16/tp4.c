#include "tp4.h"

//***************************************
//*****Initialisation des structures*****
//***************************************
Benevole *nouveauBen(char *nom, char *prenom, int CIN, char sexe, int annee){
    Benevole *newBenevole = malloc(sizeof(struct Benevole));
    if(newBenevole==NULL)
        exit(EXIT_FAILURE);
    
    newBenevole->anneeDeNaissance = annee;
    newBenevole->sexe = sexe;
    newBenevole->carteIdentite = CIN;
    
    newBenevole->prenom = malloc(maxName);
    strcpy(newBenevole->prenom, prenom);
    newBenevole->nom = malloc(maxName);
    strcpy(newBenevole->nom, nom);
    
    newBenevole->suivant = NULL;
    
    
    return newBenevole;
}

ListBenevoles *nouvelleListe(){
    ListBenevoles *newListe = malloc(sizeof(struct ListBenevoles));
    if(newListe==NULL)
        exit(EXIT_FAILURE);
    
    newListe->benevole=NULL;
    newListe->nbreElement=0;
    
    return newListe;
}

Tranche *nouvelleTranche(int borneSup){
    Tranche *newTranche = malloc(sizeof(struct Tranche));
    if(newTranche==NULL)
        exit(EXIT_FAILURE);
    
    newTranche->borneSup = borneSup;
    newTranche->listBenevole = nouvelleListe();
    newTranche->filsD = NULL;
    newTranche->filsG = NULL;
    newTranche->pere = NULL;
    
    return newTranche;
}


//***************
//*****Ajout*****
//***************
Tranche *ajoutTranche(Tranche *racine, int borneSup){
    
    Tranche *ajoutElement = NULL;
    Tranche *pere=NULL;
    
    while(racine!=NULL){
        if(racine->borneSup<borneSup){
            pere = racine;
            racine = racine->filsD;
        }
        else if(racine->borneSup>borneSup){
            pere = racine;
            racine = racine->filsG;
        }
        else{
            printf("Le noeud existe déjà\n");
            return NULL;
        }
    }
    
    if(pere == NULL){
        racine = nouvelleTranche(borneSup);
        return racine;
    }
    else{
        if(pere->borneSup>borneSup){
            ajoutElement = nouvelleTranche(borneSup);
            ajoutElement->pere = pere;
            pere->filsG = ajoutElement;
        }
        else{
            ajoutElement = nouvelleTranche(borneSup);
            ajoutElement->pere = pere;
            pere->filsD = ajoutElement;
        }

        return ajoutElement;
    }
}
//Fin ajoutTranche


Benevole *insererBen(Tranche *racine, Benevole *benevole){
    Tranche *TrancheBenevole = racine;
    
    int borneSup = calculTrancheBenevole(benevole);
    
    while(TrancheBenevole!=NULL && TrancheBenevole->borneSup!=borneSup){
        if(TrancheBenevole->borneSup>borneSup)
            TrancheBenevole = TrancheBenevole->filsG;
        else
            TrancheBenevole = TrancheBenevole->filsD;
    }
    
    if(TrancheBenevole==NULL)
        TrancheBenevole = ajoutTranche(racine, borneSup);

    
    if(ajoutBenevole(TrancheBenevole->listBenevole, benevole)==1){
        printf("ajout reussi\n");
        return benevole;
    }

    else{
        printf("aucun ajout\n");
        return NULL;
    }
}
//Fin de InsererBenevole


//On choisit de passer annee par copie. Aucun interet au passage par adresse
Benevole *chercherBen(Tranche *racine,int CIN, int annee){
    int borneSup = calculTrancheAnnee(annee);
    Benevole *benevoleRecherche = NULL;
    
    while(racine!=NULL && racine->borneSup!=borneSup){
        if(racine->borneSup > borneSup)
            racine=racine->filsG;
        else if(racine->borneSup < borneSup)
            racine= racine->filsD;
    }

    if(racine==NULL){
        printf("Le benevole recherche n'existe pas");
        return NULL;
    }
    
     benevoleRecherche = racine->listBenevole->benevole;
    
    while(benevoleRecherche!=NULL && benevoleRecherche->carteIdentite!=CIN)
        benevoleRecherche = benevoleRecherche->suivant;
    
    if(benevoleRecherche==NULL){
        printf("Le benevole recherche n'existe pas");
        return NULL;
    }
    
    return benevoleRecherche;
}
//Fin de chercherBen


ListBenevoles *BenDhonneur(Tranche *racine){
    int anneeMax;
    Benevole *benevoleMax = NULL;
    Benevole *benevole = NULL;
    ListBenevoles *listHonneur = nouvelleListe();
    
    
    while(racine->filsD!=NULL)
        racine = racine->filsD;
    
    if(racine==NULL)
        return NULL;
    
    benevoleMax = racine->listBenevole->benevole;
    benevole = racine->listBenevole->benevole;
    
    while(benevoleMax->suivant!=NULL)
        benevoleMax = benevoleMax->suivant;
    
    anneeMax = benevoleMax->anneeDeNaissance;
    
    while(benevole->anneeDeNaissance!=anneeMax)
        benevole = benevole->suivant;
    
    
    while(benevole != NULL && benevole->anneeDeNaissance==anneeMax){
        ajoutBenevole(listHonneur, benevole);
        benevole = benevole->suivant;
    }
    
    return listHonneur;
}
//Fin de benevole d'honneur.



//*********************
//*****Suppression*****
//*********************


//*********************
//*****Mise a Jour*****
//*********************

//*******************
//*****Affichage*****
//*******************
void afficherTranche(Tranche *racine, int borneSup);


void afficherTranche(Tranche *racine, int borneSup){
    Benevole *benevoles = NULL;
    
    
    while(racine!=NULL && racine->borneSup!=borneSup)
        if(racine->borneSup<borneSup)
            racine = racine->filsD;
        else
            racine = racine->filsG;
    
    benevoles = racine->listBenevole->benevole;
    
    if(benevoles==NULL){
        printf("Aucun benevole pour cette tranche d'age\n");
    }
    else{
        while(benevoles!=NULL){
            printf("%c\t",benevoles->sexe);
            printf("%s\t", benevoles->nom);
            printf("%s\t", benevoles->prenom);
            printf("%d\t",benevoles->anneeDeNaissance);
            printf("CIN:%d\n",benevoles->carteIdentite);
        
            benevoles = benevoles->suivant;
        }
    }
}








//****************
//*****Addeed*****
//****************
int calculTrancheBenevole(Benevole *benevole){
    int age = anneeActuelle()-benevole->anneeDeNaissance;
    int modulo = age%5;
    if(age%5==0)
        return age;
    else
        return age-modulo+5;
}
//Fin de calculTranche

int calculTrancheAnnee(int annee){
    int age = anneeActuelle()-annee;
    int modulo = age%5;
    if(age%5==0)
        return age;
    else
        return age-modulo+5;
    
}


int ajoutBenevole(ListBenevoles* liste,Benevole *benevole){
    Benevole *premier = liste->benevole;
    Benevole *precedent = NULL;
    
    if(liste->nbreElement==0){
        liste->benevole = benevole;
        liste->nbreElement++;
        return 1;
    }
    while(premier!=NULL && premier->anneeDeNaissance!=benevole->anneeDeNaissance && premier->anneeDeNaissance>=benevole->anneeDeNaissance){
            precedent = premier;
            premier = premier->suivant;
    }
    while(premier!=NULL && premier->carteIdentite!=benevole->carteIdentite && premier->anneeDeNaissance>=benevole->anneeDeNaissance){
            precedent = premier;
            premier = premier->suivant;
    }
    
    if(premier==NULL){
        precedent->suivant = benevole;
        benevole->suivant = premier;
        liste->nbreElement++;
        return 1;
    }
    if(premier->carteIdentite==benevole->carteIdentite){
        printf("Personne déjà existante\n");
        return 0;
    }
    

    if(precedent!=NULL){
        precedent->suivant = benevole;
        benevole->suivant = premier;
        liste->nbreElement++;
        return 1;
    }
        
    benevole->suivant = premier;
    liste->benevole = benevole;
    liste->nbreElement++;
    return 1;
}
//Fin de ajoutBenevole

void ParcoursArbre(Tranche *racine){
    if(racine->filsG!=NULL)
        ParcoursArbre(racine->filsG);
    printf("%d\t",racine->borneSup);
    if (racine->filsD!=NULL) {
        ParcoursArbre(racine->filsD);
    }
}
//Fin de ParcoursArbre

//Time
int anneeActuelle(){
    time_t secondes;
    struct tm instant; time(&secondes);
    instant = *localtime(&secondes); return instant.tm_year + 1900;
}
//Fin de anneeActuelle

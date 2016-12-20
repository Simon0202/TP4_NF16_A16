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
    
    Tranche *rememberRoot = racine;
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
            printf("Le noeud existe déjà");
            racine = NULL;
        }
    }
    
    if(pere == NULL){
        racine = nouvelleTranche(borneSup);
        return racine;
    }
    else{
        ajoutElement = nouvelleTranche(borneSup);
        ajoutElement->pere = pere;
        return ajoutElement;
    }
}
//Fin ajoutTranche


//Écrire la fonction qui permet d’ajouter un bénévole dans un ABR. Si la tranche d’âge à laquelle devrait appar- tenir le bénévole n’existe pas, elle devra être créée. L’ajout se fait en respectant le tri par ordre croissant d’âge du bénévole. Si ce bénévole est déjà présent dans une liste, il ne sera pas ajouté.
Benevole *insererBen(Tranche *racine, Benevole *benevole){
    Tranche *TrancheBenevole = racine;
    
    int borneSup = calculTranche(benevole);
    
    while(TrancheBenevole!=NULL && TrancheBenevole->borneSup!=borneSup){
        if(TrancheBenevole->borneSup>borneSup)
            TrancheBenevole = TrancheBenevole->filsG;
        else
            TrancheBenevole = TrancheBenevole->filsG;
    }
    
    if(racine==NULL)
        TrancheBenevole = ajoutTranche(racine, borneSup);

    
    if(ajoutBenevole(TrancheBenevole->listBenevole, benevole)==1){
        printf("ajout reussi");
        return benevole;
    }

    else{
        printf("aucun ajout");
        return NULL;
    }
}


//Addeed
int calculTranche(Benevole *benevole){
    int age = anneeActuelle()-benevole->anneeDeNaissance;
    int modulo = age%5;
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
    else{
        while(premier!=NULL && premier->anneeDeNaissance!=benevole->anneeDeNaissance){
            precedent = premier;
            premier = premier->suivant;
        }
        while(premier!=NULL && premier->carteIdentite!=benevole->carteIdentite && premier->anneeDeNaissance==benevole->anneeDeNaissance){
            precedent = premier;
            premier = premier->suivant;
        }
        
        
        if(premier==NULL){
            precedent->suivant = benevole;
            benevole->suivant = premier;
            liste->nbreElement++;
            return 1;
        }
        else if(premier->carteIdentite==benevole->carteIdentite){
            printf("Personne déjà existante");
            return 0;
        }
        else{
            precedent->suivant = benevole;
            benevole->suivant = premier;
            liste->nbreElement++;
            return 1;
        }
        
    }
}


void ParcoursArbre(Tranche *racine){
    if(racine->filsG!=NULL)
        ParcoursArbre(racine->filsG);
    printf("%d\t",racine->borneSup);
    if (racine->filsD!=NULL) {
        ParcoursArbre(racine->filsD);
    }
}

//Time
int anneeActuelle(){
    time_t secondes;
    struct tm instant; time(&secondes);
    instant = *localtime(&secondes); return instant.tm_year + 1900;
}


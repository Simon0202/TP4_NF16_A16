//
//  tp4.c
//  NF16_TP4_A16
//
//  Created by LAURENT SIMON on 16/12/2016.
//  Copyright © 2016 LAURENT SIMON. All rights reserved.
//

#include "tp4.h"

//***************************************
//*****Initialisation des structures*****
//***************************************
Benevole *nouveauBen(char *nom, char *prenom, int CIN, char sexe, int annee){
    Benevole *newBenevole = malloc(sizeof(newBenevole));
    if(newBenevole==NULL)
        exit(EXIT_FAILURE);
    
    newBenevole->anneeDeNaissance = annee;
    newBenevole->sexe = sexe;
    newBenevole->carteIdentite = CIN;
    
    newBenevole->prenom = malloc(sizeof(maxName));
    strcpy(newBenevole->prenom, prenom);
    newBenevole->nom = malloc(sizeof(maxName));
    strcpy(newBenevole->nom, nom);
    
    newBenevole->suivant = NULL;
    
    
    return newBenevole;
}

Tranche *nouvelleTranche(int borneSup){
    Tranche *newTranche = malloc(sizeof(newTranche));
    if(newTranche==NULL)
        exit(EXIT_FAILURE);
    
    newTranche->borneSup = borneSup;
    newTranche->listBenevole = NULL;
    newTranche->filsD = NULL;
    newTranche->filsG = NULL;
    newTranche->pere = NULL;

    return newTranche;
}

ListBenevoles *nouvelleListe(){
    ListBenevoles *newListe = malloc(sizeof(newListe));
    if(newListe==NULL)
        exit(EXIT_FAILURE);
    
    newListe->benevole=NULL;
    newListe->nbreElement=0;
    
    return newListe;
}


//***************
//*****Ajout*****
//***************
//Écrire la fonction qui permet d’ajouter (créer) un nœud dans l’ABR passé en paramètre. Si ce nœud existe, l’ajout ne se fera pas.
Tranche *ajoutTranche(Tranche *racine, int borneSup){
    
    Tranche *newTranche;
    
    if(racine==NULL){
        newTranche = nouvelleTranche(borneSup);
    }
    else{
        Tranche *root = parcours_abre(racine, borneSup);
    }
    
    
    return NULL;
}




//Addeed
Tranche *parcours_abre(Tranche *racine, int borneSup){
    if(racine>borneSup){
        if(racine->filsG==NULL)
            return racine;
        else
            parcours_arbre(racine->filsG, borneSup);
    }
    else if(racine<borneSup){
        if(racine->filsD==NULL)
            return racine;
        else
            return parcours_abre(racine->filsD, borneSup);
    }
    
}







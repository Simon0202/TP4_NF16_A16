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
//Fin de nouveauBen



ListBenevoles *nouvelleListe(){
    ListBenevoles *newListe = malloc(sizeof(struct ListBenevoles));
    if(newListe==NULL)
        exit(EXIT_FAILURE);
    
    newListe->benevole=NULL;
    newListe->nbreElement=0;
    
    return newListe;
}
//Fin de nouvelleListe



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
//Fin de nouvelleTranche





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





//*******************
//*****Recherche*****
//*******************
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
    
    if(racine->listBenevole->benevole==NULL){
        return NULL;
    }
    else{
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
}
//Fin de benevole d'honneur.





//*********************
//*****Suppression*****
//*********************

//Je considere que l on ne peut pas supprimer la racine
Tranche *supprimerNoeud(Tranche *racine,Tranche *currentTranche){
    
    Tranche *pere = currentTranche->pere;
    Tranche *succ = NULL;
    
    //root
    if(currentTranche == racine)
    {
        if(currentTranche->filsG == NULL && currentTranche->filsD == NULL){
            racine = NULL;
            free(currentTranche->listBenevole);
            free(currentTranche);
            return racine;
        }
        else if(currentTranche->filsG == NULL && currentTranche->filsD != NULL){     //un seul fils doite
            currentTranche->filsD->pere = NULL;
            racine = currentTranche->filsD;
        }
        else if(currentTranche->filsD == NULL && currentTranche->filsG != NULL){     //un seul fils gauche
            currentTranche->filsG->pere = NULL;
            racine = currentTranche->filsG;
        }
        else{   //deux fils
            succ = Successeur(currentTranche);
            succ->filsG = currentTranche->filsG;
            if(currentTranche->filsD != succ)
                succ->filsD = currentTranche->filsD;
            else
                succ->filsD = NULL;
            if(succ == succ->pere->filsG)
                succ->pere->filsG = NULL;
            else
                succ->pere->filsD = NULL;
            succ->pere = NULL;
            racine = succ;
        }
        free(currentTranche->listBenevole);
        free(currentTranche);
        return racine;
    }
    
    //feuille
    if(currentTranche->filsG == NULL && currentTranche->filsD == NULL){
        if (currentTranche == pere->filsG)
            pere->filsG = NULL;
        else
            pere->filsD = NULL;
        free(currentTranche->listBenevole);
        free(currentTranche);
        return racine;
    }
    
    //pas root
    if(currentTranche == pere->filsG){
        if(currentTranche->filsG == NULL && currentTranche->filsD != NULL){     //un seul fils doite
            pere->filsG = currentTranche->filsD;
            currentTranche->filsD->pere = pere;
        }
        else if(currentTranche->filsD == NULL && currentTranche->filsG != NULL){     //un seul fils gauche
            pere->filsG = currentTranche->filsG;
            currentTranche->filsG->pere = pere;
        }
        else{   //deux fils
            succ = Successeur(currentTranche);
            succ->filsG = currentTranche->filsG;
            if(currentTranche->filsD != succ)
                succ->filsD = currentTranche->filsD;
            else
                succ->filsD = NULL;
            if(succ == succ->pere->filsG)
                succ->pere->filsG = NULL;
            else
                succ->pere->filsD = NULL;
            pere->filsG = succ;
            succ->pere = currentTranche->pere;
        }
    }
    if(currentTranche == pere->filsD){
        if(currentTranche->filsG == NULL && currentTranche->filsD != NULL){     //un seul fils doite
            pere->filsD = currentTranche->filsD;
            currentTranche->filsD->pere = pere;
        }
        if(currentTranche->filsD == NULL && currentTranche->filsG != NULL){     //un seul fils gauche
            pere->filsD = currentTranche->filsG;
            currentTranche->filsG->pere = pere;
        }
        else{   //deux fils
            succ = Successeur(currentTranche);
            succ->filsG = currentTranche->filsG;
            if(currentTranche->filsD != succ)
                succ->filsD = currentTranche->filsD;
            else
                succ->filsD = NULL;
            if(succ == succ->pere->filsG)
                succ->pere->filsG = NULL;
            else
                succ->pere->filsD = NULL;
            pere->filsD = succ;
            succ->pere = currentTranche->pere;
        }
    }
    free(currentTranche->listBenevole);
    free(currentTranche);
    return racine;
}
//Fin de supprimer un noeud

int supprimerBen(Tranche *racine, int CIN, int annee){
    Tranche *currentTranche = racine;
    int borneSup = calculTrancheAnnee(annee);
    Benevole *benevoleSupprimer = NULL;
    Benevole *pred = NULL;
    
    while(currentTranche!=NULL && currentTranche->borneSup!=borneSup){
        if(currentTranche->borneSup > borneSup)
            currentTranche = currentTranche->filsG;
        else if(currentTranche->borneSup < borneSup)
            currentTranche= currentTranche->filsD;
    }
    
    if(racine==NULL){
        printf("Il y a aucun arbre.");
        return 0;
    }
    
    benevoleSupprimer = currentTranche->listBenevole->benevole;
    
    while(benevoleSupprimer!=NULL && benevoleSupprimer->carteIdentite!=CIN){
        pred = benevoleSupprimer;
        benevoleSupprimer = benevoleSupprimer->suivant;
    }
    
    if(benevoleSupprimer==NULL){
        printf("Le benevole a supprimer n'existe pas");
        return 0;
    }
    
    if(pred == NULL){
        currentTranche->listBenevole->benevole = NULL;
        free(benevoleSupprimer);
        currentTranche->listBenevole->nbreElement--;
        racine = supprimerNoeud(racine, currentTranche);
        return 1;
    }
    
    pred->suivant = benevoleSupprimer->suivant;
    free(benevoleSupprimer);
    currentTranche->listBenevole->nbreElement--;
    return 1;
}
//Fin de supprimer Benevole

Tranche *suppTousBenevole(Tranche *trancheSupprimer){
    Benevole *premier = trancheSupprimer->listBenevole->benevole;
    while(premier != NULL)
    {
        trancheSupprimer->listBenevole->benevole = premier->suivant;
        free(premier);
        premier = trancheSupprimer->listBenevole->benevole;
    }
    return trancheSupprimer;
}
//Fin de supprimer tous les benevole dans une tranche




int supprimerTranche(Tranche *racine, int borneSup){
    
    Tranche *tranche_a_supprimer = NULL;
    Tranche *pere = NULL;
    Tranche *min = NULL;
    Benevole *benevole_a_supprimer = NULL;
    
    while(racine!=NULL && racine->borneSup!=borneSup){
        if(racine->borneSup > borneSup){
            pere = racine;
            racine=racine->filsG;
        }
        else if(racine->borneSup < borneSup){
            pere = racine;
            racine = racine->filsD;
        }
    }

    if(racine==NULL){
        printf("La tranche n'existe pas\n");
        return 0;
    }

    //Suppression des benevole dans listeBenevole
    while(racine->listBenevole->nbreElement!=0){
        benevole_a_supprimer = racine->listBenevole->benevole;
        
        racine->listBenevole->benevole = racine->listBenevole->benevole->suivant;
        racine->listBenevole->nbreElement--;
        
        benevole_a_supprimer->suivant=NULL;
        free(benevole_a_supprimer->nom);
        free(benevole_a_supprimer->prenom);
        free(benevole_a_supprimer);
        free(racine->listBenevole);
    }
    
    //On est a la racine, on ne peut pas supprimer
    if(pere==NULL){
        printf("Interdiction de supprimer la racine.\nPour ce faire appeler la fonction 12\n");
        return 0;
    }

    
    //**********************
    //On recupere dans un variable identifiable l element a supprimer. la valeur ajoutee est de nulle.
    //**********************
    tranche_a_supprimer = racine;
    
    
    if(tranche_a_supprimer->filsG==NULL){
        if(tranche_a_supprimer->borneSup<=pere->borneSup)
            pere->filsG = tranche_a_supprimer->filsD;
        else
            pere->filsD = tranche_a_supprimer->filsD;
        
        free(tranche_a_supprimer);
        tranche_a_supprimer=NULL;
        return 1;
    }
    
    
    //On est dans le cas ou l element a supprimer possede un fils droit et/ou gauche
    min = ArbreMin(tranche_a_supprimer->filsD);
    
    if(min->filsD!=NULL){
        if(tranche_a_supprimer->borneSup<=pere->borneSup)
            pere->filsG = min->filsD;
        else
            pere->filsD = min->filsD;
        
        min->filsD = tranche_a_supprimer->filsD;
        min->filsG = tranche_a_supprimer->filsG;
    }
    else{
        if(min->borneSup<=pere->borneSup)
            pere->filsG = min;
        else
            pere->filsD = min;
        
        
        if(tranche_a_supprimer->filsD!=min){
            min->filsD = tranche_a_supprimer->filsD;
        }
        
        min->filsG = tranche_a_supprimer->filsG;
    }

    free(tranche_a_supprimer);
    tranche_a_supprimer = NULL;
    return 1;
}
//fin de supprimer Tranche


//*********************
//*****Mise a Jour*****
//*********************

//Quand un bénévole ne fait plus partie d’une certaine tranche d’âge, il devra être déplacé vers la tranche d’âge
//adéquate. Écrire la fonction qui permet d’actualiser l’ABR. Elle renvoie le nombre de personne déplacées.
int actualiser(Tranche *racine){
    int cmptTransfert = 0;
    Benevole *list_a_parcourir = NULL;
    ListBenevoles *listeActualisation = NULL;
    
    ListBenevoles *listAncien = BenDhonneur(racine);
        
    if(listAncien==NULL){
        printf("aucun benevole dans l'arbre");
        return 0;
    }
    else{
        int borneSupMax = calculTrancheAnnee(listAncien->benevole->anneeDeNaissance)+5;
        
        while(racine->borneSup!=borneSupMax-5){
            racine = racine->filsD;
        }
        
        list_a_parcourir = racine->listBenevole->benevole;
        
        while(list_a_parcourir->suivant->anneeDeNaissance!=listAncien->benevole->anneeDeNaissance){
            list_a_parcourir = list_a_parcourir->suivant;
        }
        list_a_parcourir->suivant=NULL;
        
        listeActualisation = ajoutTranche(racine, borneSupMax)->listBenevole;
        
        while(listAncien->benevole!=NULL){
            ajoutBenevole(listeActualisation, listAncien->benevole);
            listAncien->benevole = listAncien->benevole->suivant;
            cmptTransfert++;
    }
    
        return cmptTransfert;
    }
}


//**********************
//*****Statistiques*****
//**********************
int totalBenTranche(Tranche *racine, int borneSup){
    
    Tranche *currentTranche = racine;
    
    if(racine == NULL){
        printf("Pas d'arbre\n");
        return -2;
    }
    while(currentTranche!=NULL && currentTranche->borneSup!=borneSup){
        if(currentTranche->borneSup > borneSup)
            currentTranche = currentTranche->filsG;
        else if(currentTranche->borneSup < borneSup)
            currentTranche= currentTranche->filsD;
    }
    
    if(currentTranche == NULL){
        printf("Pas de tranche\n");
        return -1;
    }
    
    return currentTranche->listBenevole->nbreElement;
}
//Fin de nombre de bénévoles d’une tranche

int totalBen(Tranche *racine){
    
    int total = 0;
    Tranche *currentfTranche = ArbreMin(racine);
    
    if(racine == NULL){
        printf("Pas d'arbre\n");
        return -2;
    }
    while (currentfTranche != NULL) {
        total += currentfTranche->listBenevole->nbreElement;
        currentfTranche = Successeur(currentfTranche);
    }
    
    return total;
}
//Fin de total de bénévoles de l’association

float pourcentageTranche(Tranche *racine, int borneSup){
    
    float totalTranche = (float)totalBenTranche(racine, borneSup);
    float total = (float)totalBen(racine);
    
    if(total == -2){
        printf("Pas d'arbre\n");
        return -2;
    }
    else if(totalTranche == -1){
        printf("Pas de tranche\n");
        return -1;
    }
    else if(total == 0){
        printf("Il n'y a pas de benevole dans l'arbre\n");
        return 0;
    }
    else
        return totalTranche/total*100;
}
//Fin de pourcentage de bénévoles d’une tranche d’âge.




//*******************
//*****Affichage*****
//*******************
void afficherTranche(Tranche *racine, int borneSup){
    Benevole *benevoles = NULL;
    
    
    while(racine!=NULL && racine->borneSup!=borneSup)
        if(racine->borneSup<borneSup)
            racine = racine->filsD;
        else
            racine = racine->filsG;
    
    if(racine==NULL){
        printf("la tranche d age n existe pas");
    }
    else{
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
}
//Fin de afficher tranche



void afficherArbre(Tranche *racine){
    if(racine->filsG!=NULL)
        afficherArbre(racine->filsG);
    printf("%d\t",racine->borneSup);
    if (racine->filsD!=NULL) {
        afficherArbre(racine->filsD);
    }
}
//Fin de ParcoursArbre






//****************
//*****Addeed*****
//****************
int anneeActuelle(){
    time_t secondes;
    struct tm instant; time(&secondes);
    instant = *localtime(&secondes); return instant.tm_year + 1900;
}
//Fin de anneeActuelle


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
//Fin de calculTrancheAnnee



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



Tranche *ArbreMin(Tranche *noeud){
    while(noeud->filsG != NULL)
        noeud = noeud->filsG;
    return noeud;
}
//Fin de arbreMin



Tranche *Successeur(Tranche *noeud){
    Tranche *pere = NULL;
    
    if(noeud->filsD != NULL)
        return ArbreMin(noeud->filsD);
    pere = noeud->pere;
    while(pere != NULL && noeud == pere->filsD){
        noeud = pere;
        pere = noeud->pere;
    }
    return pere;
}
//Fin de successeur



Tranche *retournePere(Tranche *racine, int borneSup){
    Tranche *pere = NULL;
    
    while(racine!=NULL && racine->borneSup!=borneSup){
        if(racine->borneSup<=borneSup){
            pere = racine;
            racine = racine->filsD;
        }
        else{
            pere = racine;
            racine = racine->filsG;
        }
    }
    
    return pere;
}
//Fin de retournerPere

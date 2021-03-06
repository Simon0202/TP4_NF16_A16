/*
Commentaires relatifs au projet:
 
 On ne doit pas pouvoir supprimer la racine depuis une fonction autre que la 12 détruire arbre
*/

#include "tp4.h"

int main() {
    int mise_en_route = 1, quitter=0;;
    int choix=0;
    Tranche *racine = NULL;
    

//    printf("Debut de la phase de test des fonctions.\n");
    
    Benevole *ben1 = nouveauBen("a", "a", 1000, 'F', 1980);
    Benevole *ben2 = nouveauBen("b", "b", 2000, 'M', 1989);
    Benevole *ben3 = nouveauBen("c", "c", 3000, 'M', 1988);
    Benevole *ben4 = nouveauBen("d", "d", 4000, 'F', 1990);
    Benevole *ben5 = nouveauBen("e", "e", 5000, 'M', 1980);
    Benevole *ben6 = nouveauBen("f", "f", 6000, 'M', 1989);
 
    racine = ajoutTranche(racine,40);
    ajoutTranche(racine, 55);
    ajoutTranche(racine, 25);
    ajoutTranche(racine, 40);
    
    insererBen(racine, ben1);
    insererBen(racine, ben2);
    insererBen(racine, ben3);
    insererBen(racine, ben4);
    insererBen(racine, ben5);
    insererBen(racine, ben6);
    
    
    
    /*
    Benevole *ben7 = nouveauBen("Marc", "Eoche", 1, 'M', 1944);
    Benevole *ben8 = nouveauBen("Pierre", "Durand", 2, 'M', 1941);
    Benevole *ben9 = nouveauBen("Fab", "Louise", 3, 'F', 1943);
    Benevole *ben10 = nouveauBen("z", "a", 1, 'M', 1944);
    Benevole *ben11 = nouveauBen("a", "a", 20, 'M', 1941);
     */
    
 
    /*
    ajoutTranche(racine, 65);
    ajoutTranche(racine, 75);
    */
    
    
    /*
    insererBen(racine, ben7);
    insererBen(racine, ben8);
    insererBen(racine, ben9);
    insererBen(racine, ben10);
    insererBen(racine, ben11);
     */
    /*
    printf("Le benevole s'appelle: %s\n", chercherBen(racine, 123, 1995)->prenom);
    printf("Le benevole s'appelle: %s\n", chercherBen(racine, 3, 1943)->prenom);
    
    afficherArbre(racine);
    printf("\n");
    
    
    ListBenevoles *liste = BenDhonneur(racine);
    
    while(liste->benevole!=NULL){
        printf("%s\n",liste->benevole->prenom);
        liste->benevole = liste->benevole->suivant;
    }
    
    
    afficherTranche(racine, 75);
    afficherTranche(racine, 35);
    afficherArbre(racine);
    printf("%d",actualiser(racine));
    printf("\n");
    afficherArbre(racine);
    printf("\n");
    afficherTranche(racine, 80);
    printf("\n");;
    afficherTranche(racine, 75);

 
    //-------------------------
    supprimerBen(racine, 13 , 1942);    //supprimer un benevole
    afficherTranche(racine, 75);
    supprimerBen(racine, 123, 1995);    //supprimer un benevole puis supprimer la tranche
    afficherArbre(racine);
    printf("\n");
    //supprimerTranche(racine, 35);   //j'ai pas reussi parce que le contenu d'arbre n'est pas modifie apres la fonction
    //afficherArbre(racine);
    //printf("\n");
    printf("%.2f%%\n",pourcentageTranche(racine, 35));
    printf("%.2f%%\n",pourcentageTranche(racine, 75));
    //-------------------------
    
    afficherArbre(racine);
    supprimerTranche(racine, 35);
    printf("\n");
    afficherArbre(racine);
 
  printf("\nFin de la phase de test des fonctions.\n");
*/
    
   // printf("prenom : %s\n",chercherBen(racine, 2000, 1989)->prenom);
    
    //**************
    //*****Menu*****
    //**************
    printf("Bonjour, veuillez choisir le numero de l'action à faire\n");
    while(mise_en_route){
        int borneTranche = 0;
        char benevoleNom[35];
        char benevolePrenom[35];
        int benevoleCIN = 0;
        int benevoleNumberSexe = 0;
        char benevoleSexe;
        int benevoleAnneeDeNaissance = 0;
        ListBenevoles *liste_benevoles_honneur = NULL;
        Benevole *benevole_a_supprimer = NULL;
        
        printf("\n");
        printf("Initialisez un arbre - tapez 1\n");
        printf("Ajoutez une tranche - tapez 2\n");
        printf("Ajouter un bénévole dans une tranche d’âge - tapez 3\n");
        printf("Afficher les tranches d’âge d’un ABR - tapez 4\n");
        printf("Afficher les bénévoles d’une tranche d’âge - tapez 5\n");
        printf("Supprimer un bénévole - tapez 6\n");
        printf("Supprimer une tranche - tapez 7\n");
        printf("Afficher les bénévoles d’honneur - tapez 8\n");
        printf("Afficher le nombre total de bénévoles - tapez 9\n");
        printf("Actualiser l’ABR - tapez 10\n");
        printf("Afficher le pourcentage de bénévoles d’une tranche d’âge - tapez 11\n");
        printf("Détruire l’arbre - tapez 12\n");
        printf("Quittez - tapez 13\n");
        printf("Chercher un benevole - tapez 14\n");
        printf("Total benevoles de la tranche - tapez 15\n");
        scanf("%d",&choix);
        if(racine==NULL&&choix==1&&quitter==0){
            printf("Veuillez entrer la valeur de la racine\n");
            scanf("%d",&borneTranche);
            racine = nouvelleTranche(borneTranche);
            printf("\n");
        }
        else if(choix!=1&&racine==NULL&&quitter==0){
            printf("\nVeuillez initialiser l'arbre avec l'action 1\n\n");
        }
        else{
            switch (choix) {
                case 1:
                    printf("\nl'abre est deja initialise\n");
                    break;
                case 2:
                    printf("Veuillez entrer la valeur de la tranche a ajouter\n");
                    scanf("%d",&borneTranche);
                    ajoutTranche(racine, borneTranche);
                    printf("\n");
                    break;
                case 3:
                    printf("Veuillez entrer le nom du benevole\n");
                    scanf("%s",benevoleNom);
                    printf("Veuillez entrer le prenom du benevole\n");
                    scanf("%s",benevolePrenom);
                    printf("Veuillez entrer le CIN du benevole\n");
                    scanf("%d",&benevoleCIN);
                    //On pourrait egalement utiliser la fonction getchar()
                    printf("Veuillez entrer le sexe du benevole (0 pour M, 1 pour F)\n");
                    scanf("%d",&benevoleNumberSexe);
                    if(benevoleNumberSexe==0)
                        benevoleSexe = 'M';
                    else
                        benevoleSexe = 'F';
                    printf("Veuillez entrer l'annee de naissance du benevole\n");
                    scanf("%d",&benevoleAnneeDeNaissance);
                    insererBen(racine, nouveauBen(benevoleNom, benevolePrenom, benevoleCIN, benevoleSexe, benevoleAnneeDeNaissance));
                    printf("\n");
                    break;
                case 4:
                    if(racine!=NULL){
                        afficherArbre(racine);
                        printf("\n");
                    }
                    else{
                        printf("Aucune racine\n");
                    }
                    break;
                case 5:
                    printf("Veuillez choisir la tranche a afficher\n");
                    scanf("%d",&borneTranche);
                    afficherTranche(racine, borneTranche);
                    printf("\n");
                    break;
                case 6:
                    printf("Veuillez entrer le CIN du benevole\n");
                    scanf("%d",&benevoleCIN);
                    printf("Veuillez entrer l'annee de naissance du benevole\n");
                    scanf("%d",&benevoleAnneeDeNaissance);
                    supprimerBen(racine, benevoleCIN, benevoleAnneeDeNaissance);
                    printf("\n");
                    break;
                case 7:
                    printf("Veuillez choisir la tranche a supprimer\n");
                    scanf("%d",&borneTranche);
                    supprimerTranche(racine, borneTranche);
                    printf("\n");
                    break;
                case 8:
                        liste_benevoles_honneur = BenDhonneur(racine);
                    if(liste_benevoles_honneur==NULL){
                        rintf("Aucun benevole d'honneur\n");
                    }
                    else{
                        while(liste_benevoles_honneur!=NULL && liste_benevoles_honneur->benevole!=NULL){
                            printf("%s\n",liste_benevoles_honneur->benevole->prenom);
                            liste_benevoles_honneur->benevole = liste_benevoles_honneur->benevole->suivant;
                        }
                        
                    }t
                    printf("\n");
                    break;
                case 9:
                    printf("%d",totalBen(racine));
                    printf("\n");
                    break;
                case 10:
                    printf("Il y a eu %d actualisation(s):",actualiser(racine));
                    printf("\n");
                    break;
                case 11:
                    printf("Veuillez choisir la tranche pour laquelle afficher le pourcentage\n");
                    scanf("%d",&borneTranche);
                    printf("Pourcentage: %f\n",pourcentageTranche(racine, borneTranche));
                    printf("\n");
                    break;
                case 12:
                    //On vide le sous arbre droit
                    while(racine->filsD!=NULL){
                        supprimerTranche(racine, racine->filsD->borneSup);
                    }
                    //On vide le sous arbre gauche
                    while(racine->filsG!=NULL){
                        supprimerTranche(racine, racine->filsG->borneSup);
                    }
                    //On vide la liste des benevoles
                    while(racine->listBenevole->nbreElement!=0){
                        benevole_a_supprimer = racine->listBenevole->benevole;
                        
                        racine->listBenevole->benevole = racine->listBenevole->benevole->suivant;
                        racine->listBenevole->nbreElement--;
                        
                        benevole_a_supprimer->suivant=NULL;
                        free(benevole_a_supprimer->nom);
                        free(benevole_a_supprimer->prenom);
                        free(benevole_a_supprimer);
                    }
                    //on libere la memoire
                    free(racine->listBenevole);
                    free(racine);
                    racine = NULL;
                    quitter = 1;
                    printf("\n");
                    break;
                case 13:
                    if(racine!=NULL){
                        printf("Veuillez detruire l arbre avant\n");
                    }
                    else{
                        printf("\n");
                        mise_en_route = 0;
                    }
                    break;
                case 14:
                    printf("Veuillez entrer le CIN\n");
                    scanf("%d",&benevoleCIN);
                    printf("Veuillez entrer l'annee\n");
                    scanf("%d",&benevoleAnneeDeNaissance);
                    benevole_a_supprimer = chercherBen(racine, benevoleCIN, benevoleAnneeDeNaissance);
                    if(benevole_a_supprimer!=NULL){
                        printf("Prenom : %s \n",benevole_a_supprimer->prenom);
                        printf("Nom : %s \n",benevole_a_supprimer->nom);
                    }
                    else
                        printf("aucun benevole\n");
                    break;
                case 15:
                    printf("Veuillez entrer la tranche:\n");
                    scanf("%d",&benevoleAnneeDeNaissance);
                    printf("Total Benevoles de la tranche: %d\n",totalBenTranche(racine, benevoleAnneeDeNaissance));
                    break;
                default:
                    printf("\ntVeuillez saisir une valeur valide\n");
                    break;
            }
        }
    }
    
            return 0;
}

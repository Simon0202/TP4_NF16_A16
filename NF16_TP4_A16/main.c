/*
Commentaires relatifs au projet:
 
 
*/

#include "tp4.h"

int main() {
    
    printf("Debut de la phase de test des fonctions.\n");
    
    Benevole *ben1 = nouveauBen("John", "Mears", 123, 'M', 1995);
    Benevole *ben2 = nouveauBen("Rose", "Mary", 12, 'F', 1963);
    Benevole *ben3 = nouveauBen("Julie", "Moo", 73, 'F', 2010);
    Benevole *ben4 = nouveauBen("Benoit", "Dalaglio", 99, 'M', 2000);
    Benevole *ben5 = nouveauBen("Jean", "Pierre", 13, 'M', 1942);
    Benevole *ben6 = nouveauBen("Marie", "Paul", 15, 'F', 1943);
    Benevole *ben7 = nouveauBen("Marc", "Eoche", 1, 'M', 1944);
    Benevole *ben8 = nouveauBen("Pierre", "Durand", 2, 'M', 1941);
    Benevole *ben9 = nouveauBen("Fab", "Louise", 3, 'F', 1943);
    Benevole *ben10 = nouveauBen("z", "a", 1, 'M', 1944);
    Benevole *ben11 = nouveauBen("a", "a", 20, 'M', 1941);

    
    
    Tranche *racine = ajoutTranche(NULL,35);
    ajoutTranche(racine, 25);
    ajoutTranche(racine, 55);
    ajoutTranche(racine, 45);
    ajoutTranche(racine, 65);
    ajoutTranche(racine, 75);
    
    insererBen(racine, ben1);
    insererBen(racine, ben2);
    insererBen(racine, ben3);
    insererBen(racine, ben4);
    insererBen(racine, ben5);
    insererBen(racine, ben6);
    insererBen(racine, ben7);
    insererBen(racine, ben8);
    insererBen(racine, ben9);
    insererBen(racine, ben10);
    insererBen(racine, ben11);

    
    printf("Le benevole s'appelle: %s\n", chercherBen(racine, 123, 1995)->prenom);
    printf("Le benevole s'appelle: %s\n", chercherBen(racine, 3, 1943)->prenom);
    
    ParcoursArbre(racine);
    printf("\n");
    
    
    ListBenevoles *liste = BenDhonneur(racine);
    
    while(liste->benevole!=NULL){
        printf("%s\n",liste->benevole->prenom);
        liste->benevole = liste->benevole->suivant;
    }
    
    afficherTranche(racine, 75);
    afficherTranche(racine, 35);
    
    printf("Fin de la phase de test des fonctions.\n");

    
    //**************
    //*****Menu*****
    //**************
    
    
    
    return 0;
}

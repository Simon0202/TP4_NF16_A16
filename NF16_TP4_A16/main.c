#include "tp4.h"

int main() {
    Benevole *ben1 = nouveauBen("John", "Mears", 123, 'M', 1995);
    Benevole *ben2 = nouveauBen("Rose", "Mary", 12, 'F', 1963);
    Benevole *ben3 = nouveauBen("Julie", "Moo", 73, 'F', 2010);
    Benevole *ben4 = nouveauBen("Benoit", "Dalaglio", 99, 'M', 2000);
    
    
    Tranche *racine = NULL;
    ajoutTranche(racine,35);
    ajoutTranche(racine, 25);
    ajoutTranche(racine, 55);
    ajoutTranche(racine, 45);
    ajoutTranche(racine, 65);
    ajoutTranche(racine, 75);
    
    ParcoursArbre(racine);
    
    return 0;
}

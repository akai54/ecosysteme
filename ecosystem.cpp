/*
https://defelice.up8.site/poofichiers/projetEco.pdf
-----------
  Idée(s)
-----------

Si case vide (si ' '), le personnage se déplace sans rien faire
Si case non vide et animaux hostile(si 'L', 'M', 'l', 'm', '')

tableau qui contient la position de tous les animaux

fonction qui analyse ce qu'il y a autour de l'animal sur une case (comme les
déplacement d'un roi au échec)

deplacement aléatoire puis deplacement intelligent

*/

#include "class.h"

// variables globales
vector<Loup> tableauLoup;
vector<Mouton> tableauMouton;

void Init() {
  int cbLoup = 0;
  int cbMouton = 0;

  cout << "Combien de loup : ";
  cin >> cbLoup;

  cout << "Combien de Mouton : ";
  cin >> cbMouton;

  // Initialisation du tableauPionsMap à -1 pour signifier qu'il n'y a rien dans
  // chacune des cases.
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      tableauPionsMap[i][j] = Vide;
    }
  }

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 7; j++) {
      tableauPionsGenerale[i][j] = Vide;
    }
  }

  int x, y;
  // Initialisation du nombre de loup dans tableau Loup
  // Le constructeur est appelé automatiquement
  for (int i = 0; i < cbLoup; i++) {
    x = rand() % 7;
    y = rand() % 7;
    trouverCaseVide(x, y);
    Loup loup;
    int sexePionsId =
        loup.sexeAnimaux() + 3; // sexeAnimaux revoit 0 = mâle; 1 = femelle
    tableauPionsMap[x][y] = sexePionsId;
    tableauPionsGenerale[x][y] = L;
    loup.position(x, y, 'L');
    tableauPionsMap[x][y] = sexePionsId;
    tableauLoup.push_back(loup); // Mettre loup dans le vector tabLoup
  }

  // Initialisation du nombre de loup dans tableau Mouton
  // Le constructeur est appelé automatiquement
  for (int i = 0; i < cbMouton; i++) {
    x = rand() % 7;
    y = rand() % 7;
    trouverCaseVide(x, y);
    Mouton mouton;
    int sexePionsId =
        mouton.sexeAnimaux(); // sexeAnimaux revoit 0 = mâle; 1 = femelle
    tableauPionsMap[x][y] = sexePionsId;
    tableauPionsGenerale[x][y] = M;
    mouton.position(x, y, 'M');
    tableauPionsMap[x][y] = sexePionsId;
    tableauMouton.push_back(mouton); // Mettre mouton dans le vector tabMouton
  }
}

int main(void) {
  srand(time(NULL));

  Init();
  map.affiche();

  /*
   vector<Loup>::iterator i;
   for(i=tab.begin(); i!=tab.end(); i++){
    i->deplacement(rand()%7,rand()%7,'L');
   }
  */
  // map.affiche();

  // delete tabLoup;

  return 0;
}

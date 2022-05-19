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
vector<SelMineraux> tabSelMineraux;


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

  int x = rand() % 7, y = rand() % 7;
  // Initialisation du nombre de loup dans tableau Loup
  // Le constructeur est appelé automatiquement
  for (int i = 0; i < cbLoup; i++) {
    while(tableauPionsMap[x][y]!=Vide){
      x = rand() % 7;
      y = rand() % 7;
    }
    Loup loup;
    int sexePionsId = loup.sexeAnimaux() + 3; // sexeAnimaux revoit 0 = mâle; 1 = femelle
    loup.position(y, x, 'L');
    tableauPionsMap[y][x] = sexePionsId;
    tableauLoup.push_back(loup); // Mettre loup dans le vector tabLoup
  }

  // Initialisation du nombre de loup dans tableau Mouton
  // Le constructeur est appelé automatiquement
  for (int i = 0; i < cbMouton; i++) {
    while(tableauPionsMap[x][y]!=Vide){
      x = rand() % 7;
      y = rand() % 7;
    }
    Mouton mouton;
    int sexePionsId = mouton.sexeAnimaux(); // sexeAnimaux revoit 0 = mâle; 1 = femelle
    mouton.position(y, x, 'M');
    tableauPionsMap[y][x] = sexePionsId;
    tableauMouton.push_back(mouton); // Mettre mouton dans le vector tabMouton
  }


  for(int i = 0; i < 3; i++){
    while(!estUneCaseVide(x,y)){
      x = rand() % 7;
      y = rand() % 7;
    }
    map.position(x,y,'H');
    tableauPionsMap[x][y] = Herbe;
  }

  map.affiche();
}


void Jouer(){
  int comptTour = 0;
  int comptNbLoup = tableauLoup.size();
  int comptNbMouton = tableauMouton.size();

  //int comptNbMouton = tableauMouton.size();
  //&& comptNbMouton > 0
  while(comptNbLoup < 0 && comptNbMouton < 0){
    for(auto i = tableauLoup.begin(); i!=tableauLoup.end(); i++){
      if(comptNbLoup <=0)
        break;
      i->jouer();
      if(i->mortPossible()){
        cout << "Mort"<< endl;
        tableauLoup.erase(i);
        comptNbLoup = tableauLoup.size();
        //cout << "Nb Loup : "<< comptNbLoup << endl;
      }
      else if(i->BoolreproductionPossible()){
        //cout << "Reproduction"<< endl;
        int Xobj = i->getXObjet();
        int Yobj = i->getYObjet();
        Loup loup;
        int sexePionsId = loup.sexeAnimaux() + 3; // sexeAnimaux revoit 0 = mâle; 1 = femelle
        loup.position(Xobj, Yobj, 'L');
        tableauPionsMap[Xobj][Yobj] = sexePionsId;
        tableauLoup.push_back(loup);
      }
      else if(i->mangerPossible()){
        //cout << "Manger let's go"<< endl;
        int Xobj = i->getXObjet();
        int Yobj = i->getYObjet();
        for(auto j=tableauMouton.begin(); j!=tableauMouton.end(); j++){
          if(j->getY() == Xobj && i->getX() == Yobj){
            tableauMouton.erase(j);
          }
        }
      }
      else{
        //cout << "Test"<< endl;
        continue;
      }
    }//Fin boucle For


    for(auto j = tableauMouton.begin(); j != tableauMouton.end(); j++){
          if(comptNbMouton <=0)
            break;
          j->jouer();
          if(j->mortPossible()){
            //cout << "Mort"<< endl;
            tableauMouton.erase(j);
            comptNbLoup = tableauLoup.size();
            //cout << "Nb Loup : "<< comptNbLoup << endl;
          }
          else if(j->BoolreproductionPossible()){
            //cout << "Reproduction"<< endl;
            int Xobj = j->getXObjet();
            int Yobj = j->getYObjet();
            Mouton m;
            int sexePionsId = m.sexeAnimaux(); // sexeAnimaux revoit 0 = mâle; 1 = femelle
            m.position(Xobj, Yobj, 'M');
            tableauPionsMap[Xobj][Yobj] = sexePionsId;
            tableauMouton.push_back(m);
          }
          else{
            //cout << "Test"<< endl;
            continue;
          }

    }

    map.affiche();
    comptTour++;
    cout << "nb Tour : " << comptTour << endl;
    comptNbLoup = tableauLoup.size();
    comptNbMouton = tableauMouton.size();

  }// Fin While

  int test = rand()%20;
  while(comptNbLoup > 0 && comptNbMouton > 0){
    comptNbLoup = tableauLoup.size();
    comptNbMouton = tableauMouton.size();
    for(auto i = tableauLoup.begin(); i != tableauLoup.end(); i++){
      test = rand()%20;
      if(test == 1){
        tableauLoup.erase(i);
        //map.position(x,y,' ');
        break;
      }
      else{
        i->plus_proche(M,1);
        int xob = i->getXObjet();
        int yob = i->getYObjet();
        int x = i->getX();
        int y = i->getY();
        i->deplacementVersObjet(xob - x, yob - y);
      }

    }
    for(auto j = tableauMouton.begin(); j != tableauMouton.end(); j++){
      test = rand()%20;
      if(test == 1){
        tableauMouton.erase(j);
        //map.position(y,x,' ');
        break;
      }
      else{
        j->plus_proche(Herbe,0);
        int xob = j->getXObjet();
        int yob = j->getYObjet();
        int x = j->getX();
        int y = j->getY();
        j->deplacementVersObjet(xob - x, yob - y);
      }
    }
    map.affiche();
    comptTour++;
    cout << "nb Tour : " << comptTour << endl;
  }


  cout << "Fin" << endl;

}


void test(){
  int comptTour = 0;
  int x = 0;
  int y = 0;
  int Xobj = 0, Yobj = 0;
  for(auto i = tableauLoup.begin(); i != tableauLoup.end(); i++){
    i->plus_proche(M,1);
    x = i->getX();
    y = i->getY();
    cout << "x : " << x << ", y  : " << y << endl;
    Xobj = i->getXObjet();
    Yobj = i->getYObjet();
    if(x!=Xobj && y!=Yobj){
      i->deplacementVersObjet(Xobj, Yobj);
    }
  }
  map.affiche();

}


int main(void) {
  srand(time(NULL));
  Init();
  Jouer();
  //test();
  return 0;
}

#include <iterator>
#include <string>
#include <time.h>
#include <vector>

#include "map.h"

using namespace std;

// Prototype
void AutourCase(int tabDirection[], int taille);
int stockageCoordonneTab(int tab[], int ID, int compt);


// Variable Globale
Map map;

enum ObjetMap {
  Mouton_Male,
  Mouton_Femelle,
  Mouton_BB,
  Loup_Male,
  Loup_Femelle,
  Loup_BB,
  Sel_Mineraux,
  Herbe,
  Vide,
  M, // Moutons en général (sans distinction de sexe)
  L, // Loup en général (sans distinction de sexe)
};

int tableauPionsMap[7]
                   [7]; // Tableau pour savoir les coordonnées de chaque pions

int tableauPionsGenerale[7][7];

int tabcaseAutour[8] = {Vide, Vide, Vide, Vide, Vide, Vide, Vide, Vide};

class Pions {
protected:
  char nom;
  int x = 0, y = 0;
};

class Animaux : public Pions {
protected:
  int nbTourMaxSansManger;   // nb tour max sans manger
  int nbTourMaxSurLeTerrain; // Nb de tour qu'il est sur le terrain
  int sexe;                  // 0 = mâle; 1 = femelle
  int comptJourSansManger = 0;
  int comptJour = 0;
  int sexeIdPions = 0;

  int testX = 0;
  int testY = 0;

public:
  Animaux() {
    sexe = rand() % 2; // 0 = mâle; 1 = femelle
  }

  ~Animaux(){};

  int sexeAnimaux() { return sexe; }

  void jouer() {
    if (comptJourSansManger == nbTourMaxSansManger ||
        comptJour == nbTourMaxSurLeTerrain)
      mortNaturel();

    comptJour++;
    comptJourSansManger++;
    cout << comptJour << endl;
  }

  void position(int newX, int newY, char nom) {
    map.position(x, y, ' ');
    tableauPionsMap[x][y] = Vide;
    x = newX;
    y = newY;
    map.position(x, y, nom);
    tableauPionsMap[x][y] = nom;
    testX = x;
    testY = y;
  }

  void reproduction();

  void mortNaturel() { map.position(x, y, 'S'); }

  void mort() { map.position(x, y, ' '); }

  // int
  // tabDeplacementPossibe[16]={x+1,y,x+1,y+1,x,y+1,x-1,y+1,x-1,y,x-1,y-1,x,y-1,x+1,y-1};
  // // Faire indice+2 pour obtenir la direction voulue (que des multiples de
  // 2)(droite puis sens des aiguilles d'une montre)

  void Autour() {
    if (x == 0) {
      if (y == 0) {
        int tabDirectionPossible[] = {x + 1, y, x + 1, y + 1, x, y + 1};
        AutourCase(tabDirectionPossible, 6);
      } else if (y == 7) {
        int tabDirectionPossible[] = {x, y - 1, x + 1, y - 1, x + 1, y};
        AutourCase(tabDirectionPossible, 6);
      } else {
        int tabDirectionPossible[] = {
            x, y - 1, x + 1, y - 1, x + 1,
            y, x + 1, y + 1, x,     y + 1}; // Si y entre 1 et 6
        AutourCase(tabDirectionPossible, 10);
      }
    } else if (x == 7) {
      if (y == 0) {
        int tabDirectionPossible[] = {x, y + 1, x - 1, y + 1, x - 1, y};
        AutourCase(tabDirectionPossible, 6);

      } else if (y == 7) {
        int tabDirectionPossible[] = {x - 1, y, x - 1, y - 1, x, y - 1};
        AutourCase(tabDirectionPossible, 6);

      } else {
        int tabDirectionPossible[] = {
            x, y + 1, x - 1, y + 1, x - 1,
            y, x - 1, y - 1, x,     y - 1}; // Si y entre 1 et 6
        AutourCase(tabDirectionPossible, 10);
      }
    } else {
      if (y == 0) {
        int tabDirectionPossible[] = {x + 1, y,     x + 1, y + 1, x,
                                      y + 1, x - 1, y + 1, x - 1, y};
        AutourCase(tabDirectionPossible, 10);
      } else if (y == 7) {
        int tabDirectionPossible[] = {x + 1, y,     x + 1, y - 1, x,
                                      y - 1, x - 1, y - 1, x - 1, y};
        AutourCase(tabDirectionPossible, 10);
      } else {
        int tabDirectionPossible[16] = {x + 1, y,     x + 1, y + 1, x,
                                        y + 1, x - 1, y + 1, x - 1, y,
                                        x - 1, y - 1, x,     y - 1, x + 1,
                                        y - 1}; // Si le pions n'est pas proche
                                                // d'une bordure
        AutourCase(tabDirectionPossible, 16);
      }
    }
  }

  //Fait également les diagonales
  void deplacementVersObjet(int XObjet, int YObjet) {
    int xCbDeDeplacement = 0;
    int yCbDeDeplacement = 0;

    xCbDeDeplacement = XObjet - x;
    yCbDeDeplacement = YObjet - y;

    if (xCbDeDeplacement > 0)
      xCbDeDeplacement = 1;
    else if (xCbDeDeplacement < 0)
      xCbDeDeplacement = -1;

    if (yCbDeDeplacement > 0)
      yCbDeDeplacement = 1;
    else if (yCbDeDeplacement < 0)
      yCbDeDeplacement = -1;

    position(x + xCbDeDeplacement, y + yCbDeDeplacement, nom);
  }








 int ComptNbPAS(int XObjet, int YObjet, int compt) {
    int xCbDeDeplacement = 0;
    int yCbDeDeplacement = 0;

    cout << "testX = " << testX << endl;
    cout << "testY = " << testY << endl;


    xCbDeDeplacement = XObjet - testX;
    yCbDeDeplacement = YObjet - testY;

    if (xCbDeDeplacement > 0){
      //xCbDeDeplacement = 1;
      testX++;
    }
    else if (xCbDeDeplacement < 0){
      //xCbDeDeplacement = -1;
      testX--;
    }

    if (yCbDeDeplacement > 0){
      //yCbDeDeplacement = 1;
      testY++;
    }
    else if (yCbDeDeplacement < 0){
      //yCbDeDeplacement = -1;
      testY--;
    }

    if(testX == XObjet && testY == YObjet){
      cout << "---------" << endl;
      cout << "compt = " << compt << endl;
      cout << "---------" << endl;

      return compt;
    }
    else{
      return ComptNbPAS(XObjet, YObjet, compt+1);
    }
  }






  int XcalculNbPas(int XObjet){
    int xCbDeDeplacement = 0;
    xCbDeDeplacement = XObjet - x;
    return xCbDeDeplacement;
  }

  int YcalculNbPas(int YObjet){
    int yCbDeDeplacement = 0;
    yCbDeDeplacement = YObjet - y;
    return yCbDeDeplacement;
  }

  void transformationTabNbCase(int tab[]){
    for(int i = 0; tab[i]!=Vide; i+=2){
      tab[i] = XcalculNbPas(tab[i]);
      tab[i+1] = YcalculNbPas(tab[i+1]);
    }
  }

  // La variable idObjet correspond à une variable de l'énumération ObjetMap
  // La variable precision permet de savoir si on recherche un type particulier ou toute l'espece
  // Par exemple si precision == 0, on recherchera que les loups mâles (par exemple)
  // si precision == 1, on recherchera tout les loups (même les loups femelles et les loups BB)
  void plus_proche(int idObjet, int precision) {
    int tab[100];
    int tabCompt[100];

    for(int i = 0; i < 100; i++){
      tab[i] = Vide;
      tabCompt[i] = 200;
    }
    int MinX = 50;
    int MinY = 50;
    int compt = 0;
    int MinCompt = 100;
    if(precision == 1){ // Si on recherche une famille d'objet en général (par exemple tous les Loups ou les Moutons)
      if(idObjet < 3 || idObjet == M){ // Si Mouton en Général
        compt = stockageCoordonneTab(tab, Mouton_Femelle, 0);
        compt = stockageCoordonneTab(tab, Mouton_Male, compt);
        compt = stockageCoordonneTab(tab, Mouton_BB, compt);
        //transformationTabNbCase(tab);
        cout << "Recherche Mouton" << endl;
        for(int i = 0; tab[i] != Vide; i++){
          cout << tab[i];
        }
        cout << endl;

        int comptTest = 0;
        for(int i = 0; tab[i] != Vide; i+=2){
          testX = y;
          testY = x;
          tabCompt[comptTest] = ComptNbPAS(tab[i], tab[i+1], 1);
          comptTest++;
        }

        cout << "tableauCompt : ";
        for(int i = 0; tabCompt[i] != 200; i++){
          cout << tabCompt[i];
          cout << " ";
        }
        cout << endl;

        MinCompt = tabCompt[0];
        int position = 0;
        for(int i = 0; tabCompt[i] != 200; i++){
          if(tabCompt[i] < MinCompt){
            MinCompt = tabCompt[i];
            position = i;
          }
        }

        MinX = tab[position*2];
        MinY = tab[position*2+1];

        cout << "position : " << position << endl;
        cout << "Min Compt = " << MinCompt << endl;
        cout << "X = " << MinX << endl;
        cout << "Y = " << MinY << endl;
      }
      else if(idObjet < 6 || idObjet == L){ // Si Loup en Général
        compt = stockageCoordonneTab(tab, Loup_Femelle, 0);
        compt = stockageCoordonneTab(tab, Loup_Male, compt);
        compt = stockageCoordonneTab(tab, Loup_BB, compt);
        transformationTabNbCase(tab);
        for(int i = 0; tab[i] != Vide; i+=2){
          if(tab[i] <= MinX){
            if(tab[i+1] <= MinY){
              MinX = tab[i];
              MinY = tab[i+1];
            }
          }
        }
        cout << "X = " << MinX << endl;
    cout << "Y = " << MinY << endl;
      }
      else if(idObjet == 7){ // Si Herbe
        compt = stockageCoordonneTab(tab, Herbe, 0);
        transformationTabNbCase(tab);
        for(int i = 0; tab[i] != Vide; i+=2){
          if(tab[i] <= MinX){
            if(tab[i+1] <= MinY){
              MinX = tab[i];
              MinY = tab[i+1];
            }
          }
        }
        cout << "X = " << MinX << endl;
    cout << "Y = " << MinY << endl;
      }
      else{ // Si Sel Minéraux
        stockageCoordonneTab(tab, Sel_Mineraux, 0);
        transformationTabNbCase(tab);
        for(int i = 0; tab[i] != Vide; i+=2){
          if(tab[i] <= MinX){
            if(tab[i+1] <= MinY){
              MinX = tab[i];
              MinY = tab[i+1];
            }
          }
        }
        cout << "X = " << MinX << endl;
    cout << "Y = " << MinY << endl;
      }
    }
    else{ // Si on recherche un objet en particulier
      stockageCoordonneTab(tab,idObjet, 0);
      transformationTabNbCase(tab);
      for(int i = 0; tab[i] != Vide; i+=2){
          if(tab[i] <= MinX){
            if(tab[i+1] <= MinY){
              MinX = tab[i];
              MinY = tab[i+1];
            }
          }
        }
        cout << "X = " << MinX << endl;
    cout << "Y = " << MinY << endl;
    }
  }


};

//Cette fonction marche ( :) )
int stockageCoordonneTab(int tab[], int ID, int compt){
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 7; j++){
      if(tableauPionsMap[i][j] == ID){
        tab[compt] = j; //coordonnée X
        tab[compt+1] = i; //coordonnée Y
        compt+=2;
      }
    }
  }
  return compt;
}





class Loup : public Animaux {

public:
  Loup() {
    nom = 'L';
    nbTourMaxSurLeTerrain = 60;
    nbTourMaxSansManger = 10;

  }

  ~Loup(){};

  void attaquerMoutons();
};

class Mouton : public Animaux {

public:
  Mouton() {
    nom = 'M';
    nbTourMaxSurLeTerrain = 50;
    nbTourMaxSansManger = 5; // Meur qu'au 6eme jours
  }

  ~Mouton(){};

  void mangerHerbe();
};

// Permet de mettre toute les valeurs de
inline void initialiserTabCaseAutour(int tab[]) {
  for (int i = 0; i < 8; i++) {
    tab[i] = Vide;
  }
}

inline void afficherTabInt(int tab[]) {
  cout << "tab [ ";
  for (int i = 0; i < 8; i++) {
    cout << tab[i];
    if (i < 7)
      cout << ", ";
  }
  cout << " ]" << endl;
}

inline void AutourCase(int tabDirection[], int taille) {
  initialiserTabCaseAutour(tabcaseAutour);
  int compt = 0;
  int x = 0, y = 0;
  for (int i = 0; i < taille; i += 2) {
    x = tabDirection[i];
    y = tabDirection[i + 1];
    tabcaseAutour[compt] = tableauPionsMap[x][y];
    compt++;
  }

  // afficherTabInt(tabcaseAutour);
}

inline bool estUneCaseVide(int x, int y) {
  if (tableauPionsMap[x][y] == Vide)
    return true;
  return false;
}

inline void trouverCaseVide(int &x, int &y) {
  if (!estUneCaseVide(x, y)) {
    x = rand() % 7;
    y = rand() % 7;
    trouverCaseVide(x, y);
  }
}

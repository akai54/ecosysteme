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
  int nbTourMaxSurLeTerrain; // Nb de tour qu'il est sur le terrain
};

class Animaux : public Pions {
protected:
  int nbTourMaxSansManger;   // nb tour max sans manger
  int sexe;                  // 0 = mâle; 1 = femelle
  int comptJourSansManger = 0;
  int comptJour = 0;
  int sexeIdPions = 0; // Détermine L'identité de l'objet dans l'énumération Objet

  int testX = 0;
  int testY = 0;

  int Xobj = 100; // Coordonnée X de l'objet le plus proche
  int Yobj = 100; // Coordonnée Y de l'objet le plus proche


public:
  Animaux() {
    sexe = rand() % 2; // 0 = mâle; 1 = femelle
  }

  ~Animaux(){};

  int sexeAnimaux() { return sexe; }

  void virtual jouer() = 0;

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

    if(testX == XObjet && testY == YObjet)
      return compt;
    else
      return ComptNbPAS(XObjet, YObjet, compt+1);
  }


  //Cette fonction permet de trouver soit un type d'Objet précis (Loup_Male, Herbe, ...) ou de trouver tous les Objets d'un même type (tous les loups, tous les moutons)
  //Si précision == 1 (recherche tous les Objets de même types (par exemple tous les moutons))
  //Si précision == 0 (recherche un Objet précis (Loup_Femelle, Mouton_BB))
  void DLCplusProche(int ID, int precision){
    int tab[100];
    int tabCompt[100];
    for(int i = 0; i < 100; i++){
      tab[i] = Vide;
      tabCompt[i] = 200;
    }
    int compt = 0;
    int MinCompt = 100;

    if(precision == 1){
      if(ID < 3 || ID == M){
        cout << "OK" << endl;
        compt = stockageCoordonneTab(tab, Mouton_Femelle, 0);
        compt = stockageCoordonneTab(tab, Mouton_Male, compt);
        compt = stockageCoordonneTab(tab, Mouton_BB, compt);
      }
      else if(ID < 6 || ID == L){
        compt = stockageCoordonneTab(tab, Loup_Femelle, 0);
        compt = stockageCoordonneTab(tab, Loup_Male, compt);
        compt = stockageCoordonneTab(tab, Loup_BB, compt);
      }
      else if(ID == Herbe)
        compt = stockageCoordonneTab(tab, Herbe, 0);
      else
        compt = stockageCoordonneTab(tab, Sel_Mineraux, 0);
    }
    else
      compt = stockageCoordonneTab(tab, ID, 0);

    int comptTest = 0;
        for(int i = 0; tab[i] != Vide; i+=2){
          testX = y;
          testY = x;
          tabCompt[comptTest] = ComptNbPAS(tab[i], tab[i+1], 1);
          comptTest++;
        }

        cout << "tabCompt : ";
        for(int i = 0; tabCompt[i] != 200; i++){
          cout << tab[i] << " ";
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

        Xobj = tab[position*2];
        Yobj = tab[position*2+1];

        cout << "X = " << Xobj << endl;
        cout << "Y = " << Yobj << endl;
  }


  // La variable idObjet correspond à une variable de l'énumération ObjetMap
  // La variable precision permet de savoir si on recherche un type particulier ou toute l'espece
  // Par exemple si precision == 0, on recherchera que les loups mâles (par exemple)
  // si precision == 1, on recherchera tout les loups (même les loups femelles et les loups BB)
  void plus_proche(int idObjet, int precision) {
    DLCplusProche(idObjet, precision);
  }


};


class Loup : public Animaux {

public:
  Loup() {
    nom = 'L';
    nbTourMaxSurLeTerrain = 60;
    nbTourMaxSansManger = 10;
    sexeIdPions = sexe + 3;
  }

  ~Loup(){};

  void jouer() {
    if (comptJourSansManger == nbTourMaxSansManger ||
        comptJour == nbTourMaxSurLeTerrain){
      mortNaturel();
    }

    else{
      if(comptJour >= nbTourMaxSurLeTerrain){
        int rechercheId = 0;
        if(sexeIdPions == 3)
          rechercheId = 4;
        else
          rechercheId = 3;
        plus_proche(rechercheId, 0);
        deplacementVersObjet(Xobj, Yobj);
      }

      // Si il a faim
      if(comptJourSansManger == nbTourMaxSansManger/2){
        plus_proche(M, 1);
        deplacementVersObjet(Xobj, Yobj);
      }

      comptJour++;
      comptJourSansManger++;
      cout << comptJour << endl;
    }
  }




  void attaquerMoutons();
};




class Mouton : public Animaux {

public:
  Mouton() {
    nom = 'M';
    nbTourMaxSurLeTerrain = 50;
    nbTourMaxSansManger = 5; // Meur qu'au 6eme jours
    sexeIdPions = sexe;
  }

  ~Mouton(){};



  void jouer() {
    if (comptJourSansManger == nbTourMaxSansManger ||
        comptJour == nbTourMaxSurLeTerrain){
      mortNaturel();
    }

    else{
      if(comptJour >= nbTourMaxSurLeTerrain){
        int rechercheId = 0;
        if(sexeIdPions == 0)
          rechercheId = 1;
        else
          rechercheId = 0;
        plus_proche(rechercheId, 0);
        deplacementVersObjet(Xobj, Yobj);
      }

      // Si il a faim
      if(comptJourSansManger == nbTourMaxSansManger/2){
        plus_proche(M, 1);
        deplacementVersObjet(Xobj, Yobj);
      }

      comptJour++;
      comptJourSansManger++;
      cout << comptJour << endl;
    }
  }



  void mangerHerbe();
};




class SelMineraux : public Pions{
  private :
  int nbTour = 0;

  public :
  SelMineraux(){};
};






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

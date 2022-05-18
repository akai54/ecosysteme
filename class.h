#include <iterator>
#include <string>
#include <time.h>
#include <vector>

#include "map.h"

using namespace std;

// Prototype
void AutourCase(int tabDirection[], int taille);
int stockageCoordonneTab(int tab[], int ID, int compt);
bool estAutourCase(int x, int y);

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

int tableauPionsMap[7][7]; // Tableau pour savoir les coordonnées de chaque pions
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
  int sexeIdPionsOppose = 0; // Détermine L'identité de l'objet de sexe opposé dans l'énumération Objet


  int testX = 0;
  int testY = 0;

  int Xobj = 100; // Coordonnée X de l'objet le plus proche
  int Yobj = 100; // Coordonnée Y de l'objet le plus proche
  bool Boolmort = false;
  bool Boolreproduction = false;
  bool BoolManger = false;

  bool tailleSuperieur = false;

public:

  Animaux() {
    sexe = rand() % 2; // 0 = mâle; 1 = femelle
  }

  ~Animaux(){};

  int sexeAnimaux() { return sexe; }

  //void virtual jouer() = 0;


  bool BoolreproductionPossible(){
    return Boolreproduction;
  }

  bool mortPossible(){
    return Boolmort;
  }

  bool mangerPossible(){return BoolManger;}

  int getX(){return x;}
  int getY(){return y;}

  int getXObjet(){return Xobj;}
  int getYObjet(){return Yobj;}

  int getComptJourSansManger(){return comptJourSansManger;}
  int getComptJour(){return comptJour;}
  int getSexeIdPions(){return sexeIdPions;}



  void position(int newX, int newY, char nom) {
    map.position(x, y, ' ');
    tableauPionsMap[x][y] = Vide;
    y = newX;
    x = newY;
    //cout << "test x = " << y << " test y = " << x << endl;
    map.position(x, y, nom);
    tableauPionsMap[x][y] = sexeIdPions;
    testX = x;
    testY = y;
  }



  void mortNaturel() {
    map.position(x, y, 'S');
    tableauPionsMap[x][y] = Sel_Mineraux;
  }

  void mort() {
    map.position(x, y, ' ');
    tableauPionsMap[x][y] = Vide;
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


//Fonction récursive
//La fonction CompteNbPas permet de calculer le nombre de case qui sépare l'animal de l'objet recherché
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
  void plus_proche(int ID, int precision){
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
        // << "OK" << endl;
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
          testX = x;
          testY = y;
          tabCompt[comptTest] = ComptNbPAS(tab[i], tab[i+1], 1);
          comptTest++;
        }


        int taille = 0;
        //cout << "tabCompt : ";
        for(int i = 0; tabCompt[i] != 200; i++){
          //cout << tab[i] << " ";
          taille++;
        }
        //cout << endl;

        MinCompt = tabCompt[0];
        int position = 0;
        for(int i = 0; tabCompt[i] != 200; i++){
          if(tabCompt[i] < MinCompt){
            MinCompt = tabCompt[i];
            position = i;
          }
        }


        if(taille == 0){
          tailleSuperieur = false;
        }
        else
          tailleSuperieur = true;

        Yobj = tab[position*2];
        Xobj = tab[position*2+1];
        //cout << "Xobj = " << Xobj;
        //cout << ", Yobj = " << Yobj << endl;
  }


};


class Loup : public Animaux {

public:
  Loup() {
    nom = 'L';
    nbTourMaxSurLeTerrain = 60;
    nbTourMaxSansManger = 10;
    sexeIdPions = sexe + 3;
    if(sexeIdPions == 3)
        sexeIdPionsOppose = 4;
      else
        sexeIdPionsOppose = 3;
  }

  ~Loup(){};

  void jouer() {
    if(comptJourSansManger >= nbTourMaxSansManger || comptJour >= nbTourMaxSurLeTerrain){
        mortNaturel();
        Boolmort = true;
      }
      else{//Si toujours en vie
        //cout << "SexePionsId : " << endl;
        plus_proche(sexeIdPionsOppose, 0);
        if(tailleSuperieur){
          if(estAutourCase(Xobj-x, Yobj-y)){ // reproduction
            //cout << "Vide : " << endl;
            plus_proche(Vide, 0);
            if(estAutourCase(Xobj-x, Yobj-y)){
            Boolreproduction = true;
            }
          }
        }
        else{ // Va chasser le moutons
          Boolreproduction = false;
          plus_proche(M, 1);
          //cout << "X : " << Xobj << ", Y : " << Yobj << endl;
          //cout << "Lx : " << x << ", Ly : " << y << endl;
          //cout << "Xobj - x : " << Xobj-x << ", Yobj - y : " << Yobj-y << endl;

          if(estAutourCase(Xobj-x,Yobj-y)){
            if(tailleSuperieur){
            //cout << "Manger!!!!!" << endl;
            BoolManger = true;
            //mangerMouton();
            comptJourSansManger = 0;
            deplacementVersObjet(Yobj, Xobj);
            }
          }
          else{
            //cout << "Deplacement vers Objet" << endl;
            BoolManger = false;
            plus_proche(M, 1);
            //cout << "X : " << Xobj << ", Y : " << Yobj << endl;
            //cout << "Xobj - y : " << Xobj-x << ", Yobj - y : " << Yobj-y << endl;

            deplacementVersObjet(Xobj, Yobj);
          }
        }
        //BoolManger = false;
        comptJour++;
        comptJourSansManger++;
      }
  }

  void mangerMouton(){
      //cout << "J'autorise à manger !" << endl;
      map.position(x, y, ' ');
      tableauPionsMap[x][y] = Vide;
      map.position(Xobj, Yobj, 'L');
      tableauPionsMap[Xobj][Yobj] = sexeIdPions;
  }

  /*
  void reproduction(){
    plus_proche(sexeIdPionsOppose, 0);
    if(estAutourCase(Xobj, Yobj)){ // Verifie si sexe opposé est bien autour de l'animal
      plus_proche(Vide, 0);
      if(estAutourCase(Xobj, Yobj)){ //Verifie coordonnée Case Vide autour de l'animal
        map.position(Xobj, Yobj, 'L');
        tableauPionsMap[Xobj][Yobj] = Loup_BB;
      }
    }
  }
  */


  bool reproductionPossible(){
    plus_proche(sexeIdPionsOppose, 0);
    if(estAutourCase(Xobj, Yobj)){ // Verifie si sexe opposé est bien autour de l'animal
      plus_proche(Vide, 0);
      if(estAutourCase(Xobj, Yobj)){ //Verifie coordonnée Case Vide autour de l'animal
        return true;
      }
      else{
        return false;
      }
    }
    else{
      return false;
    }
  }


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
    if(comptJourSansManger >= nbTourMaxSansManger || comptJour >= nbTourMaxSurLeTerrain){
        mortNaturel();
        Boolmort = true;
      }
      else{//Si toujours en vie
        //cout << "SexePionsId : " << endl;
        plus_proche(sexeIdPionsOppose, 0);
        if(tailleSuperieur){
          if(estAutourCase(Xobj-x, Yobj-y)){ // reproduction
            //cout << "Vide : " << endl;
            plus_proche(Vide, 0);
            if(estAutourCase(Xobj-x, Yobj-y)){
            Boolreproduction = true;
            }
          }
        }
        else{ // Va chasser le moutons
          Boolreproduction = false;
          plus_proche(Herbe, 0);
          //cout << "X : " << Xobj << ", Y : " << Yobj << endl;
          //cout << "Lx : " << x << ", Ly : " << y << endl;
          //cout << "Xobj - x : " << Xobj-x << ", Yobj - y : " << Yobj-y << endl;

          if(estAutourCase(Xobj-x,Yobj-y)){
            if(tailleSuperieur){
            //cout << "Manger!!!!!" << endl;
            BoolManger = true;
            //mangerMouton();
            comptJourSansManger = 0;
            deplacementVersObjet(Yobj, Xobj);
            }
          }
          else{
            //cout << "Deplacement vers Objet" << endl;
            BoolManger = false;
            plus_proche(Herbe, 0);
            //cout << "X : " << Xobj << ", Y : " << Yobj << endl;
            //cout << "Xobj - y : " << Xobj-x << ", Yobj - y : " << Yobj-y << endl;

            deplacementVersObjet(Xobj, Yobj);
          }
        }
        //BoolManger = false;
        comptJour++;
        comptJourSansManger++;
      }
  }

  void mangerHerbe(){
    plus_proche(Herbe, 0);
    if(estAutourCase(Xobj, Yobj)){
      map.position(Xobj, Yobj, 'M');
      tableauPionsMap[Xobj][Yobj] = sexeIdPions;
    }
  }

  void reproduction(){
    //int newX = Xobj, newY = Yobj;
    if(estAutourCase(Xobj, Yobj)){ // Verifie si sexe opposé est bien autour de l'animal
      plus_proche(Vide, 0);
      if(estAutourCase(Xobj, Yobj)){ //Verifie coordonnée Case Vide autour de l'animal
        map.position(Xobj, Yobj, 'M');
        tableauPionsMap[Xobj][Yobj] = Mouton_BB;
      }
    }
  }

};




class SelMineraux : public Pions{
  private :
  int nbTourMax = 1;
  int compt = 0;

  public :
  SelMineraux(){};
  ~SelMineraux(){};

  void Jouer(){
    ComptNbTour(compt);
    compt++;
  }

  void position(int CoordonneX, int CoordonneY){
    x = CoordonneX;
    y = CoordonneY;
    map.position(x, y, 'S');
    tableauPionsMap[x][y] = Sel_Mineraux;
  }

  void ComptNbTour(int compt){
    if(compt == nbTourMax)
      transformationHerbe();
    compt++;
  }

  void transformationHerbe(){
    map.position(x,y,'H');
    tableauPionsMap[x][y] = Herbe;
  }

};




inline bool estUneCaseVide(int x, int y) {
  if(tableauPionsMap[x][y] == Vide)
    return true;
  else
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

bool estAutourCase(int x, int y){
  if((x <= 1 && x >= -1) && (y <= 1 && y >= -1)){ // SI l'Objet est à une case de l'animal (autour de lui)
    return true;
  }
  else
    return false;
}

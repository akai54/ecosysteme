#include <string>
#include <vector>
#include <iterator>
#include <time.h>

#include "map.h"

//Variable Globale
Map map;


enum Pions {Mouton_Male, Mouton_Femelle, Mouton_BB, Loup_Male, Loup_Femelle, Loup_BB, Sel_Mineraux, Herbe, Vide};

int tableauPionsMap[7][7]; // Tableau pour savoir les coordonnées de chaque pions



class Animaux{
protected:
  char nom;
  int nbTourMaxSansManger;   //nb tour max sans manger
  int nbTourMaxSurLeTerrain; //Nb de tour qu'il est sur le terrain
  int x, y; //Coordonnée X et Y de la map
  int sexe; // 0 = mâle; 1 = femelle
  int comptJourSansManger = 0;
  int comptJour= 0;


public:

  Animaux(){
    sexe = rand()%2; // 0 = mâle; 1 = femelle
  }

  ~Animaux(){};

  int sexeAnimaux(){
    return sexe;
  }

  void jouer(){
    if(comptJourSansManger == nbTourMaxSansManger || comptJour == nbTourMaxSurLeTerrain)
      mortNaturel();

    comptJour++;
    comptJourSansManger++;
    cout << comptJour << endl;
  }


  void deplacement(int newX, int newY, char nom, int idPions){
    map.position(x,y,' ');
    tableauPionsMap[x][y] = Vide;
    x = newX;
    y = newY;
    map.position(x,y,nom);
    tableauPionsMap[x][y] = idPions;
  }

  void reproduction();

  void mortNaturel(){
    map.position(x,y, 'S');
  }

  void mort(){
    map.position(x,y,' ');
  }

  //int tabDeplacementPossibe[16]={x+1,y,x+1,y+1,y+1,x,x-1,y+1,x-1,y,x-1,y-1,y-1,x,x+1,y-1}; // Faire indice+2 pour obtenir la direction voulue (que des multiples de 2)(droite puis sens des aiguilles d'une montre)
  void caseAutour(){
    if(x==0){
      if(y==0)
        int tabDirectionPossible[]={x+1,y,x+1,y+1,x,y+1};
      if(y==7)
        int tabDirectionPossible[]={x,y-1,x+1,y-1,x+1,y};
      int tabDirectionPossible[]={x,y-1,x+1,y-1,x+1,y,x+1,y+1,x,y+1};//Si y entre 1 et 6
    }
    else if(x == 7){
      if(y == 0)
        int tabDirectionPossible[]={x,y+1,x-1,y+1,x-1,y};
      if(y==7)
        int tabDirectionPossible[]={x-1,y,x-1,y-1,x,y-1};
      int tabDirectionPossible[]={x,y+1,x-1,y+1,x-1,y,x-1,y-1,x,y-1}; //Si y entre 1 et 6
    }




  }


};





class Loup : public Animaux{


public:
  Loup(){
    nom = 'L';
    nbTourMaxSurLeTerrain = 60;
    nbTourMaxSansManger = 10;
  }

  ~Loup(){};

  void attaquerMoutons();
};





class Mouton : public Animaux{

public:
  Mouton(){
    nom = 'M';
    nbTourMaxSurLeTerrain = 50;
    nbTourMaxSansManger = 5; // Meur qu'au 6eme jours
  }

  ~Mouton(){};

  void mangerHerbe();
};

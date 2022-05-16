#include <string>
#include <vector>
#include <iterator>
#include <time.h>

#include "map.h"

using namespace std;


// Prototype
void AutourCase(int tabDirection[], int taille);


//Variable Globale
Map map;



enum ObjetMap {Mouton_Male, Mouton_Femelle, Mouton_BB, Loup_Male, Loup_Femelle, Loup_BB, Sel_Mineraux, Herbe, Vide};

int tableauPionsMap[7][7]; // Tableau pour savoir les coordonnées de chaque pions

int tabcaseAutour[8] = {Vide, Vide, Vide, Vide, Vide, Vide, Vide, Vide};


class Pions {
protected:
  char nom;
  int x = 0, y = 0;
};



class Animaux : public Pions{
protected:
  int nbTourMaxSansManger;   //nb tour max sans manger
  int nbTourMaxSurLeTerrain; //Nb de tour qu'il est sur le terrain
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

  //int tabDeplacementPossibe[16]={x+1,y,x+1,y+1,x,y+1,x-1,y+1,x-1,y,x-1,y-1,x,y-1,x+1,y-1}; // Faire indice+2 pour obtenir la direction voulue (que des multiples de 2)(droite puis sens des aiguilles d'une montre)

  void Autour(){
    if(x==0){
      if(y==0){
        int tabDirectionPossible[]={x+1,y,x+1,y+1,x,y+1};
        AutourCase(tabDirectionPossible, 6);
      }
      else if(y==7){
        int tabDirectionPossible[]={x,y-1,x+1,y-1,x+1,y};
        AutourCase(tabDirectionPossible, 6);
      }
      else {
      int tabDirectionPossible[]={x,y-1,x+1,y-1,x+1,y,x+1,y+1,x,y+1};//Si y entre 1 et 6
      AutourCase(tabDirectionPossible, 10);
      }
    }
    else if(x == 7){
      if(y == 0){
        int tabDirectionPossible[]={x,y+1,x-1,y+1,x-1,y};
        AutourCase(tabDirectionPossible, 6);

      }
      else if(y==7){
        int tabDirectionPossible[]={x-1,y,x-1,y-1,x,y-1};
        AutourCase(tabDirectionPossible, 6);

      }
      else{
      int tabDirectionPossible[]={x,y+1,x-1,y+1,x-1,y,x-1,y-1,x,y-1}; //Si y entre 1 et 6
      AutourCase(tabDirectionPossible, 10);
      }
    }
    else{
      if(y == 0){
        int tabDirectionPossible[] = {x+1,y,x+1,y+1,x,y+1,x-1,y+1,x-1,y};
        AutourCase(tabDirectionPossible, 10);
      }
      else if(y == 7){
        int tabDirectionPossible[] = {x+1,y,x+1,y-1,x,y-1,x-1,y-1,x-1,y};
        AutourCase(tabDirectionPossible, 10);
      }
      else{
      int tabDirectionPossible[16]={x+1,y,x+1,y+1,x,y+1,x-1,y+1,x-1,y,x-1,y-1,x,y-1,x+1,y-1}; // Si le pions n'est pas proche d'une bordure
      AutourCase(tabDirectionPossible, 16);
      }
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


//Permet de mettre toute les valeurs de
void initialiserTabCaseAutour(int tab[]){
  for(int i = 0; i < 8; i++){
    tab[i] = Vide;
  }
}


void afficherTabInt(int tab[]){
  cout << "tab [ ";
  for(int i = 0; i < 8; i++){
    cout << tab[i];
    if(i < 7)
      cout << ", ";
  }
  cout << " ]" << endl;
}


void AutourCase(int tabDirection[], int taille){
  initialiserTabCaseAutour(tabcaseAutour);
  int compt = 0;
  int x = 0, y = 0;
  for(int i = 0; i < taille; i+=2){
    x = tabDirection[i];
    y = tabDirection[i+1];
    tabcaseAutour[compt] = tableauPionsMap[x][y];
    compt++;
  }
  //afficherTabInt(tabcaseAutour);
}

bool estUneCaseVide(int x, int y){
  if(tableauPionsMap[x][y] == Vide)
    return true;
  return false;
}

void trouverCaseVide(int& x,  int& y){
  if(!estUneCaseVide(x,y)){
    x = rand()%7;
    y = rand()%7;
    trouverCaseVide(x,y);
  }
}

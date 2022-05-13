#include <iostream>


using namespace std;

struct Map{
    int x = 7;
    int y = 7;
    char **tab;

    Map(){ //Constructeur
        tab = new char*[y];
        for (int i = 0; i < y; ++i)
        {
            tab[i] = nullptr;
        }
        for (int i = 0; i < y; ++i)
        {
            tab[i]= new char[x];
        }
        for (int i = 0; i < x; ++i)
        {
            for (int j = 0; j < y; ++j)
            {
                tab[i][j]=' ';
            }
        }
    }

    ~Map(){
        delete tab;
    }

    void affiche(){
        cout<<"   1   2   3   4   5   6   7"<<endl;
        cout<<" +---+---+---+---+---+---+---+"<<endl;
        char p[7]={'A','B','C','D','E','F','G'};
        for(int i = 0; i < x; i++)
        {
            cout<<p[i]<<"| ";
            for(int j = 0; j < y; j++)
            {

                cout<<tab[i][j]<<" | ";
            }
            cout<<endl;

            cout<<" +---+---+---+---+---+---+---+"<<endl;

        }
    }


    void position(int x, int y, char lettre){
        tab[x][y] = lettre;
    }


};

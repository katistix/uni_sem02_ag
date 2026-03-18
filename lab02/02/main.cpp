/*
Sa se determine închiderea transitivă a unui graf orientat.
(Închiderea tranzitivă poate fi reprezentată ca matricea care descrie,
pentru fiecare vârf în parte, care sunt vârfurile accesibile din acest vârf.

Matricea inchiderii tranzitive arată unde se poate ajunge din fiecare vârf.)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

// pt ca e neponderat nu o sa avem niciodata -1, deci folosim -1 ca marcator pt INF
#define INF -1 

using namespace std;


ifstream fin("graf.txt");



vector<vector<int>> adj;

int n; // nr de noduri
int inchidere_tranzitiva[1000][1000];


void calcInchidere(){
    // roy-warshall
    // daca putem lua un k intermediar, ai. i->k->j atunci putem i->j

    // luam un k intermediar
    for(int k=1;k<=n;k++){
        // pt toate perechile i j, vedem daca k este intermediar
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(inchidere_tranzitiva[i][j]==0){
                    if(inchidere_tranzitiva[i][k] == 1 && inchidere_tranzitiva[k][j] == 1){
                        // i->k->j atunci putem i->j
                        inchidere_tranzitiva[i][j] = 1;
                    }
                }
            }
        }
    }
}


int main(){


    // citire graf
    fin >> n;

    int x,y;
    while (fin>>x>>y)
    {
        inchidere_tranzitiva[x][y]=1; // exista arc direct i->j
    }

    // diagonala principala este = 1
    for (int i = 1; i <= n; i++)
    {
        inchidere_tranzitiva[i][i]=1;
    }
    

    calcInchidere();



    // printare matrice inchidere tranzitiva
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout << inchidere_tranzitiva[i][j] << " ";
        }
        cout << "\n";
    }


    return 0;
}
/*

1. Fie un fisier ce contine un graf neorientat reprezentat sub forma: 
prima linie conține numărul nodurilor iar urmatoarele randuri muchiile grafului. 

Sa se scrie un program in C/C++ care sa citeasca fisierul si sa reprezinte/stocheze
un graf folosind matricea de adiacenta, lista de adiacenta si matricea de incidenta. 
Sa se converteasca un graf dintr-o forma de reprezentare in alta.

Fisier -> matrice de adiacenta -> lista adiacenta -> matrice de incidenta -> lista adiacenta -> matrice de adiacenta -> lista.

exemplu fisier
in.txt

4
1 2
3 4
2 3
4 2

*/


#include <fstream>
#include <vector>

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");

void print_matrice_adiacenta(int matrice[100][100], int n){
    for(int i = 1; i<=n; i++){
        for (int j = 1; j <=n; j++)
        {
            fout << matrice[i][j] << " ";
        }
        fout << "\n";
    }
}

void print_lista_adiacenta(vector<vector<int>> lista){
    // afisam fiecare lista interioara
    for(int i=1;i<lista.size();i++){
        fout << i << ": ";
        for (int j = 0; j < lista[i].size(); j++)
        {
            fout << lista[i][j] << " ";
        }
        fout << "\n";
    }
}

int main(){
    int n; // noduri
    int m = 0; // muchii
    fin >> n;
    int x,y;
    // 1. fisier -> matrice adiacenta
    int matrice_adiacenta[100][100]={0};
    while(fin>>x>>y){
        m++; // creste numarul de muchii

        // marcam muchia (x,y)
        matrice_adiacenta[x][y] = 1;
        matrice_adiacenta[y][x] = 1;
    }
    fout << "Matrice de adiacenta:\n";
    print_matrice_adiacenta(matrice_adiacenta, n);

    // 2. matrice adiacenta -> lista adiacenta
    vector<vector<int>> lista_adiacenta(n+1);
    for(int i=1;i<=n;i++){ // pt fiecare nod,
        // formam lista sa de vecini
        for(int j=1;j<=n;j++){
            if(matrice_adiacenta[i][j]) { // daca exista muchia (i,j), atunci j este vecin al lui i
                lista_adiacenta[i].push_back(j);
            }
        }
    }
    fout << "Lista adiacenta:\n";
    print_lista_adiacenta(lista_adiacenta);

    // 3. lista adiacenta -> matrice incidenta
    int matrice_incidenta[100][100] = {0};
    for(int muchie_curenta=1; muchie_curenta<=m; muchie_curenta++){
        // fiecare coloana reprezinta muchia curenta,
        // parcurgem lista_adiacenta 
    }
}
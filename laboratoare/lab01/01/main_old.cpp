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

void print_matrice_adiacenta(int matrice[100][100], int n) {
    fout << "Matrice de adiacenta:\n";
    // Afisam toate elementele matricei, for i for j
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fout << matrice[i][j] << " ";
        }
        fout << "\n";
    }
    fout << "\n";
}

void print_lista_adiacenta(vector<vector<int>> lista) {
    fout << "Lista de adiacenta:\n";
    // pt fiecare vector din lista, afisam elementele vectorului
    for (int i = 1; i < lista.size(); i++) {
        fout << i << ": "; // afisam nodul curent
        for (int j = 0; j < lista[i].size(); j++) {
            fout << lista[i][j] << " ";
        }
        fout << "\n";
    }
    fout << "\n";
}

void print_matrice_incidenta(int matrice[100][100], int n, int m) {
    fout << "Matrice de incidenta:\n";
    // Afisam toate elementele matricei, for i for j
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            fout << matrice[i][j] << " ";
        }
        fout << "\n";
    }
    fout << "\n";
}


int main() {

    // 1. citire in matrice de adiacenta
    int n; 
    int m; 
    fin >> n;
    int matrice_adiacenta[100][100] = {0};
    int x, y;
    while (fin >> x >> y) {
        m++; // crestem numarul de muchii
        // punem in matrice
        matrice_adiacenta[x][y] = 1;
        matrice_adiacenta[y][x] = 1;
    }
    print_matrice_adiacenta(matrice_adiacenta, n);

    // 2. matrice de adiacenta -> lista de adiacenta
    vector<vector<int>> lista_adiacenta(n+1);
    // pt. fiecare element din matrice, daca e 1, adaugam in lista de adiacenta a nodului i, nodul j
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (matrice_adiacenta[i][j] == 1) {
                // putem merge de la i la j, adaugam in lista de adiacenta
                lista_adiacenta[i].push_back(j);
            }
        }
    }
    print_lista_adiacenta(lista_adiacenta);
    /*
    Lista de adiacenta:
    1: 2 
    2: 1 3 4
    3: 2 4 
    4: 2 3 
    */


    // 3. lista de adiacenta -> matrice de incidenta
    int matrice_incidenta[100][100] = {0};
    int muchie = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < lista_adiacenta[i].size(); j++) {
            int nod_adiacent = lista_adiacenta[i][j];
            if (i < nod_adiacent) { // pentru a evita dublarea muchiilor, luam doar muchia i -> nod_adiacent daca i < nod_adiacent
                // muchia dintre i si nod_adiacent este reprezentata in matricea de incidenta
                muchie++; // crestem numarul muchiei curente pe care o procesam
                matrice_incidenta[i][muchie] = 1;
                matrice_incidenta[nod_adiacent][muchie] = 1;
            }
        }
    }
    
    print_matrice_incidenta(matrice_incidenta, n, muchie);
    /*
    Matrice de incidenta:
    1 0 0 0 
    1 0 1 1 
    0 1 1 0
    0 1 0 1
    */


    // 4. matrice de incidenta -> lista de adiacenta
    vector<vector<int>> lista_adiacenta2(n+1);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= muchie; j++) {
            if (matrice_incidenta[i][j] == 1) {
                lista_adiacenta2[i].push_back(j);
            }
        }
    }
    print_lista_adiacenta(lista_adiacenta2);

    // 5. lista de adiacenta -> matrice de adiacenta
    int matrice_adiacenta2[100][100] = {0};
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < lista_adiacenta2[i].size(); j++) {
            int nod_adiacent = lista_adiacenta2[i][j];
            matrice_adiacenta2[i][nod_adiacent] = 1;
            matrice_adiacenta2[nod_adiacent][i] = 1;
        }
    }
    print_matrice_adiacenta(matrice_adiacenta2, n);


    return 0;
}
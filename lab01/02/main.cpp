/*
Fie un graf reprezentat sub o anumita forma
(graful este citit dintr-un fisier).

Sa se rezolve:

a. sa se determine nodurile izolate dintr-un graf.
b. sa se determine daca graful este regular.
c. pentru un graf reprezentat cu matricea de adiacenta sa se determine matricea distantelor.
d. pentru un graf reprezentat cu o matrice de adiacenta sa se determine daca este conex.

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

int main(){
    int n,m;
    // citire
    fin >> n;
    int val;
    int matrice_adiacenta[100][100] = {0};
    for (int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            fin >> matrice_adiacenta[i][j]; // 1 sau 0
            m += matrice_adiacenta[i][j]; // numaram muchiile
        }
    }
    m/=2; // numaram o singura data muchiile

    fout << "a. determinati nodurile izolate\n";

    // formam un "vector de frecventa" pt a numara cati vecini are un nod dat
    vector<int> nr_vecini(n+1);
    for (int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            // idef(matrice_adiacenta[i][j]){
            //     nr_vecini[i]++;
            // } // same as:
            nr_vecini[i]+=matrice_adiacenta[i][j];
        }
    }
    // vedem care nu are vecini
    int count_izolate = 0;
    for (int i = 1; i <=n; i++)
    {
        if (nr_vecini[i]==0){
            fout << i << " ";
            count_izolate++;
        }
    }
    if (!count_izolate) fout << "nu exista noduri izolate";
    fout << "\n\n";

    fout << "b. determinati daca graful este regular\n";
    /*
        un graf este regular daca toate varfurile au acelasi grad
    */
    // avem deja lista cu numarul de vecini, verificam daca toate au acelasi numar de vecini
    int target = nr_vecini[1];
    int e_regular = 1;
    for(int i=2;i<=n;i++){ // mergem de la 2 pt ca target=nr_vecini[1]
	    if(nr_vecini[i] != target){
		e_regular = 0;
		break;
	    }
    }
    if(e_regular) fout << "graful este regular\n";
    else fout << "graful nu este regular\n";



    fout << "c. determinati matricea distantelor\n";


    // folosim roy-floyd
    int d[100][100] = {0}; // matricea distantelor
    int INF = 99999;
    // initializam matricea
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
        	// daca exista o muchie directa, distanta e 1
        	if (matrice_adiacenta[i][j]) d[i][j]=1;
        	// daca i = j, este acelasi nod, distanta 0
        	else if (i==j) d[i][j] = 0;
        	// altfel, presupunem distanta infinita (adica nu putem ajunge acolo)
        	else d[i][j] = INF; // nu avem cum sa avem distanta mai mare de 100 dar punem ceva mare, practic infinit
		}
    }

    // roy-floyd: luam fiecare nod ca fiind intermediar pt o pereche i,j,
    // iar daca suma drumului de la i la j prin nodul intermediar e mai scurta decat drumul direct de la i la j,
    // atunci actualizam lungimea drumului dintre i j



    // afisare roy-floyd
    for (int k=1;k<=n;k++){
	    for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
            	if(d[i][k]+d[k][j]<d[i][j]){
            		d[i][j] = d[i][k]+d[k][j];
            	}
    		}
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == INF) fout << "inf ";
            else fout << d[i][j] << " ";
        }
        fout << "\n";
    }

    
    

}

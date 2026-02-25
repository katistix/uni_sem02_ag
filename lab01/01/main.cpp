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
void print_matrice_incidenta(int matrice[100][100], int n, int muchii){
    for(int i = 1; i<=n; i++){
        for (int j = 1; j <=muchii; j++)
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
    int muchie_curenta = 1;
    // parcurgem lista de adiacenta, si punem pe coloane muchiile,
    // avem un contor pt cate muchii am adaugat deja, si adaugam doar daca i<j pt a asigura o ordine si a nu dubla muchii
    for(int i=1;i<=n;i++){
        for (int j = 0; j < lista_adiacenta[i].size(); j++)
        {
            if(i<=lista_adiacenta[i][j]){ // impunem o ordine pt a nu dubla muchiile, <= pt ca poate sa fie si bucla
                matrice_incidenta[i][muchie_curenta]++; // creste contorul pt muchii incidente
                matrice_incidenta[lista_adiacenta[i][j]][muchie_curenta]++; // daca avem muchia (i,i), atunci pur si simplu se v-a pune 2 pe pozitia corespunzatoare
                muchie_curenta++;
            }
        }
    }
    fout << "Matrice incidenta: \n";
    print_matrice_incidenta(matrice_incidenta, n, m);

    // 4. matrice de incidenta -> lista adiacenta
    vector<vector<int>> lista_adiacenta2(n+1);
    // parcurgem pe coloane, daca gasim valoarea 2, atunci x=y=randul_curent,
    // daca valoarea e 1, atunci punem in "urmatoarea" variabila libera (x si apoi y)
    for(int j=1;j<=m;j++){
        // parcurgem randurile coloanei curente
        x=-1; y=-1;
        for(int i=1;i<=n;i++){

            if(matrice_incidenta[i][j]==2){ // cazul buclei
                x=i; y=i;
                break;
            }

            if(x==-1 && matrice_incidenta[i][j]==1){ // daca trebuie sa completam prima extremitate
                x=i;
            }
            else if(x!=-1 && matrice_incidenta[i][j]==1){ // daca trebuie sa completam a doua extremitate
                y=i;
                break; // finalul cautarii, deoarece stim ambele extremitati
            }
        }
        // introducere in lista de adiacenta, in ambele directii ca e neorientat
        lista_adiacenta2[x].push_back(y);
        lista_adiacenta2[y].push_back(x);
    }
    fout << "Lista adiacenta 2:\n";
    print_lista_adiacenta(lista_adiacenta2);

    // 5. lista adiacenta -> matrice adiacenta
    int matrice_adiacenta2[100][100]={0};
    for(int i=1;i<=n;i++){
        for (int j = 0; j < lista_adiacenta2[i].size(); j++)
        {
            int nod = lista_adiacenta2[i][j];
            matrice_adiacenta2[i][nod]=1;
            // e suficient intr-o directie deoarece lista de adiacenta deja contine, la un moment dat si directia inversa
        }
    }
    fout << "Matrice adiacenta 2:\n";
    print_matrice_adiacenta(matrice_adiacenta2, n);

    // 6. matrice adiacenta -> lista muchii
    // vom printa doar perechile de deasupra diagonalei principale pentru a evita duplicate
    vector<pair<int,int>> muchii2;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i+1; j <= n; j++)
        {
            if (matrice_adiacenta2[i][j]==1) muchii2.push_back(make_pair(i,j));
        }
    }
    fout << "Lista de muchii:\n";
    fout << "Exista " <<  muchii2.size() << " muchii:\n";
    for(int i=0;i<muchii2.size();i++){
        fout << muchii2[i].first << " " << muchii2[i].second << "\n";
    }
    
}
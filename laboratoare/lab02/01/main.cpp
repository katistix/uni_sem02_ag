/*
Implementați algoritmul lui Moore pentru un graf orientat neponderat
(algoritm bazat pe Breath-first search, vezi cursul 2).

Datele sunt citete din fisierul graf.txt.

Primul rând din graf.txt conține numărul vârfurilor,
iar următoarele rânduri conțin muchiile grafului.

Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf
(vârful sursa poate fi citit de la tastatura).
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
vector<int> distante;
vector<int> parinte; // vector de parinti pt a reconstrui lantul
int n; // nr de noduri


void Moore(int start){
    distante[start] = 0; // deja suntem la start, distanta 0
    // initializam restul la infinit
    for(int i=1; i<=n; i++){
        if (i!=start) distante[i] = INF;
    }

    // folosim o coada in care punem nodul de start
    queue<int> Q;
    Q.push(start);

    // cat timp avem ceva in coada
    while (!Q.empty())
    {
        // luam varful cozii
        int nod = Q.front();
        Q.pop();

        // pentru toti vecinii nodului
        for(int next : adj[nod]){
            // daca distanta pana la next este INF, atunci nu l-am vizitat pe next inca
            if(distante[next]==INF){
                parinte[next] = nod; // ajungem din nod in next
                // distanta pana la next este distanta pana la nod+1
                distante[next]=distante[nod]+1;
                
                // punem next in coada, pt. a-i procesa vecinii
                Q.push(next);
            }
        }
    }
}


void print_lant(int start, int destinatie) {
    if (distante[destinatie] == INF) {
        cout << "nu exista drum de la " << start << " la " << destinatie << endl;
        return;
    }

    vector<int> drum;
    int nod = destinatie;
    
    // Mergem inapoi pe firul parintilor pana ajungem la start
    while (nod != 0) {
        drum.push_back(nod);
        nod = parinte[nod];
    }

    // Inversam drumul pentru a-l afisa de la start la destinatie
    reverse(drum.begin(), drum.end());

    cout << "lantul cel mai scurt: ";
    for (int i = 0; i < drum.size(); i++) {
        cout << drum[i];
        if(i!=drum.size()-1){
            cout << "->";
        }
    }
    cout << "\ndistanta: " << distante[destinatie] << endl;
}


int main(){


    // citire graf
    fin >> n;

    adj.resize(n+1); // indexam de la 1
    distante.resize(n+1);
    parinte.resize(n+1);

    int x,y;
    while (fin>>x>>y)
    {
        adj[x].push_back(y); // avem muchie de la x la y
    }

    // citire nod sursa
    int start;
    cout << "Introdu nodul de start: ";
    cin >> start;

    Moore(start);

    int dest;
    cout << "Introdu destinatia pt care sa se afiseze lantul: ";
    cin >> dest;

    print_lant(start, dest);


    return 0;
}
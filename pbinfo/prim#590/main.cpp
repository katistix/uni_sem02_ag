/*
Se dă un graf neorientat ponderat conex cu n vârfuri și m muchii - 
în care fiecare muchie are asociat un cost, număr natural strict pozitiv.

Folosind algoritmul lui Prim, determinați un arbore parțial de cost minim,
cu rădăcina în vârful 1.

Fișierul de intrare prim.in conține pe prima linie numerele n m,
iar următoarele linii câte un triplet i j c, cu semnificația:
există muchia (i j) și are costul c.

Fișierul de ieșire prim.out va conține pe prima linie
costul arborelui de cost minim determinat,
iar pe a doua linie vectorul de tați al arborelui,
cu elementele separate prin exact un spațiu
*/

#include<iostream>
#include<fstream>
#include<queue>
#define INF 99999999

using namespace std;

ifstream fin("prim.in");
ofstream fout("prim.out");

int n,m;

// reprezentarea grafului
vector<pair<int, int>> G[1001];
int parent[1001];
int d[1001];
int viz[1001];
int total_cost = 0;



void Prim(int start){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // bag primul nod in coada
    pq.push({0, start}); // distanta pana la start este 0
    parent[start] = 0; // start nu are parinte

    for (int i = 1; i <= n; i++)
    {
        d[i] = INF;
    }
    


    while (!pq.empty())
    {
        // extragem cea mai "prioritara muchie" (cea mai ieftina)
        pair<int, int> much = pq.top();
        pq.pop();

        // daca deja am vizitat destinatia, ignoram muchia
        if (viz[much.second]) continue;


        // marcam destinatia ca vizitata si punem in coada toate
        // muchiile sale adiacente
        viz[much.second] = 1;

        total_cost+=much.first;

        for(auto next_much : G[much.second]){
            // daca muchia este mai ieftina decat cea curenta pentru destinatia sa
            if (!viz[next_much.second] && next_much.first < d[next_much.second]) {
                parent[next_much.second] = much.second; // update parent
                d[next_much.second] = next_much.first; // update distanta
                // punem muchia in coada
                pq.push(next_much);
            }
        }
    }
}

int main(){
    // citire
    fin>>n>>m;

    int x,y,c;
    for(int i=0;i<m;i++){
        fin>>x>>y>>c;
        // punem ambele directii
        G[x].push_back({c, y});
        G[y].push_back({c, x});
    }

    Prim(1);

    fout << total_cost << "\n";

    // afisare
    for (int i = 1; i <= n; i++)
    {
        fout << parent[i] << " ";
    }
    
    return 0;


}
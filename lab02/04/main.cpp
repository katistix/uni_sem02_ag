/*
Pentru un graf dat să se afișeze pe ecran
vârfurile descoperite de algoritmul BFS și
distanța față de vârful sursă (arborele descoperit). 
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#define INF 9999999

using namespace std;

ifstream fin("graf.txt");

vector<vector<int>> graf;
vector<int> dist; // vectorul de distante
int n, sursa;

void BFS(int sursa){
    queue<int> Q;

    Q.push(sursa);

    while (!Q.empty())
    {
        int nod = Q.front();
        Q.pop();

        // parcurgem toti vecinii nodului
        for (int next:graf[nod]){
            // prima data cand ajungem la acel nod, e si cea mai scurta
            // datorita modului in care BFS functioneaza
            // deci e destul sa verificam daca distanta curenta pana la next
            // este INF, si daca este atunci setam distanta
            if(dist[next] == INF){
                dist[next] = dist[nod] + 1;
            }

            // punem next in coada
            Q.push(next);
        }
    }
}

int main(){

    // citire
    fin >> n;
    fin >> sursa;
    graf.resize(n+1);
    dist.resize(n+1);


    // initializare distante
    for(int i=1;i<=n;i++){
        if(i!=sursa) dist[i] = INF;
        else dist[i] = 0; // distanta pana la sursa este 0
    }

    int x, y;
    while (fin >> x >> y)
    {
        graf[x].push_back(y);
    }


    // aplicare BFS
    BFS(sursa);

    
    // afisam doar distantele care != INF
    int contor = 0;
    for (int i = 1; i <=n; i++)
    {
        if(dist[i]!=INF){
            contor++;
            cout << i << " la o distanta de " << dist[i] << " de nodul sursa\n";
        }
    }

    cout << "\n" << contor << " noduri descoperite.\n";

    return 0;
}
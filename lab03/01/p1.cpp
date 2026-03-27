// Bellman-Ford

#include <iostream>
#include <fstream>
#include <vector>
#define INF 1e8

using namespace std;


int n; // nr noduri
int m; // nr arce
int sursa; // nodul sursa


// vector<vector<pair<int,int>>> G;
struct Muchie {
    int x;
    int y;
    int w;
};

vector<Muchie> muchii;


vector<int> bellmanFord(){

    // avem un vector de distante
    vector<int> dist(n,INF);
    dist[sursa] = 0;

    
    // se face "relaxarea" de maxim |V| ori
    // pt a detecta cicluri negative
    for (int i=1;i<=n;i++){
        bool modified = 0;
        // pentru fiecare muchie din graf
        for (auto muchie : muchii)
        {
            // daca inca nu stim cum sa ajungem la muchie.x
            // sarim peste aceasta muchie
            if(dist[muchie.x]==INF) continue;

            // daca prim muchia curenta putem sa ajungem
            // mai ieftin la muchie.y, atunci actualizam
            if(dist[muchie.x] + muchie.w < dist[muchie.y]){
                dist[muchie.y] = dist[muchie.x] + muchie.w;
                modified=1;

                // daca suntem la iteratia n, si inca facem "relaxari"
                // inseamna ca exista ciclu de cost negativ
                // returnam un vector cu {-1}
                if (i==n){
                    return {-1};
                }
            }
        }

        // OPTIMIZARE: 
        // daca nu s-a facut nicio actualizare la distante atunci ne putem opri
        if (!modified) break;
    }

    return dist; // returnam vectorul de distante
}



int main(int argc,char* argv[]){
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    fin >> n >> m >> sursa;

    // citim muchiile
    int x,y,w;
    for (int i = 0; i < m; i++)
    {
        Muchie much;
        fin >> much.x >> much.y >> much.w;
        muchii.push_back(much);
    }

    vector<int> distante = bellmanFord();

    if(distante.size() == 1 && distante[0] == -1) {
        fout << "Exista ciclu de cost negativ!";
        return 0;
    }

    // afisare
    for (auto dist:distante)
    {
        if (dist==INF){
            fout << "INF ";
        }
        else {
            fout << dist << " ";
        }
    }
    

    fin.close();
    fout.close();

}
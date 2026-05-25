#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int INF = 1e8;

ifstream fin("input.txt");
ofstream fout("out.txt");

struct Muchie {
    int u;
    int v;
    int cost;
};

vector<Muchie> muchii;


int n, m;


struct BellmanResult {
    bool hasNegativeCycle;
    vector<int> distante;
};

BellmanResult bellman_ford(int start){
    vector<int> dist(n,INF);
    dist[start] = 0; // distanta pana la sursa e 0

    // facem "relaxari" de maxim n-1 ori
    // daca in N-a oara inca se fac relaxari atunci exista ciclu de cost negativ
    bool modified = false;
    for (int i=1; i<=n; i++) {
        modified = false;
        // pentru fiecare muchie din graf, facem relaxare
        for (const auto& muchie : muchii) {
            // daca nu stim cum sa ajungem la muchie.u, atunci skip, we'll be right back
            if(dist[muchie.u] == INF) continue;

            // daca, luand muchia curenta in considerare,
            // este mai ieftin sa ajungem la muchie.v, 
            // atunci facem relaxarea
            if (dist[muchie.u] + muchie.cost < dist[muchie.v]) {
                dist[muchie.v] = dist[muchie.u] + muchie.cost; // update min

                modified = true; // pt optimizare (early stop)


                // daca relaxarea a avut loc in a N-a iteratie,
                // atunci exista ciclu de cost negativ
                if(i==n){
                    return {
                        true,
                        {}
                    };
                }

            }
        }

        if(!modified) break;
    }
    
    return {
        false, 
        dist
    };

}


int main(){
    
    int start;
    fin >> n >> m >> start;

    int u,v,c;
    for (int i=0; i<m;i++) {
        fin >> u >> v >> c;
        muchii.push_back({
            u,v,c
        });
    }

    // aplica bellman ford
    BellmanResult res = bellman_ford(start);

    if(res.hasNegativeCycle) {
        fout << "Exista ciclu de cost negativ\n";
        return 0;
    }

    // afisare costuri
    for (auto cost : res.distante) {
        if(cost == INF){
            fout << "INF ";
        }
        else{
            fout << cost << " ";
        }
    }

    return 0;

}
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin("lantpq.in");
ofstream fout("lantpq.out");

vector<vector<int>> G;
int n,m;
int p,q;
int lanturi_gasite = 0;

vector<bool> viz;
void DFS(vector<int>& lant_curent, int nod){
    // vizitam nodul
    lant_curent.push_back(nod);
    viz[nod] = true;
    
    // afiseaza lantul curent
    if(lant_curent.size() - 1 >= p && lant_curent.size() - 1 <= q){
        lanturi_gasite++;
        for (int i=0;i<lant_curent.size();i++) {
            fout << lant_curent[i] << " ";
        }
        fout << "\n";
    }

    if(lant_curent.size() - 1 <= q){
        // vizitam toti vecinii nevizitati ai nodului
        for (int next : G[nod]) {
            if (!viz[next]) {
                DFS(lant_curent, next);
            }
        }
    }


    viz[nod] = false;
    lant_curent.pop_back();
}

int main(){

    // citim n,m
    fin >> n >> m;
    G.resize(n+1);
    viz.resize(n+1);
    for (int i=0; i<=n; i++) {
        viz[i] = false;
    }

    // citim m muchii
    int u,v;
    for (int i=0; i<m; i++) {
        fin >> u >> v;

        if (find(G[u].begin(), G[u].end(), v) == G[u].end()) {
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }
    // sorteaza listele sa fie in ordine
    for (int i=1; i<=n; i++) {
        sort(G[i].begin(), G[i].end());
    }

    // citim p q
    fin >> p >> q;

    // aplica DFS pornind din fiecare
    vector<int> lant;
    for (int i=1; i<=n; i++) {
        DFS(lant, i);
    }

    if (!lanturi_gasite) {
        fout << "NU EXISTA\n";
    }

}
/*
Pentru un graf dat să se afișeze pe ecran
vârfurile descoperite de apelul recursiv
al procedurii DFS_VISIT(G, u).
*/

#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

ifstream fin("graf.txt");

vector<bool> viz;

// DFS_VISIT(G, u) - recursiv
void DFS_VISIT(vector<vector<int>> G, int nod){
    viz[nod] = true;

    // vizitam recursiv vecinii lui `nod`
    for(int next:G[nod]){
        // daca nu e vizitat deja
        if(viz[next]==false){
            DFS_VISIT(G, next);
        }
    }
}

int main(){

    vector<vector<int>> graf;
    int n, sursa;
    
    // citire
    fin >> n;
    fin >> sursa;
    
    graf.resize(n+1);
    viz.resize(n+1, false);
    
    int x,y;
    while (fin >> x >> y)
    {
        graf[x].push_back(y);
    }
    

    // DFS
    DFS_VISIT(graf, sursa);


    // afisare
    cout << "noduri vizitate: ";
    for (int i = 1; i <=n; i++)
    {
        if(viz[i]) cout << i << " ";
    }
    


    return 0;
}
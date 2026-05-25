/*
Se dau cele n-1 muchii ale unui arbore cu n noduri și un nod k.
Afișați vectorul de tați al arborelui cu rădăcina în k.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

ifstream fin("arbore.in");
ofstream fout("arbore.out");

int p[105];
int viz[105];
vector<vector<int>> G;


void BFS(int root){
    p[root]=0;
    viz[root]=1;

    queue<int> Q;
    Q.push(root);

    while (!Q.empty())
    {
        int nod = Q.front();
        Q.pop();

        // parcurg toti vecinii nevizitati ai nodului
        for(auto next: G[nod]){
            if(!viz[next]){
                Q.push(next);
                p[next]=nod;
                viz[next]=1;
            }
        }
    }
    
}

int main(){


    int x,y;
    int n,k;
    fin >> n >> k;
    G.resize(n+1);

    while(fin >> x >> y){    
        G[x].push_back(y);
        G[y].push_back(x);
    }

    // apelare BFS
    BFS(k);

    // afisare vector tati
    for (int i = 1; i <= n; i++)
    {
        fout << p[i] << " ";
    }
    
    

}
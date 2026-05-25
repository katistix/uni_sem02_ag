#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream fin("input.txt");

int n,m;

vector<vector<int>> G;
bool viz[100005];
int muchii_vizitate = 0;

void dfs(int nod){
    viz[nod] = true;

    for (int next : G[nod]) {
        if (!viz[next]) {
            muchii_vizitate++;
            dfs(next);
        }
    }
}

int main(){

    fin >> n >> m;
    G.resize(n+1);

    int x,y;
    for (int i=0;i<m;i++) {
        fin >> x >> y;

        G[x].push_back(y);
        G[y].push_back(x);
    }

    dfs(1);

    if(muchii_vizitate == m){
        cout << "DA\n";
    }
    else {
        cout << "NU\n";
    }
    
    
}
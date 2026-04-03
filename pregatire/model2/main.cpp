#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("input.txt");

vector<vector<int>> G;

int n,m;

void BFS(vector<bool>& viz, int start, int a, int b){
    queue<int> Q;
    viz[start] = true;
    Q.push(start);

    while (!Q.empty()) {
        int nod = Q.front(); Q.pop();

        for (int next : G[nod]) {
            if(!viz[next]){
                // ignore the a-b edge
                if ((nod == a && next == b) || (nod == b && next == a)) continue;

                viz[next] = true;
                Q.push(next);
                
            }
        }
    }
}

int main(){
    // citire
    fin >> n >> m;
    G.resize(n+1);
    vector<bool> viz(n+1, false);

    // citeste muchiile
    int x,y;
    for (int i =0; i<m;i++) {
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    // citeste de la tastatura
    cout << "introdu muchia care sa fie ignorata: ";
    cin >> x >> y;

    BFS(viz,1, x, y);

    // if after BFS we still have nodes that are not visited,
    // then the x,y edge is required
    for (int i = 1; i <= n; i++) {
        if (!viz[i]) {
            cout << "NU\n";
            return 0;
        }
    }

    cout << "DA\n";
    return 0;
}

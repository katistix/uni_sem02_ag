#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

ifstream fin("input.txt");
ofstream fout("out.txt");

int n, m;

vector<vector<int>> G;

void BFS(vector<int>& comp, int componenta, int start){
    queue<int> Q;

    comp[start] = componenta;
    Q.push(start);


    while (!Q.empty()) {
        // take the leading element
        int nod = Q.front(); Q.pop();

        // visit all non-visited neighbors
        for(int next : G[nod]){
            if(!comp[next]) {
                comp[next] = componenta;
                Q.push(next);
            }
        }
    }
}


int main(){
    // citire
    fin >> n >> m;
    G.resize(n+1);
    vector<int> comp(n+1, 0);
    
    int x,y;
    for (int i=0;i<m;i++) {
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    // aplica BFS pentru a determina componentele conexe
    int componenta = 0;
    for(int i = 1; i<=n; i++){
        if(!comp[i]){ // daca nodul i nu se afla intr-o componenta conexa, incepem o noua componenta din el
            componenta++;
            BFS(comp, componenta, i);
        }
    }

    // acum avem in comp componenta conexa din care apartine fiecare nod
    // pt fiecare componenta afisam doar nodurile care fac parte din ea
    for (int k=1;k<=componenta;k++) {
        fout << "componenta " << k << ": ";
        for (int i=1;i<=n; i++) {
            if(comp[i] == k){
                fout << i << " ";
            }
        }
        fout << "\n";
    }
}
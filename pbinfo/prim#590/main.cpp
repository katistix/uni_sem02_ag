#include<iostream>
#include<fstream>
#include<queue>
#define INF 99999999
using namespace std;

ifstream fin("prim.in");
ofstream fout("prim.out");

int G[105][105];
int parent[105];
int dist[105];
bool viz[105];
int n, m;

int Prim(int start){

    dist[start]=0;
    parent[start]=0;

    int cost_total = 0;
    



}

int main(){
    fin >> n >> m;


    for (int i = 1; i <= n; i++)
    {
        dist[i]=INF;
    }
    

    int x,y,c;
    for(int i=0;i<m;i++){
        fin>>x>>y>>c;
        G[x][y]=c;
        G[y][x]=c;
    }

    Prim(1);

}
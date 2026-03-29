#include <fstream>

#define INF 999999999

using namespace std;

ifstream fin("picard.in");
ofstream fout("picard.out");

int n,m;
int G[105][105];
int sume[105];


void RoyFloyd(){
    // nod intermediar
    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if(i==j) continue;

                    // relax
                    if(G[i][k]+G[k][j] < G[i][j]){
                        G[i][j] = G[i][k]+G[k][j];
                    }
                }
                
        }
    }
}

int main(){
    // citire
    fin >> n >> m;

    // initial toate distantele sunt infinite
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++){
            if(i==j) G[i][j]=0;
            else G[i][j] = INF;
        }
    }
    int x,y,c;
    for (int i = 0; i < m; i++)
    {
        fin >> x >> y >> c;
        G[x][y]=c;
        G[y][x]=c;
    }


    RoyFloyd();

    // calcul sume + suma max
    int suma_max=0;
    for (int i = 1; i <= n; i++)
    {
        int suma_curenta = 0;
        for (int j = 1; j <= n; j++){
            suma_curenta+=G[i][j];
        }

        sume[i]=suma_curenta;

        if (suma_curenta>suma_max)
        {
            suma_max = suma_curenta;
        }
        
    }

    // print noduri cu suma max
    for (int i = 1; i <= n; i++)
    {
        if (suma_max == sume[i])
        {
            fout << i << " ";
        }
        
    }
    

    
}
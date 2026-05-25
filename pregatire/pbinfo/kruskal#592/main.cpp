#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
#define INF 99999999
using namespace std;

ifstream fin("kruskal.in");
ofstream fout("kruskal.out");

struct muchie {
    int x,y,cost;
};


int n,m;
int comp[105];
vector<muchie> muchii(105);


int cmp(muchie a, muchie b){
    return a.cost < b.cost;
}

int find_root(int x){
    if(comp[x]==x) return x; // daca x este radacina a arborelui

    comp[x] = find_root(comp[x]); // path compression - punem direct radacina in locul lui x

    return comp[x];
}

bool uneste(int a, int b){
    int root_a = find_root(a);
    int root_b = find_root(b);

    if (root_a == root_b) return false; // daca sunt in aceeasi componenta conexa, nu le unim

    comp[root_b] = root_a; // uneste cele 2 componente conexe, legam o radacina de cealalta
    return true;
}

int main(){
    fin >> n >> m;
    muchii.resize(m);
    
    // citire
    int x,y,c;
    for(int i=0;i<m;i++){
        fin>>x>>y>>c;
        muchii[i].x = x;
        muchii[i].y = y;
        muchii[i].cost = c;
    }
    
    
    // SORTAM MUCHIILE CRESCATOR DUPA COST
    sort(muchii.begin(), muchii.end(), cmp);
    
    vector<muchie> mst;
    int cost_total = 0;

    for (int i = 1; i < n; i++)
    {
        comp[i]=i; // initial fiecare nod este in propria componenta conexa
    }
    

    // parcurgem toate muchiile (in functie de cost)
    for(int i=0;i<m;i++){
        // capetele muchiei
        int st = muchii[i].x; 
        int dr = muchii[i].y;

        // daca fac parte din componente conexe diferite, 
        // inseamna ca daca adaugam muchia curenta, nu formam ciclu
        // if (comp[st] != comp[dr]) 
        // {
        //     // punem muchia in mst
        //     mst.push_back(muchii[i]);
        //     cost_total+=muchii[i].cost;

        //     // UNIM COMPONENTELE CONEXE
        //     // probabil se poate face cumva mai eficient
        //     int a = comp[st]; // componenta conexa A
        //     int b = comp[dr]; // componenta conexa B

        //     // vedem care noduri j sunt in componenta B si le punem in A
        //     for (int j = 1; j <= n; j++){
        //         if (comp[j] == b){
        //             comp[j] = a;
        //         }
        //     }

        // }

        // daca se unesc cele 2 componente conexe, adaugam muchia in mst
        if (uneste(st, dr)){
            mst.push_back(muchii[i]);
            cost_total+=muchii[i].cost;
        }
    }   


    // afisare
    fout << cost_total << endl;
    for (int i = 0; i < mst.size(); i++)
    {
        fout << mst[i].x << " " << mst[i].y << endl;
    }


}
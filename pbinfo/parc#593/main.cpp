#include <fstream>
#include <vector>
#include <queue>

#define INF 999999999

using namespace std;

ifstream fin("parc.in");
ofstream fout("parc.out");


int n,m,C;
int P;
vector<vector<pair<int,int>>> G;
vector<int> porti;



vector<int> Dijkstra(int start){
    // initializare dist
    vector<int> dist(n+1,INF);
    dist[start] = 0; // distanta pana la start e 0

    // priority queue pentru noduri
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    pq.push({0, start});

    while (!pq.empty())
    {
        pair<int,int> muchie = pq.top();
        pq.pop();
        int y = muchie.second;
        int cost = muchie.first;

        // if this is not better, skip
        if(cost > dist[y]) continue;

        // pentru toti vecinii
        for (auto next_muchie : G[muchie.second])
        {
            int cost_next = next_muchie.first;
            int next = next_muchie.second;

            // daca dist[x]+w < dist[y] update
            if(dist[y] + cost_next < dist[next]){
                dist[next] = dist[y] + cost_next;
                pq.push({dist[next], next});
            }
        }
    }

    return dist;
}

int main(){

    // citire
    fin >> n >> m >> C;

    G.resize(n+1);

    int x,y,L;
    for (int i = 0; i < m; i++)
    {
        fin >> x >> y >> L;
        G[x].push_back({L,y});
        G[y].push_back({L,x});
    }   

    fin >> P;
    for (int i = 0; i < P; i++)
    {
        int poarta;
        fin >> poarta;
        porti.push_back(poarta);
    }


    // diskstra
    vector<int> dist = Dijkstra(C);

    int min_enterance_cost = INF;
    for (int i = 0; i < P; i++)
    {
        if(dist[porti[i]] < min_enterance_cost){
            min_enterance_cost = dist[porti[i]];
        }
    }

    for (int i = 1; i < n; i++)
    {
        if(dist[i] == min_enterance_cost){
            fout << i;
            break;
        }
    }

    return 0;
}
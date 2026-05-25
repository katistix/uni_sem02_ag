#include <cmath>
#include <functional>
#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>


#define INF 1e8

using namespace std;

ifstream fin("input.txt");

int n,m;
int S,F;

vector<pair<int, int>> points;

vector<vector<pair<double, int>>> G;

vector<double> Dijkstra(){
    vector<double> dist(n+1, INF);



    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> PQ;
    PQ.push({0.0, S});
    dist[S] = 0.0;

    // while there are elements in the queue
    while (!PQ.empty()) {
        // take the top element
        pair<double, int> el = PQ.top(); PQ.pop();
        double d = el.first; 
        int node = el.second;

        // skip outdated
        if (dist[node] < d) continue;

        // relax all neighbors
        for (auto el : G[node]) {
            double cost = el.first;
            int next = el.second;
            // daca trecand prin aceasta muchie este mai eficient
            // atunci relaxam
            if (dist[next] > dist[node] + cost) {
                // relax
                dist[next] = dist[node] + cost;
                // put the relaxed thing in the PQ
                PQ.push({dist[next], next});
            } 
        }
    }

    return dist;
}

int main(){

    fin >> n >> m;
    points.push_back({0,0});
    G.resize(n+1);
    int x,y;
    for (int i=0;i<n;i++) {
        fin >> x >> y;
        points.push_back({x,y});
    }


    // read edges
    int v,u;
    for (int i=0; i<m; i++) {
        fin >> u >> v;
        double dx = points[v].first-points[u].first;
        double dy = points[v].second-points[u].second;
        // compute the distance
        double cost = sqrt(dx*dx + dy*dy);

        G[u].push_back({cost, v});
    }


    // read start finish
    cin >> S >> F;

    vector<double> dist = Dijkstra();


    cout << dist[F];

}
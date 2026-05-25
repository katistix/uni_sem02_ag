#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct Muchie {
  int u, v, cost;
};
int cost_total = 0;

int n, m;
vector<vector<pair<int, int>>> G;
vector<bool> viz;
vector<Muchie> mst;

struct CompareCost {
  bool operator()(const Muchie &a, const Muchie &b) { return a.cost > b.cost; }
};

int main() {
  ifstream fin("apm.in");
  ofstream fout("apm.out");

  priority_queue<Muchie, vector<Muchie>, CompareCost>
      muchii_accesibile; // cost,destinatie

  fin >> n >> m;
  G.resize(n + 1);
  viz.resize(n + 1, false);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    fin >> u >> v >> c;
    G[u].push_back({v, c});
    G[v].push_back({u, c});
  }

  // incepem de la un nod oarecare, il alegem pe 1
  viz[1] = true;
  // punem toate muchiile sale adiacente in PQ
  for (const auto &vecin : G[1]) {
    muchii_accesibile.push({1, vecin.first, vecin.second});
  }

  // cat timp mai avem muchii de procesat
  while (!muchii_accesibile.empty()) {
    // preia prima muchie
    Muchie curenta = muchii_accesibile.top();
    muchii_accesibile.pop();

    int u = curenta.u;
    int v = curenta.v;
    int cost = curenta.cost;

    // daca destinatia nu a fost vizitata, punem muchia in mst
    if (!viz[v]) {
      cost_total += cost;
      viz[v] = true;

      mst.push_back(curenta); // adaugare in mst

      // adaugam toate muchiile adiacente in coada
      for (const auto &vecin : G[v]) {
        int urmatorul = vecin.first;
        int cost_muchie = vecin.second;
        if (!viz[urmatorul]) {
          muchii_accesibile.push({v, urmatorul, cost_muchie});
        }
      }
    }
  }

  // afisare
  fout << cost_total << endl;
  fout << mst.size() << endl;
  for (const auto &m : mst) {
    fout << m.u << " " << m.v << "\n";
  }

  return 0;
}
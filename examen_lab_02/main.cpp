/*
algoritmul lui prim. complexitate O(M log N) (daca implementam cu PQ)

- pornim de la un nod oarecare (am ales primul (1))
- parcurgem aproape ca la BFS graful, dar alegem mereu cea mai ieftina muchie
adiacenta cu arborele curent (kinda like Greedy)
- folosim un PQ pentru a ordona automat muchiile adiacente arborelui curent
- repetam pana cand am vizitat toate nodurile

utilitate reala:
avem o retea de calculatoare, vrem sa folosim cat mai putin cablu pentru a le
conecta pe toate

*/

#include <fstream>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct Muchie {
  int u, v, cost;
};

int cost_total = 0; // costul total al MST-ului

int n, m;
vector<vector<pair<int, int>>> G; // liste de adiacenta (destinatie, cost)
vector<bool> viz;
vector<Muchie> mst; // MST-ul solutie

struct RelOrdine {
  bool operator()(const Muchie &a, const Muchie &b) { return a.cost > b.cost; }
};

int main() {
  ifstream fin("prim.in");
  ofstream fout("prim.out");

  priority_queue<Muchie, vector<Muchie>, RelOrdine>
      muchii_accesibile; // cost,destinatie;

  fin >> n >> m;
  // indexam de la 1
  G.resize(n + 1);
  viz.resize(n + 1, false);
  // citire muchii
  for (int i = 0; i < m; i++) {
    int u, v, c;
    fin >> u >> v >> c;
    // ambele directii, ca e neorientat
    G[u].push_back({v, c});
    G[v].push_back({u, c});
  }

  // initializare

  // incepem de la un nod oarecare, il alegem pe 1
  viz[1] = true;
  // punem toate muchiile sale adiacente in PQ
  for (const auto &vecin : G[1]) {
    muchii_accesibile.push({1, vecin.first, vecin.second});
  }

  // cat timp mai avem muchii de procesat
  while (!muchii_accesibile.empty()) {
    // preia prima muchie (cea mai ieftina)
    Muchie curenta = muchii_accesibile.top();
    muchii_accesibile.pop();

    // muchia u->v
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
  fout << "cost total: " << cost_total << endl;
  fout << "avem " << mst.size() << " muchii in MST:" << endl;
  for (Muchie &m : mst) {
    fout << m.u << " " << m.v << "\n";
  }

  return 0;
}
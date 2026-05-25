#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct Muchie {
  int idx; // indexul muchiei, pt a fi usor sa facem viz[idx]
  int dest;
};

int n, m;

vector<vector<Muchie>> G; // liste de adiacenta
vector<bool> viz;
vector<int> sol;

void Hierholzer(int nod) {
  // cat timp mai are muchii de explorat
  while (!G[nod].empty()) {
    Muchie m = G[nod].back(); // luam ultima muchie din lista ramasa
    G[nod].pop_back();

    // daca nu a fost vizitata deja
    if (!viz[m.idx]) {
      // o vizitam
      viz[m.idx] = true;
      // daca o vizitam, inseamna ca intram in adancime
      Hierholzer(m.dest);
    }
  }

  // cand iese din while, inseamna ca ne-am blocat la acest nod
  // (nu mai sunt muchii nevizitate)
  // adaugam in solutie
  sol.push_back(nod);
}

int main() {

  ifstream fin("date.in");
  ofstream fout("date.out");

  fin >> n >> m;
  G.resize(n);
  viz.resize(n, false);
  for (int i = 0; i < m; i++) {
    int u, v;
    fin >> u >> v;
    G[u].push_back({i, v});
  }

  // pornim dintr-un nod oarecare
  Hierholzer(0);

  // afisam drumul stocat in sol
  for (int nod : sol) {
    fout << nod << " ";
  }
}
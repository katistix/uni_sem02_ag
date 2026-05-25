#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int n, m;
struct Muchie {
  int u, v;
  int cost;
};

vector<Muchie> muchii;
vector<Muchie> mst;

vector<int> parent; // vector de tati pentru DSU

int root(int x) {
  if (parent[x] == x)
    return x;
  parent[x] = root(parent[x]);
  return parent[x];
}

bool uneste(int a, int b) {
  int root_a = root(a);
  int root_b = root(b);

  // daca sunt in aceeasi componenta, nu le unim
  if (root_a == root_b)
    return false;

  // uneste
  parent[root_b] = root_a;
  return true;
}

int main() {
  ifstream fin("apm.in");
  ofstream fout("apm.out");

  fin >> n >> m;
  parent.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    fin >> u >> v >> c;
    muchii.push_back({u, v, c});
  }

  // sortam muchiile in functie de cost
  sort(muchii.begin(), muchii.end(),
       [](Muchie &a, Muchie &b) { return a.cost < b.cost; });

  // initializare vector de tati pentru DSU, initial fiecare e propriul sau
  // parinte
  for (int i = 1; i <= n; i++) {
    parent[i] = i;
  }

  // luam pe rand muchiile, ne asiguram sa nu formam cicluri
  int cost_total = 0;
  for (const auto &m : muchii) {
    if (uneste(m.u, m.v)) {
      mst.push_back(m);
      cost_total += m.cost;
    }
  }

  fout << cost_total << endl;
  fout << mst.size() << endl;
  for (const auto &m : mst) {
    fout << m.u << " " << m.v << endl;
  }

  return 0;
}
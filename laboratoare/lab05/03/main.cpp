#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int N, M;

struct Muchie {
  int dest;
  int idx; // indexul muchiei, pt a putea usor sa o cautam in viz[]
};

vector<bool> viz; // vector cu muchii vizitate
vector<vector<Muchie>> G;
vector<int> sol;

void Euler(int nod) {
  // cat timp nodul mai are muchii de explorat
  while (!G[nod].empty()) {
    Muchie m = G[nod].back();
    G[nod].pop_back(); // eliminam muchia ca sa nu o mai parcurgem in viitor

    // daca muchia nu a fost vizitata deja din sens opus
    if (!viz[m.idx]) {
      // marcam muchia ca vizitata
      viz[m.idx] = true;
      // parcurgem muchia, in adancime
      Euler(m.dest);
    }
  }

  // cand while se termina, ne-am blocat in nodul `nod`
  // Hierholzer => adaugam `nod` la solutie
  sol.push_back(nod);
}

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  fin >> N >> M;

  G.resize(N);
  viz.resize(M);

  // citire muchii
  int x, y;
  for (int i = 0; i < M; i++) {
    fin >> x >> y;
    G[x].push_back({y, i});
    G[y].push_back({x, i});
  }

  Euler(0); // calculam solutia

  // afisare
  for (int nod : sol) {
    fout << nod << " ";
  }

  return 0;
}
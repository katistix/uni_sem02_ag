#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n; // numarul de noduri
int m; // numarul de muchii

vector<int> h;
vector<int> e;
queue<int> Q; // coada cu nodurile care au exces

struct Muchie {
  int dest;
  int cap;
  int idx_inversa;
};

// liste de adiacenta
vector<vector<Muchie>> G;

int main() {

  ifstream fin("date.in");
  ofstream fout("date.out");

  fin >> n >> m;
  h.resize(n);
  e.resize(n);
  G.resize(n);

  // citire graf
  for (int i = 0; i < m; i++) {
    int x, y, c;
    fin >> x >> y >> c;

    // punem muchia directa
    G[x].push_back({y, c, (int)G[y].size()});
    // punem muchia inversa
    G[y].push_back({x, 0, (int)G[x].size() - 1});
  }

  // PREFLUX
  h[0] = n; // punem sursa pe nivelul N
  for (Muchie &m : G[0]) {
    int v = m.dest;
    e[v] += m.cap;
    // muchia inversa, in caz ca vrem sa intoarcem
    G[v][m.idx_inversa].cap += m.cap;
    //
    m.cap = 0;

    // punem toate care au exces in coada
    // ignoram destinatia
    if (v != n - 1) {
      Q.push(v);
    }
  }

  // POMPARE+INALTARE

  // procesam toata coada
  while (!Q.empty()) {
    int u = Q.front(); // nodul curent de procesat
    Q.pop();

    // POMPARE
    // incercam sa pompam catre toti vecinii
    for (Muchie &m : G[u]) {
      int v = m.dest;
      // daca e:
      // downhill, daca mai e loc, u mai are exces
      if (h[u] > h[v] && m.cap > 0 && e[u] > 0) {
        // trimitem pe muchia asta cat putem
        int de_trimis = min(e[u], m.cap);

        // daca v nu avea exces inainte, si acum v-a avea, il bagam in coada
        // ignoram sursa si destinatia
        if (e[v] == 0 && v != 0 && v != n - 1) {
          Q.push(v);
        }

        // mutam apa din u in v
        e[u] -= de_trimis;
        e[v] += de_trimis;

        // actualizam capacitatile (graful rezidual)
        m.cap -= de_trimis; // avem mai putin loc de trimis pe conducata asta
                            // (sau 0 daca min(m.cap,e[u])==m.cap)
        G[v][m.idx_inversa].cap +=
            de_trimis; // ne asiguram ca putem sa trimitem inapoi
      }
    }

    // INALTARE
    // daca si dupa ce am pompat, in u inca exista exces,
    // trebuie sa-l inaltam, deci gasim cel mai jos vecin si il ducem pe u
    // deasupra lui
    if (e[u] > 0) {
      Q.push(u); // u are inca exces, il punem inapoi in coada

      int minn = 1e9;

      for (Muchie &m : G[u]) {
        // ignoram ce nu are capacitate
        if (m.cap == 0)
          continue;

        minn = min(minn, h[m.dest]);
      }

      h[u] = minn + 1;
    }
  }

  // cand coada de procesare e gata, fluxul maxim este in excesul lui N-1
  fout << e[n - 1] << "\n";

  return 0;
}
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// o muchie in lista de adiacenta
struct Muchie {
  int to;      // nodul destinatie
  int cap;     // capacitatea reziduala curenta a muchiei
  int rev_idx; // indexul muchiei inverse in lista nodului 'to'
};

int N, M;
vector<Muchie> G[1005]; // listele de adiacenta

int parinte_nod[1005];    // pt a retine nodul parinte in BFS
int parinte_muchie[1005]; // pt a retine indexul muchiei din lista
                          // parintelui

// adauga o muchie si muchia sa inversa
void adauga_muchie(int u, int v, int c) {
  G[u].push_back({v, c, (int)G[v].size()});
  G[v].push_back({u, 0, (int)G[u].size() - 1});
}

bool BFS(int s, int d) {
  vector<bool> viz(N, false);
  queue<int> Q;

  Q.push(s);
  viz[s] = true;

  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();

    // Iteram doar prin vecinii nodului u
    for (int i = 0; i < G[u].size(); i++) {
      int v = G[u][i].to;
      int capacitate_reziduala = G[u][i].cap;

      // Daca nu e vizitat si avem capacitate disponibila pe muchie
      if (!viz[v] && capacitate_reziduala > 0) {
        viz[v] = true;
        parinte_nod[v] = u;
        parinte_muchie[v] =
            i; // Retinem pozitia muchiei pentru update mai tarziu

        Q.push(v);

        // Optimizare: daca am atins destinatia, ne oprim din cautat
        if (v == d) {
          return true;
        }
      }
    }
  }

  return viz[d];
}

int FF(int s, int d) {
  int flux_maxim = 0;

  // cat timp gasim un drum de crestere
  while (BFS(s, d)) {
    int flux_curent = INT_MAX;
    int v;

    // gaseste cap minima din drumul curent
    v = d; // parcurgem lantul de la dest la sursa
    while (v != s) {
      int u = parinte_nod[v];
      int idx = parinte_muchie[v]; // indexul muchiei u -> v

      // update cap minima
      flux_curent = min(flux_curent, G[u][idx].cap);
      v = u; // go up the chain
    }

    // actualizam cap rez pt muchiile directe si inverse
    v = d; // aceeasi parcurgere
    while (v != s) {
      int u = parinte_nod[v];
      int idx = parinte_muchie[v];     // indexul muchiei u -> v
      int rev_idx = G[u][idx].rev_idx; // indexul muchiei v -> u

      G[u][idx].cap -= flux_curent;     // scadem de pe muchia directa
      G[v][rev_idx].cap += flux_curent; // adaugam pe muchia inversa

      v = u;
    }

    flux_maxim += flux_curent;
  }

  return flux_maxim;
}

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  fin >> N >> M;

  // citim muchiile
  for (int i = 0; i < M; i++) {
    int x, y, c;
    fin >> x >> y >> c;
    adauga_muchie(x, y, c);
  }

  // rezolvam
  int sol = FF(0, N - 1);
  fout << sol;

  return 0;
}
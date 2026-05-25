#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
#define INF 1e9

using namespace std;

// matrice de adiacenta
int G[105][105];
int n, m;

bool bfs(int sursa, int destinatie, vector<int> &drum) {

  // facem clear la drum
  fill(drum.begin(), drum.end(), -1);

  queue<int> Q;
  // punem sursa
  Q.push(sursa);
  drum[sursa] = sursa;

  while (!Q.empty()) {
    // luam nodul din varful cozii
    int nod = Q.front();
    Q.pop();

    // adaugam toti vecinii lui nevizitati si care mai au capacitate directa
    // (reziduala)
    for (int i = 0; i < n; i++) {
      // drum[i]==-1 => (nevizitat)
      if (drum[i] == -1 && G[nod][i] > 0) {
        drum[i] = nod;       // am ajuns in i din nod
        if (i == destinatie) // daca am ajuns la destinatie, exista un drum
          return true;

        Q.push(i); // continua cautarea
      }
    }
  }

  return false; // daca am ajuns aici, nu am mai gasit un drum bun
}

int edmondsKarp(int sursa, int destinatie) {
  int flux_maxim = 0;

  vector<int> drum; // traseul drumului curent
  drum.resize(n);

  // cat timp bfs gaseste un drum valid de la sursa la destinatie
  while (bfs(sursa, destinatie, drum)) {
    // gasim capacitatea minima pe drumul curent

    int cap_min = INF;

    // parcurgem drumul de la final
    int v = destinatie;
    while (v != sursa) {
      int u = drum[v]; // nodul precedent, deci suntem la muchia u->v
      if (cap_min > G[u][v])
        cap_min = G[u][v];
      // progress
      v = u;
    }

    // actualizam reteaua reziduala pe drum
    // mai parcurgem drumul o data
    v = destinatie;
    while (v != sursa) {
      int u = drum[v];
      // scade capacitatea pe drumul direct
      G[u][v] -= cap_min;
      // creste capacitatea pe drumul invers
      G[v][u] += cap_min;
      v = u;
    }

    flux_maxim += cap_min; // actualizam fluxul maxim
  }

  return flux_maxim;
}

int main() {
  ifstream fin("date.in");
  ofstream fout("date.out");

  // citire
  fin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, c;
    fin >> u >> v >> c;
    G[u][v] = c;
  }

  int sursa = 0;
  int destinatie = n - 1;

  fout << edmondsKarp(sursa, destinatie) << endl;

  return 0;
}
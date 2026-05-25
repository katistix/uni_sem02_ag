#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m, e;

int G[105][105];

bool bfs(int sursa, int destinatia, vector<int> &parent) {
  // clear drum
  fill(parent.begin(), parent.end(), -1);

  queue<int> Q;
  Q.push(sursa);
  parent[sursa] = sursa;

  while (!Q.empty()) {
    int nod = Q.front();
    Q.pop();

    // adaugam in coada toti vecinii nevizitati
    // este vecin doar daca exista o muchie cu cap>0 catre el
    // daca nu are parent, inseamna ca nu este vizitat in drumul curent
    for (int i = 0; i <= n + m + 1; i++) {
      if (G[nod][i] > 0 && parent[i] == -1) {
        parent[i] = nod; // am ajuns in i prin nod
        // daca am ajuns la destinatie inseamna ca exista un drum
        if (i == destinatia) {
          return true;
        }
        Q.push(i);
      }
    }
  }

  // nu am gasit drum
  return false;
}

int edmondsKarp(int sursa, int destinatie) {
  int flux_maxim = 0;

  // drumul curent definit printr-un lant de parinti
  vector<int> parent;
  parent.resize(n + m + 2);

  // cat timp mai avem drumuri valide de la sursa la destinatie
  while (bfs(sursa, destinatie, parent)) {
    // stim ca bottleneck-ul e 1, toate capacitatile sunt 1
    // actualizam reteaua reziduala
    int nod = destinatie;
    while (nod != sursa) {
      G[parent[nod]][nod] -= 1; // pe directa scade capacitatea
      G[nod][parent[nod]] += 1; // pe inversa creste capacitatea
      nod = parent[nod];        // next
    }

    flux_maxim++; // crestem fluxul maxim
  }

  return flux_maxim;
}

int main() {
  ifstream fin("date.in");
  ofstream fout("date.out");

  fin >> n >> m >> e;
  for (int i = 0; i < e; i++) {
    int u, v;
    fin >> u >> v;

    // avem muchie de la u la v
    G[u][n + v] = 1;
  }

  // adaugam nod virtual sursa pana la toate 1,N noduri
  for (int i = 1; i <= n; i++) {
    G[0][i] = 1;
  }

  // adaugam nod virtual de la toate din R catre destinatie
  for (int i = n + 1; i <= n + m; i++) {
    G[i][n + m + 1] = 1;
  }

  // compute maximum flow
  fout << edmondsKarp(0, n + m + 1) << endl;
}
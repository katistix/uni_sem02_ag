#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int n, m;
int G[101][101];

int grade[101];
int culoare[101];
int culoare_curenta = 0;
vector<pair<int, int>> noduri_sortate;

void COLORARE() {
  // parcurgem lista de noduri sortate
  for (int i = 0; i < n; i++) {
    int nod = noduri_sortate[i].second;
    // daca nodul a fost deja colorat intr-un pas anterior
    if (culoare[nod] != -1) {
      continue;
    }

    // il coloram
    culoare[nod] = culoare_curenta;

    // cautam alte noduri necolorate din restul listei care
    // pot sa primeasca aceeasi culoare
    for (int j = i + 1; j < n; j++) {
      int next = noduri_sortate[j].second;

      if (culoare[next] != -1) {
        continue;
      }

      // verificam daca are vecini colorati cu culoare_curenta
      bool vecin = false;
      for (int k = 0; k < n; k++) {
        if (G[next][k] == 1 && culoare[k] == culoare_curenta) {
          vecin = true;
          break;
        }
      }
      // daca nu are vecini colorati cu culoare_curenta, il putem colora
      if (!vecin) {
        culoare[next] = culoare_curenta;
      }
    }

    // trecem la urmatoarea culoare
    culoare_curenta++;
  }
}

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  // citire in matrice de adiacenta
  fin >> n >> m;
  int x, y;
  for (int i = 0; i < m; i++) {
    fin >> x >> y;
    G[x][y] = 1;
    G[y][x] = 1;

    // calculam si gradele direct
    grade[x]++;
    grade[y]++;
  }

  // sortam nodurile in functie de grade
  for (int i = 0; i < n; i++) {
    noduri_sortate.push_back({grade[i], i});
  }
  sort(noduri_sortate.begin(), noduri_sortate.end(), greater<pair<int, int>>());

  // coloram greedy
  for (int i = 0; i < n; i++) {
    culoare[i] = -1;
  }

  COLORARE();

  // afisare
  fout << culoare_curenta << "\n";

  for (int i = 0; i < n; i++) {
    fout << culoare[i] << " ";
  }
}
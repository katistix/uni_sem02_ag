#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, M;
vector<int> h; // inaltimile nodurilor
vector<int> e; // excesul din noduri

queue<int> Q; // coada cu nodurile care au exces

struct Muchie {
  int dest;
  int cap;
  int idx_inversa; // index muchia inversa
};

vector<vector<Muchie>> G;

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  fin >> N >> M;
  h.resize(N);
  e.resize(N);
  G.resize(N);

  // citim muchiile, construim graful rezidual
  int x, y, c;
  for (int i = 0; i < M; i++) {
    fin >> x >> y >> c;
    // adaugam muchia directa
    G[x].push_back({y, c, (int)G[y].size()});
    // adaugam muchia inversa
    G[y].push_back({x, 0, (int)G[x].size() - 1});
  }

  // initializare (pre-flux)
  h[0] = N; // nodul sursa primeste inaltimea maxima
  // inundam reteaua, trimitem tot fluxul posibil pe muchiile directe din sursa
  for (Muchie &m : G[0]) {
    int v = m.dest;                   // vecinul
    e[v] += m.cap;                    // creste excesul lui v
    G[v][m.idx_inversa].cap += m.cap; // creste capacitatea muchiei inverse
    m.cap = 0; // cap muchiei directe devine 0, (m este referinta)

    // vecinul v este "activ" (are exces), deci il punem in coada
    // ignoram destinatia
    if (v != N - 1) {
      Q.push(v);
    }
  }

  // cat timp avem noduri cu exces (in coada), facem pomparea
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();

    // 1. POMPARE
    // incercam sa pompam catre toti vecinii lui u
    for (Muchie &m : G[u]) {
      int v = m.dest;

      // daca nivelul lui u e mai sus, avem spatiu pe conducta si
      // u inca are exces
      if (h[u] > h[v] && m.cap > 0 && e[u] > 0) {
        int volum_pompat = min(m.cap, e[u]);

        // daca v nu avea deloc apa inainte, inseamna ca nu e in coada.
        // il adaugam acum, inainte sa ii crestem excesul
        if (e[v] == 0 && v != 0 && v != N - 1) {
          Q.push(v);
        }

        // actualizam excesul (apa mutata de la u la v)
        e[u] -= volum_pompat;
        e[v] += volum_pompat;

        // actualizam capacitatile (graful rezidual)
        m.cap -= volum_pompat;
        G[v][m.idx_inversa].cap += volum_pompat;
      }
    }

    // 2. INALTARE
    // daca am incercat toti vecinii dar u a ramas blocat cu exces de apa,
    // trebuie sa il ridicam la un nivel mai mare decat cel mai de jos vecin
    // disponibil
    if (e[u] > 0) {
      int inaltime_minima = INT_MAX; // infinit

      // vedem care e cel mai jos vecin al lui u
      for (Muchie &m : G[u]) {
        // ne uitam doar la vecinii catre care avem tevi cu spatiu,
        // la restul nu are sens
        if (m.cap > 0) {
          inaltime_minima = min(inaltime_minima, h[m.dest]);
        }
      }

      // ridicam nodul cu un nivel mai sus decat cel mai jos vecin
      h[u] = inaltime_minima + 1;

      // deoarece u inca are exces, il punem inapoi in coada pt a fi
      // procesat din nou
      Q.push(u);
    }
  }

  // loop-ul de pompare-inaltare e gata,
  // fluxul maxim se afla in excesul lui N-1
  fout << e[N - 1] << "\n";

  return 0;
}
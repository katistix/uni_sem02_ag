#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n;

vector<int> parents;
vector<int> children_count;

int main() {
  ifstream fin("date.in");
  ofstream fout("date.out");

  fin >> n;
  parents.resize(n);
  children_count.resize(n, 0);

  // citire arbore
  int x;
  for (int i = 0; i < n; i++) {
    fin >> x;
    parents[i] = x;
    // daca nu e radacina, creste numarul de copii ai parintelui
    if (x != -1) {
      children_count[x]++;
    }
  }

  // folosim un priority queue, pentru a ordona frunzele dupa label
  priority_queue<int, vector<int>, greater<int>> PQ;
  // punem initial in PQ toate frunzele initiale
  for (int i = 0; i < n; i++) {
    if (children_count[i] == 0) {
      PQ.push(i);
    }
  }

  vector<int> solutie; // vectorul solutie, codarea prufer

  // tot luam frunza cu cel mai mic label, si o punem in solutie
  // cand luam frunza, o eliminam din arbore ->
  // numarul de fii ai parintelui ei scade, eventual parintele devine frunza

  // facem asta pana cand in solutie avem n-2 elemente
  while (solutie.size() < n - 2) {
    int frunza = PQ.top();
    PQ.pop();

    int p = parents[frunza];
    if (p == -1)
      continue;

    solutie.push_back(p); // punem parintele frunzei in solutie

    // scade numarul de fii ai parintelui frunzei
    children_count[p]--;

    // daca parintele nu mai are fii, inseamna ca a devenit frunza
    if (children_count[p] == 0) {
      PQ.push(p);
    }
  }

  // cand nu mai avem elemente in PQ, am terminat de procesat tot
  // afisam solutia
  fout << solutie.size() << '\n';
  for (int x : solutie) {
    fout << x << ' ';
  }

  fin.close();
  fout.close();
}
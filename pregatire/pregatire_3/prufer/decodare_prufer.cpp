#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int n, m;

vector<int> cod;
vector<int> children_count;
vector<int> parents;

int main() {

  ifstream fin("decodare.in");
  ofstream fout("decodare.out");

  fin >> m;
  n = m + 2; // noduri in arbore

  children_count.resize(n);
  parents.resize(n);

  fill(children_count.begin(), children_count.end(), 0);

  // citim codul
  for (int i = 0; i < m; i++) {
    int x;
    fin >> x;
    cod.push_back(x);

    // numaram fii, ca sa stim care sunt frunzele
    // are atatia fii de care ori apare in codare
    children_count[x]++;
  }

  // avem un PQ cu noduri la care nu cunoastem parintele
  // initial in PQ punem frunzele
  priority_queue<int, vector<int>, greater<int>> PQ;
  for (int i = 0; i < n; i++) {
    if (children_count[i] == 0) {
      PQ.push(i);
    }
  }

  // parcurgem codarea, stim ca cel mai mic nod din PQ este fiu al nodului
  // curent din codare
  for (int i = 0; i < m; i++) {
    int p = cod[i];
    int nod = PQ.top();
    PQ.pop();

    // p -> nod (p este parintele lui nod)
    parents[nod] = p;

    // scade numarul de fii neprocesati ai lui p
    children_count[p]--;

    // daca p nu mai are fii neprocesati, inseamna ca el trebuie procesat in
    // continuare
    if (children_count[p] == 0) {
      PQ.push(p);
    }
  }

  // la final mai avem in PQ 2 noduri, consideram ca ultimul este parentul
  // primului
  int prim = PQ.top();
  PQ.pop();
  int ultim = PQ.top();
  PQ.pop();

  parents[prim] = ultim;
  // ultimul il consideram si radacina arborelui
  parents[ultim] = -1;

  // afisare rezultat
  fout << n << "\n";
  for (int i = 0; i < n; i++) {
    fout << parents[i] << " ";
  }

  return 0;
}
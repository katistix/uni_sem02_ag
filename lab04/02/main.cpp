#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int M;

vector<int> code;
vector<int> children; // nr de fii pe care ii are un nod
vector<int> parents;

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  fin >> M;
  int N = M + 1; // noduri in arbore

  children.resize(N);
  parents.resize(N);
  fill(children.begin(), children.end(), 0); // initial toti au 0 fii
  fill(parents.begin(), parents.end(), -1);

  int x;
  for (int i = 0; i < M; i++) {
    fin >> x;
    code.push_back(x);

    // numaram fii, un nod are atatia fii de cate ori apare in codare
    children[x]++;
  }

  // punem in PQ toate frunzele (nodurile fara copii)
  priority_queue<int, vector<int>, greater<int>> PQ;
  for (int i = 0; i < N; i++) {
    if (children[i] == 0) // e frunza
      PQ.push(i);
  }

  // pentru fiecare numar din codare, stim sigur ca cea mai mica frunza
  // din PQ de la acel moment e fiul numarului din codare.
  for (int i = 0; i < M; i++) {
    int x = code[i];
    int f = PQ.top();
    PQ.pop();

    // stim sigur ca x este parent-ul lui f
    parents[f] = x;
    // scade numarul de fii pe care ii are x
    children[x]--;

    // daca acum x nu mai are copii de procesat, devine frunza
    if (children[x] == 0) {
      PQ.push(x);
    }
  }

  // am procesat M valori, inseamna ca in PQ a mai ramas un nod neprocesat
  // acesta este radacina arborelui
  int root = PQ.top();
  PQ.pop();
  parents[root] = -1;

  // afisare
  fout << N << "\n";
  for (int i = 0; i < N; i++) {
    fout << parents[i] << " ";
  }

  return 0;
}
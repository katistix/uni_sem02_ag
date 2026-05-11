#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N;
vector<int> parents;

// numarul de copii pe care il are [i]
vector<int> children;

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  fin >> N;
  parents.resize(N);
  children.resize(N);
  fill(parents.begin(), parents.end(), 0);
  fill(children.begin(), children.end(), 0);

  // citire arbore
  for (int i = 0; i < N; i++) {
    int x;
    fin >> x;
    parents[i] = x; // notam care e parentul lui x

    // daca nu e radacina, crestem contorul de copii pentru parinte
    if (x != -1) {
      children[x]++; // ca sa stim cati copii are x
    }
  }

  vector<int> solution;

  // avem un PQ cu frunzele in ordine crescatoare
  priority_queue<int, vector<int>, greater<int>> PQ;

  // bagam toate frunzele in PQ
  for (int i = 0; i < N; i++) {
    if (children[i] == 0) {
      PQ.push(i);
    }
  }

  // cat timp avem elemente in coada (avem frunze) le procesam
  while (!PQ.empty()) {
    int f = PQ.top();
    PQ.pop();

    int p = parents[f];

    // verificam ca p sa nu fie radacina
    if (p == -1)
      continue;

    // punem parintele lui f in codare
    solution.push_back(p);
    // eliminam frunza curenta (cea minima) prin a scadea numarul de fii ai
    // parintelui
    children[p]--;

    // daca parintele p nu mai are fii, atunci devine frunza si il introducem in
    // PQ O(log n)
    if (children[p] == 0) {
      PQ.push(p);
    }
  }

  fout << solution.size() << "\n";
  for (int x : solution) {
    fout << x << " ";
  }

  fin.close();
  fout.close();
}
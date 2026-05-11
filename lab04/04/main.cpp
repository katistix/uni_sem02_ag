#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Nod {
  int freq;
  char min_ascii;
  Nod *left, *right; // referinte catre standa si dreapta

  // constructor sa fie mai usor sa facem un nod nou
  Nod(int f, char c) : freq(f), min_ascii(c), left(nullptr), right(nullptr) {}
};

// structura de comparare pentru PQ
struct Compare {
  bool operator()(Nod *a, Nod *b) {
    if (a->freq != b->freq) {
      return a->freq > b->freq; // frecventa cea mai mica
    }

    // daca sunt egale, atunci comparam in functie de ascii
    return a->min_ascii > b->min_ascii;
  }
};

int N;

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  fin >> N;
  fin.get(); // sarim peste newline-ul de dupa N

  // reconstruim arborele huffman
  char ch;
  int frv;
  priority_queue<Nod *, vector<Nod *>, Compare> PQ;
  for (int i = 0; i < N; i++) {
    fin.get(ch);
    fin.get(); // sarim peste spatiul de dupa caracter

    fin >> frv;
    fin.get(); // sarim peste spatiul de dupa frecventa

    Nod *nod = new Nod(frv, ch);
    PQ.push(nod);
  }

  // legam nodurile (exact ca la codare)
  while (PQ.size() > 1) {
    // st<dr
    Nod *st = PQ.top();
    PQ.pop();
    Nod *dr = PQ.top();
    PQ.pop();

    // calculam caracterul ascii minim din subarbore
    char min_ascii = min(st->min_ascii, dr->min_ascii);

    // avem un nou nod care le leaga pe cele doua
    Nod *p = new Nod(st->freq + dr->freq, min_ascii);

    // legam noul nod de fii
    p->left = st;
    p->right = dr;

    // punem noul nod in PQ
    PQ.push(p);
  }

  // ultimul nod ramas in PQ este radacina
  Nod *radacina = PQ.top(); // incepem cu radacina
  PQ.pop();

  // citim sirul de "biti" si parcurgem arborele
  string cod;
  fin >> cod;
  string text = "";

  Nod *curent = radacina; // pornim de la radacina
  for (int i = 0; i < cod.size(); i++) {

    // stanga sau dreapta in functie de cod
    if (cod[i] == '0') {
      curent = curent->left;
    } else {
      curent = curent->right;
    }

    // parcurgem stanga dreapta pana ajungem la o frunza
    // cand e frunza, ii adaugam valoarea in textul final
    if (curent->left == nullptr && curent->right == nullptr) {
      // curent este frunza
      text += curent->min_ascii;

      curent = radacina; // resetam "curent"
    }
  }

  fout << text;

  return 0;
}
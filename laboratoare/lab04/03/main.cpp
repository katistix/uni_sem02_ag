#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int freq[256]; // vector de frecventa pt fiecare caracter ascii

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

map<char, string> huffman_map;

void genereazaCoduri(Nod *radacina, string cod_curent) {
  if (!radacina)
    return;

  // daca am ajuns la o frunza, ii salvam codul curent in map
  if (!radacina->left && !radacina->right) {
    huffman_map[(char)radacina->min_ascii] = cod_curent;
    return;
  }

  // DFS pe stanga si dreapta
  genereazaCoduri(radacina->left,
                  cod_curent + "0"); // stanga adauga un 0 la cod
  genereazaCoduri(radacina->right, cod_curent + "1");
}

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  int caractere_totale = 0;
  string text = "";
  char ch;
  while (fin.get(ch)) {
    text += ch;
  }

  // calculam frecventa fiecarui caracter
  for (int i = 0; i < text.size(); i++) {
    ch = text[i];
    freq[ch]++;
  }

  // folosim un PQ pentru noduri,
  // le sortam in functie de relatia de ordine din cerinta
  priority_queue<Nod *, vector<Nod *>, Compare> PQ;

  // punem in PQ toate caracterele care apar in text
  for (int i = 0; i <= 255; i++) {
    if (freq[i] > 0) {
      caractere_totale++;
      // formam un nod frunza pentru caracterul curent
      Nod *f = new Nod(freq[i], char(i));
      PQ.push(f);
    }
  }

  // construim arborele binar cu cate doua noduri din coada
  // cat timp avem minim 2 elemente in coada
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

  // in PQ mai ramane un nod, acesta este radacina
  Nod *radacina = PQ.top();
  PQ.pop();

  // avem arborele binar format sub forma de noduri inlantuite
  // acum trebuie sa generam codul prin parcurgere DFS,
  // si formam tabelul huffman

  genereazaCoduri(radacina, "");

  // afisare
  fout << caractere_totale << "\n";
  // afisam fiecare caracter si frecventa lui
  for (int i = 0; i < 256; i++) {
    if (freq[i] > 0) {
      fout << (char)i << " " << freq[i] << "\n";
    }
  }
  // afisam textul tradus folosind map-ul huffman
  for (char c : text) {
    fout << huffman_map[c];
  }

  return 0;
}
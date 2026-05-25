#include <cstddef>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
  char ch;
  int freq;
  Node *left;
  Node *right;

  Node(int f, Node *l, Node *r) {
    ch = '\0'; // sau orice caracter dummy
    freq = f;
    left = l;
    right = r;
  }
};

unordered_map<char, int> freq;
unordered_map<char, string> huffmanCodes;

struct CompCharFreq {
  // vrem descrescator
  bool operator()(Node *left, Node *right) { return left->freq > right->freq; }
};

void generateCodes(Node *root, string str) {
  if (root == nullptr) {
    return;
  }

  // daca este frunza
  if (root->left == nullptr && root->right == nullptr) {
    huffmanCodes[root->ch] = str;
  }

  // parcurgem in adancime
  generateCodes(root->left, str + "0");  // stanga inseamna 0
  generateCodes(root->right, str + "1"); // dreapta inseamna 1
}

Node *generateHuffman() {
  // adaugam in PQ nodurile literelor de procesat
  priority_queue<Node *, vector<Node *>, CompCharFreq> PQ;
  for (const auto &el : freq) {
    int frecv = el.second;
    char caracter = el.first;
    Node *newNode = new Node(frecv, nullptr, nullptr);
    newNode->ch = caracter;
    PQ.push(newNode);
  }

  // procesam cate doua noduri din PQ
  while (PQ.size() > 1) {
    Node *nod1 = PQ.top();
    PQ.pop();
    Node *nod2 = PQ.top();
    PQ.pop();

    // avem un nod nou care le leaga pe cele doua
    Node *newNode = new Node(nod1->freq + nod2->freq, nod1, nod2);

    PQ.push(newNode);
  }

  // ultimul nod ramas este radacina
  Node *radacina = PQ.top();

  return radacina;
}

string encode(string original) {
  string result = "";
  for (char &c : original) {
    result += huffmanCodes[c];
  }
  return result;
}

string decode(Node *root, string str) {
  Node *curent = root;
  string decoded = "";
  // traverse the tree
  for (const char &c : str) {
    if (c == '0') {
      curent = curent->left;
    } else {
      curent = curent->right;
    }

    // daca am ajuns la o frunza, avem un caracter
    if (curent->left == nullptr && curent->right == nullptr) {
      decoded += curent->ch;
      curent = root; // reset inapoi sus, pentru urmatorul caracter
    }
  }

  return decoded;
}

int main() {

  ifstream fin("date.in");
  ofstream fout("date.out");

  string original_text;
  getline(fin, original_text);

  cout << original_text << endl;

  // build freq map
  for (char &c : original_text) {
    freq[c]++;
  }

  Node *huffmanRoot = generateHuffman();
  generateCodes(huffmanRoot, "");

  // afisam codificarea
  cout << encode(original_text) << endl;
  string encoded = encode(original_text);

  // decodam
  cout << decode(huffmanRoot, encoded) << endl;

  return 0;
}
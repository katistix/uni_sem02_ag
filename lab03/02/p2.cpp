/*
folosim algoritmul lui johnson.

liste de adiacenta

bellman-ford (cu sursa un nod extra care are arc de cost 0 catre fiecare alt nod)
    - detectam cicluri de cost negativ
    - calculam "potentiala" `h`

dijkstra cu fiecare nod ca sursa (folosind potentiala pt costuri)
    - pt fiecare nod luat ca sursa, calculam distanta lui la alte noduri (distanta modificata cu potentiala)

readucem distantele.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>


using namespace std;

const int INF = 1e8;
int n, m;


vector<vector<pair<int, int>>> G; // listele de adiacenta
vector<int> h; // potentiala nodurilor, calculata cu bellman-ford

// bellman-ford
bool compute_h(){

    // initial distantele sunt INF
    // vector<int> h(n+1, INF); // consideram nodul n+1 ca fiind cel adaugat extra
    // // indexare de la 0
    // h[n] = 0;

    // adaugam in graf nodul special
    // G.resize(n+1);
    // for(int i=0;i<n;i++){
    //     G[n].push_back(make_pair(i,0)); // special --0--> i 
    // }

    // deoarece adaugam un nod sursa "virtual" care are arc de cost 0 catre toate celelalte noduri,
    // putem sa consideram ca toate distantele incep de la 0,
    // iar rezultatul v-a reprezenta functia "potentiala" h a nodurilor.

    // initializare h
    h.resize(n, 0);



    // facem n parcurgeri,
    // daca la ultima inca facem modificari,
    // atunci exista ciclu de cost negativ
    for (int iter = 1; iter <= n; iter++)
    {
        bool modified = 0; // pt optimizare


        // desi e for in for, o sa se faca exact m pasi.
        // (numarul de muchii)
        // teoretic se putea face cu lista de muchii nu cu lista de adiacenta
        for (int i = 0; i < n; i++)
        {        
            // Parcurgem toate muchiile care pleaca din i
            for(auto muchie: G[i]){
                int x = i, y=muchie.first, cost=muchie.second;

                // daca nu stim cum sa ajungem la acel nod, skip
                // if(h[x] == INF) continue; 
                // !! dar deoarece am adaugat un nod sursa virtual care are arc de cost 0 catre toate celelalte noduri,
                // toate nodurile sunt accesibile, deci nu e nevoie de acest check

                // daca prin muchia curenta putem sa ajungem mai ieftin
                // relax
                if(h[x]+cost < h[y]){
                    h[y]=h[x]+cost;
                    modified=1;

                    // daca la ultima parcurgere inca se fac "relaxari"
                    // atunci exista ciclu de cost negativ
                    if(iter == n){
                        return false; // false = exista ciclu negativ
                    }
                }
            }
        }

        // daca nu s-a modificat nimic, putem sa ne oprim mai devreme
        if(!modified) break;
    }

    return true; // true = nu exista ciclu negativ, h contine potentiala nodurilor
}

// dijkstra
vector<int> dijkstra(int source){

    // distantele modificate (cu potentiala)
    vector<int> dist(n, INF);
    dist[source] = 0;

    // implementare cu coada de prioritati
    // (cost, nod)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    // adaugam nodul sursa in coada, cu distanta 0
    pq.push({0, source});

    // cat timp mai avem noduri de procesat
    while(!pq.empty()){
        // luam nodul cel mai apropiat (cu distanta modificata cea mai mica)
        auto top = pq.top();
        pq.pop();

        int cost = top.first;
        int node = top.second;

        // daca am ajuns la un nod cu o distanta mai mare decat cea deja calculata, skip
        // nu se mai face relaxarea muchiilor
        if(cost > dist[node]) continue;

        // parcurgem toate muchiile care pleaca din nod
        for(auto muchie: G[node]){
            int next = muchie.first;
            int cost_next = muchie.second;

            // calculam costul modificat al muchiei (cu potentiala)
            // folosind algoritmul lui johnson, costul modificat al unei muchii (u,v) este:
            // cost(u,v) + h(u) - h(v)
            int modified_cost = cost_next + h[node] - h[next];

            // daca putem sa ajungem mai ieftin la next prin nod
            if(dist[node] + modified_cost < dist[next]){
                dist[next] = dist[node] + modified_cost; // actualizam distanta modificata la next
                pq.push({dist[next], next}); // adaugam next in coada cu distanta modificata
            }
        }
    }

    return dist; // returnam vectorul de distante modificate de la sursa la toate celelalte noduri

}



// johnson
using Johnson_result = pair<bool, vector<vector<int>>>; // {true, {...}} sau {false, whatever}
Johnson_result johnson(){

    vector<vector<int>> distante_finale(n, vector<int>(n, INF)); // matricea de distante finale

    // 1. calculam h cu bellman-ford
    bool am_calculat_h = compute_h();

    if(!am_calculat_h){
        // exista ciclu de cost negativ, deci nu putem calcula distantele
        return {false, {}}; // false = exista ciclu negativ
    }

    // o pasam in dijkstra pentru a calcula rapid distantele dintre toate nodurile
    // folosind h pentru a modifica costurile ca sa fie toate pozitive

    // aplicam dijkstra pentru fiecare nod ca sursa
    for(int source = 0; source < n; source++){
        vector<int> dist = dijkstra(source); // vectorul de distante (modificate) de la sursa la toate celelalte noduri

        // readucem distantele la forma initiala
        for(int i = 0; i < n; i++){
            if(dist[i] != INF){
                // folosind algoritmul lui johnson, distanta reala de la sursa la i este:
                // distanta modificata + h(i) - h(sursa)
                dist[i] = dist[i] + h[i] - h[source];
            }
        }

        // acum dist[i] reprezinta distanta reala de la sursa la i
        distante_finale[source] = dist; // salvam distanta finala in matricea de distante
    }

    return {true, distante_finale}; // true = nu exista ciclu negativ, distantele sunt in distante_finale
}

int main(int argc,char* argv[]){

    ifstream fin(argv[1]);
    ofstream fout(argv[2]);


    // citire
    fin >> n >> m;
    G.resize(n); // redimensionam lista de adiacenta pentru n noduri

    int x,y,w;
    for (int i = 0; i < m; i++)
    {
        fin >> x >> y >> w;
        G[x].push_back({y, w}); // adaugam muchia (x,y) cu costul w
    }

    // aplicam algoritmul lui johnson
    Johnson_result result = johnson();

    // afisare
    if(!result.first){
        fout << -1; // afisam -1 daca exista ciclu de cost negativ, deci nu putem calcula distantele
    } else {
        vector<vector<int>> distante = result.second;

        // primele M linii contine muchiile modificate



        for(int i = 0; i < n; i++){
            for(auto muchie: G[i]){
                // muchie.first = nodul destinatie
                // muchie.second = costul initial al muchiei (i, muchie.first)
                // w + h[i] - h[j] reprezinta costul modificat al muchiei (i,j) in graful cu costuri modificate
                fout << i << " " << muchie.first << " " << muchie.second + h[i] - h[muchie.first] << "\n";
            }
        }


        // urmatoarele N linii contin matricea de distante
        // afisam matricea de distante
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(distante[i][j] == INF){
                    fout << "INF "; // daca nu exista drum, afisam INF
                } else {
                    fout << distante[i][j] << " "; // altfel, afisam distanta
                }
            }
            fout << "\n"; // trecem la urmatorul rand dupa fiecare linie de distante
        }
    }

}
#include <fstream>

using namespace std;

ifstream fin("afisarefii.in");
ofstream fout("afisarefii.out");

int n,k;
int p[105];


int main(){
    fin >> n;
    int x;
    for (int i = 1; i <= n; i++)
    {
        fin >> x;
        p[i] = x;
    }

    fin >> k;
    for (int j = 1; j <= k; j++)
    {
        fin >> x;

        //
        int count = 0;
        for (int j = 1; j <= n; j++)
        {
            if (p[j]==x) count++;
        }
        fout << count << " ";
        for (int j = 1; j <= n; j++)
        {
            if (p[j]==x) fout << j << " ";
        }

        fout << "\n";
    }
    
    

}
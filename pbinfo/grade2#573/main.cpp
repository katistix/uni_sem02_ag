/*
Se dă lista arcelor unui graf orientat.

Să se determine nodurile care au gradul exterior
egal cu gradul interior.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<pair<int,int>> grade;

int main(){

    int n,m;

    cin >> n >> m;
    grade.resize(n+1);

    int x,y;
    for (size_t i = 0; i < m; i++)
    {
        cin >> x >> y;

        grade[x].first++;
        grade[y].second++;
    }

    int count=0;
    for (int i = 1; i <= n; i++)
    {
        if(grade[i].first == grade[i].second){
            count++;
        }
    }

    cout << count;

    cout << "\n";

    for (int i = 1; i <= n; i++)
    {
        if(grade[i].first == grade[i].second){
            cout << i << " ";
        }
    }
    
    

}
/*

Să se scrie un program care găsește o soluție
pentru unul din următoarele labirinturi:
labirint_1.txt, labirint_2.txt, labirint_cuvinte.txt.

Pentru labirintul 1 si 2 punctul de pornire este indicat de
litera S și punctul de oprire este indicat de litera F,
spre deosebire de labirintul 1 și 2, labirintul 3 nu are o soluție unică

*/


#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
j=1
(j%3 == 1) -> j+=2 => j=3

j++ => j=4

01234
111111111111111111111 S 11111111111111111
1       1                   1       1   1
1   11111   11111   11111   1   1   1   1
1               1       1       1   1   1
1   11111111111111111   111111111   1   1
=====

131313131 ->



*/


int n, m;

// transforma din 
vector<vector<int>> normalizare_input(vector<vector<int>> raw_input){

    // fiecare linie
    for(int i=0;i<raw_input.size();i++){
        // pentru fiecare linie, coloanele alterneaza cu latime 1,3,1,3,...,3,1
        for(int j=0;j<raw_input[i].size();j++){


            // daca suntem in pozitie "lata", sari peste 2 pozitii
            if(j%3==1){
                j+=2;
            }
            else{ // suntem in pozitie "subtire"
                
            }
            
        }
    }
}


int main(){


    return 0;
}
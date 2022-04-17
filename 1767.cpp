#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define INF 0x3f3f3f
#define MAX 123
#define ii pair<int,int>


/*
M(i,j) = maior lucro de uma mochila de capacidade j, podendo usar os 
i primeiros objetos
*/
int M[MAX+1][MAX+1];
int pesos[MAX];
int valores[MAX];

void back_track_weight(int i, int j, int& peso, int& packs_used){
    peso = 0;
    packs_used = 0;
    for(int a=i; a>0; a--){
        if(M[a][j] != M[a-1][j]){
            // Usado
            peso += pesos[a];
            packs_used++;

            if(j - pesos[a] >= 0){
                j -= pesos[a];
            }
        }
    }
}



// problema da mochila simples
// Solução gulosa não rola, vai ter que ser via dinâmica
int main() {
    ios_base::sync_with_stdio(false);
    int W = 50;

    int n_tests; cin >> n_tests;
    for (int i=0; i<n_tests; i++){
        memset(M, -1, (MAX+1)*(MAX+1)*sizeof(int));
        memset(pesos, 0x3f, (MAX)*sizeof(int));
        memset(valores, 0, (MAX)*sizeof(int));

        int pac; cin >> pac;

        for (int p=1; p<=pac; p++){
            int qtd, wei; cin >> qtd >> wei;
            
            pesos[p] = wei;
            valores[p] = qtd;
        }

        for(int i=0; i<=pac; i++){
            for(int j=0; j<=W; j++){
                if(i==0 || j==0){
                    M[i][j] = 0;
                }else{
                    if(pesos[i] > j){
                        M[i][j] = M[i-1][j];
                    }else{
                        M[i][j] = max(M[i-1][j], valores[i]+M[i-1][j-pesos[i]]);
                    }
                }
            }
        }

        // for(int i=0; i<=pac; i++){
        //     for(int j=0; j<=W; j++){
        //         cout << M[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;


        int wei_used, packs_used;
        back_track_weight(pac,W,wei_used, packs_used);
        // for(int i=0; i<pac; i++){
        //     cout << used[i] << ", ";
        // }
        // cout << endl;

        cout << M[pac][W] << " brinquedos" << endl;
        cout << "Peso: " << wei_used << " kg" << endl;
        cout << "sobra(m) " << pac - packs_used << " pacote(s)" << endl;
        cout << endl;
    }
    return 0;
}
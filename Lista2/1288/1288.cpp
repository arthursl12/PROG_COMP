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
#define MAX_ITEMS 60
#define MAX_PESO 111
#define ii pair<int,int>


/*
M(i,j) = maior lucro de uma mochila de capacidade j, podendo usar os 
i primeiros objetos
*/
int M[MAX_ITEMS+1][MAX_PESO+1];
int pesos[MAX_ITEMS];
int valores[MAX_ITEMS];

// int mochila(int i, int peso){
//     if (M[i][peso])



// 	if (condicional) return tab[obj][aguenta] = 0;
// 	if (obj > n || !aguenta) return tab[obj][aguenta]=0;
// 	if (tab[obj].count(aguenta)) return tab[obj][aguenta];
// 	ll nao_coloca = knapsack(obj+1,aguenta);
// 	condicional += int(nao_coloca >= r);
// 	if (peso[obj]<=aguenta){
// 		ll coloca = valor[obj]+knapsack(obj+1,aguenta-peso[obj]);
// 		condicional += int(coloca >= r);
// 		return tab[obj][aguenta]=max(coloca,nao_coloca);
// 	}
// 	return tab[obj][aguenta]=nao_coloca;	
// }

// problema da mochila simples
int main() {
    ios_base::sync_with_stdio(false);

    int n_tests; cin >> n_tests;
    for (int i=0; i<n_tests; i++){
        memset(M, -1, (MAX_ITEMS+1)*(MAX_PESO+1)*sizeof(int));
        memset(pesos, 0x3f, (MAX_ITEMS)*sizeof(int));
        memset(valores, 0, (MAX_ITEMS)*sizeof(int));

        int pac; cin >> pac;

        for (int p=1; p<=pac; p++){
            int qtd, wei; cin >> qtd >> wei;
            
            pesos[p] = wei;
            valores[p] = qtd;
        }

        int W; cin >> W;
        int resistance; cin >> resistance;

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
        // back_track_weight(pac,W,wei_used, packs_used);
        // for(int i=0; i<pac; i++){
        //     cout << used[i] << ", ";
        // }
        // cout << endl;
        int max_attack = M[pac][W];
        if (max_attack >= resistance){
            cout << "Missao completada com sucesso" << endl;
        }else{
            cout << "Falha na missao" << endl;
        }
        // cout << M[pac][W] << " brinquedos" << endl;
        // cout << "Peso: " << wei_used << " kg" << endl;
        // cout << "sobra(m) " << pac - packs_used << " pacote(s)" << endl;
        // cout << endl;
    }
    return 0;
}
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

#define INF 0x3f3f3f
#define MAX 1234
#define ii pair<int,int>

int matrix[MAX][MAX];
int fw[MAX][MAX];
int custos_minimos[MAX];
int explorados[MAX];

// BFS simples
int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N; // nós
    int M; cin >> M; // arestas

    // inicialização
    memset(matrix, INF, MAX*MAX*sizeof(int));
    memset(fw, INF, MAX*MAX*sizeof(int));
    memset(custos_minimos, INF, MAX*sizeof(int));
    memset(explorados, 0, MAX*sizeof(int));


    // Matriz de adjacências
    for(int i=0; i<M; i++){
        int u; cin >> u;
        int v; cin >> v;
        int p; cin >> p;

        matrix[u-1][v-1] = p;
        matrix[v-1][u-1] = p;
        
        fw[u-1][v-1] = p;
        fw[v-1][u-1] = p;
    }
    for(int i=0; i<N; i++){
        fw[i][i] = 0;
    }


    // Print
    // for(int i=0; i<M; i++){
    //     for (int j=0; j<M; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    
    int root; cin >> root;
    // vector<int> custos_minimos(N,1234);
    custos_minimos[root-1] = 0;

    // Mínimo é o menor dos vizinhos da raiz
    int root_idx = root-1;
    int min = INF;
    for(int i=0; i<N; i++){
        if (fw[root_idx][i] < min && fw[root_idx][i] != 0)
            min = fw[root_idx][i];
    }

    // Tentativa: FW
    // for(int k=0; k<N; k++){
    //     for(int i=0; i<N; i++){
    //         for(int j=0; j<N; j++){
    //             if(fw[i][j] > fw[i][k] + fw[k][j]){
    //                 fw[i][j] = fw[i][k] + fw[k][j];
    //             }
    //         }
    //     }
    // }

    // // Máximo é só procurar a partir da raiz
    // int max = -1;
    // for(int j=0; j<N; j++){
    //     int current = fw[root_idx][j];
    //     if (current > max){
    //         max = fw[root_idx][j];
    //     }
    // }


    // "Dijkstra" n^2
    priority_queue<ii, vector<ii>, greater<ii>> p_queue;
    ii root_p(0,root_idx);
    p_queue.emplace(root_p);
    while(!p_queue.empty()){
        ii cur_p = p_queue.top();
        p_queue.pop();
        int custo = cur_p.first; 
        int idx = cur_p.second;

        // cout << "Explorando: " << idx << ", custo=" << custo << endl;

        if(custos_minimos[idx] != custo || explorados[idx] == 1){
            // cout << "Já explorado: " << idx << endl; 
            // Vértice já explorado antes, pode continuar
            continue;
        }

        explorados[idx] = 1;

        // Explorar os vizinhos
        for(int j=0; j<N; j++){
            int custo_extra = matrix[idx][j];
            if (custo + custo_extra < custos_minimos[j] && idx != j){
                // Achei um caminho melhor
                int novo_custo = custo + custo_extra;
                custos_minimos[j] = novo_custo;
                ii myp(novo_custo, j);
                p_queue.push(myp);
                // cout << "\tMelhor: " << j << ", custo=" << novo_custo << endl;

            }
        }
    }

    // Máximo é o maior do custos_minimos
    int min2 = INF;
    int max = -1;
    for(int i=0; i<N; i++){
        int val = custos_minimos[i];
        if (val < min2 && val != 0){
            min2 = val;
        }
        if (val > max && val != 0){
            max = val;
        }
        // cout << custos_minimos[i] << " ";
    }
    // cout << endl;

    // cout << "MAX=" << max << ", MIN=" << min << ", MIN2=" << min << endl;
    cout << max - min << endl;

    return 0;
}
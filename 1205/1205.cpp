#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <cstring>
#include <map>
#include <stack>
#include <cmath>

using namespace std;


#define INF 0x3f3f3f
#define MAXV 1234
// #define MAXE 2*MAXV

#define ii pair<int,int>

vector<vector<int>> graph;
int explorados[MAXV];
int vertex_weight[MAXV];
int custos_minimos[MAXV];

void print_vector(int* array, int i){
    for(int j=0; j<i; j++){
        cout << array[j] << ",";
    }
    cout << endl;
}
void print_vector(vector<int> v){
    for(int j=0; j<v.size(); j++){
        cout << v[j] << ",";
    }
    cout << endl;
}

void dijkstra_vertex_weight(int root_idx){
    priority_queue<ii, vector<ii>, greater<ii>> p_queue;
    ii root_p(vertex_weight[root_idx],root_idx);
    custos_minimos[root_idx] = vertex_weight[root_idx];
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
        for(int j=0; j<graph[idx].size(); j++){
            int custo_extra = vertex_weight[graph[idx][j]];
            // cout << "\tNovo custo=" << custo+custo_extra << ", antigo=" << custos_minimos[graph[idx][j]] << endl;
            if (custo + custo_extra < custos_minimos[graph[idx][j]] 
                && idx != graph[idx][j]){
                // Achei um caminho melhor
                int novo_custo = custo + custo_extra;
                custos_minimos[graph[idx][j]] = novo_custo;
                ii myp(novo_custo, graph[idx][j]);
                p_queue.push(myp);
                // cout << "\tMelhor: " << j << ", custo=" << novo_custo << endl;

            }
        }
    }
}



int main(){
    ios_base::sync_with_stdio(false);
    cout << fixed;
    cout << setprecision(3);

    int V;
    while(cin >> V){
        int E; cin >> E;

        // Balas e probabilidade
        int balas; cin >> balas;
        float P; cin >> P;

        // Inicialização
        graph.clear();
        memset(explorados, 0, MAXV*sizeof(int));
        memset(vertex_weight, 0, MAXV*sizeof(int));
        memset(custos_minimos, 0x3f, MAXV*sizeof(int));

        // Monta o grafo
        for(int i=0; i<V; i++){
            vector<int> myvec;
            graph.push_back(myvec);
        }
        for(int i=0; i<E; i++){
            int u; cin >> u; u--;
            int v; cin >> v; v--;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // for(int i=0; i<V; i++){
        //     cout << i+1 << ": ";
        //     for (int j=0; j<graph[i].size(); j++){
        //         cout << graph[i][j] + 1 << ", ";
        //     }
        //     cout << endl;
        // }

        // Pesos (atiradores)
        int n_atiradores; cin >> n_atiradores;
        for(int i=0; i<n_atiradores; i++){
            int idx; cin >> idx; idx--;
            vertex_weight[idx]++;
        }

        // Entrada e saída
        int idx_start; cin >> idx_start; idx_start--;
        int idx_goal; cin >> idx_goal; idx_goal--;

        // Dijkstra
        dijkstra_vertex_weight(idx_start);
        // print_vector(custos_minimos, V);
        int total_atiradores = custos_minimos[idx_goal];
        if (total_atiradores > balas){
            cout << "0.000" << endl;
        }else{
            double prec = pow(P,total_atiradores);
            cout << prec << endl;
        }
    }
    return 0;
}
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

#define INF 0x3f3f3f
#define MAXV 12345
#define MAXE 2*MAXV

#define ii pair<int,int>

int matrix[MAXV][MAXV];
int explorados[MAXV];
int custos_minimos[MAXV];

using namespace std;

void print_stack(stack<int> mys){
    cout << "[";
    int top = mys.top();
    mys.pop();
    while(!mys.empty()){
        cout << top << ",";
        top = mys.top();
        mys.pop();
    }
    cout << "]" << endl;
}

void print_vector(vector<int> vec){
    for(int i : vec){
        cout << i << ", ";
    }
    cout << endl;
}


void processa_ciclo(int i, vector<int> curr_stack, set<pair<int,int>>& ciclos){
    vector<int> curr_cycle;
    // print_vector(curr_stack);

    // Acha os elementos do ciclo, a partir de 'i'
    int k=curr_stack.size() - 1;
    while(curr_stack[k] != i){
        curr_cycle.push_back(curr_stack[k]);
        k--;
    }
    curr_cycle.push_back(i);
    reverse(curr_cycle.begin(),curr_cycle.end());    

    // Acha o custo do ciclo
    int total = 0;
    int last_vertex = i;
    for(int k=1; k<curr_cycle.size(); k++){
        total += matrix[last_vertex][curr_cycle[k]];
        last_vertex = curr_cycle[k];
    }
    total += matrix[last_vertex][i];

    ciclos.insert({total,i});
}

void dfs(int i, int parent, vector<int> path_now, set<pair<int,int>>& ciclos){
    if(explorados[i] == 0){
        explorados[i] = 1;
        path_now.push_back(i);

        // cout << "\tExplorando " << i << ", pai=" << parent <<  endl;
        for(int j=0; j<MAXV; j++){
            if (matrix[i][j] < INF && j != parent){
                // path_now.push_back(j);
                // cout << "\t\t";
                // print_vector(path_now);
                dfs(j, i, path_now, ciclos);
                // curr_stack.pop();

            }
        }
    }else if (explorados[i] == 1){
        // cout << "\tCiclo! " << i << endl;

        // Detectamos um ciclo
        processa_ciclo(i, path_now, ciclos);
    }
    explorados[i] = 2;
}

void dijkstra(int root_idx){
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
        for(int j=0; j<MAXV; j++){
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
}



int main(){
    ios_base::sync_with_stdio(false);

    int V;
    while(cin >> V){
        // Inicialização
        memset(matrix, 0x3f, MAXV*MAXV*sizeof(int));
        memset(explorados, 0, MAXV*sizeof(int));
        memset(custos_minimos, INF, MAXV*sizeof(int));
        
        // Entradas e montagem do grafo
        int E; cin >> E;
        for(int i=0; i<E; i++){
            int u; cin >> u;
            int v; cin >> v;
            int c; cin >> c;

            matrix[u-1][v-1] = c;
            matrix[v-1][u-1] = c;
        }

        // Processamento das queries
        int n_queries; cin >> n_queries;
        for(int i=0; i<n_queries; i++){
            int idx_start; cin >> idx_start; idx_start--;
            int size; cin >> size;

            // DFS: achar os ciclos
            memset(explorados, 0, MAXV*sizeof(int));
            vector<int> visiting;
            set<pair<int,int>> ciclos;
            dfs(idx_start, -1, visiting, ciclos);

            // for(auto p : ciclos){
            //     cout << p.second.first << "(" << p.first << ") ->";
            //     print_vector(p.second.second);
            // }

            // Dijkstra: mínimo para cada outro vértice 
            memset(custos_minimos, INF, MAXV*sizeof(int));
            memset(explorados, 0, MAXV*sizeof(int));
            custos_minimos[idx_start] = 0;
            dijkstra(idx_start);
            // for(int i=0; i<V; i++){
            //     cout << custos_minimos[i] << ",";
            // }
            // cout << endl;

            // Achar os ciclos que cabem
            int min_to_turn = INF;
            for(ii p : ciclos){
                int c_size = p.first;
                int c_start = p.second;

                if (c_size < size){
                    // cout << "Muito pequeno" << endl;
                    // Ciclo muito pequeno
                    continue;
                }else{
                    int possible_min = 2*custos_minimos[c_start] + c_size;
                    if (possible_min < min_to_turn){
                        min_to_turn = possible_min;
                    }
                }
            }
            if (min_to_turn == INF){
                cout << -1 << endl;
            }else{
                cout << min_to_turn << endl;
            }
            
            
            // sort them
        }
        // cout << endl;
    }

    
    return 0;
}
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

// int matrix[MAXV][MAXV];
int explorados[MAXV];
int parent_table[MAXV];
int custos_minimos[MAXV];

using namespace std;

typedef struct Node{
    int destination;
    int cost;
} Node;

vector<vector<Node>> graph;


void print_stack(stack<int>& mys){
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

void print_vector(vector<int>& vec){
    for(int i : vec){
        cout << i << ", ";
    }
    cout << endl;
}


void processa_ciclo(int i, int custo_ate_aqui, int parent_cycle, set<pair<int,int>>& ciclos){
    // vector<int> curr_cycle;
    // print_vector(curr_stack);
    int idx = parent_cycle;
    int min_cost = INF;
    int min_idx = -1;
    while(idx != parent_table[i]){
        // cout << "\tCusto até " << idx+1 << "= " << custos_minimos[idx] << ", min=" << min_cost << ", fechador=" << i+1 << endl;
        if(custos_minimos[idx] < min_cost){
            min_cost = custos_minimos[idx];
            min_idx = idx;
        }
        idx = parent_table[idx];
    }
    // cout << "\tmin=" << min_cost << ", min_idx=" << min_idx+1 << endl;

    // cout << "\tCusto até " << idx+1 << "= " << custos_minimos[idx] << ", min=" << min_cost << ", fechador=" << i+1 << endl;
    // if(custos_minimos[idx] < min_cost){
    //     min_cost = custos_minimos[idx];
    //     min_idx = idx;
    // }
    // Acha os elementos do ciclo, a partir de 'i'
    // int k=curr_stack.size() - 1;
    // while(curr_stack[k] != i){
    //     // curr_cycle.push_back(curr_stack[k]);
    //     k--;
    // }
    // curr_cycle.push_back(i);
    // reverse(curr_cycle.begin(),curr_cycle.end());    

    int custo_ciclo = custo_ate_aqui - custos_minimos[i];
    ciclos.insert({custo_ciclo,min_idx});
}

void dfs(int i, int parent, int custo_ate_aqui, set<pair<int,int>>& ciclos){
    if(explorados[i] == 0){
        explorados[i] = 1;
        // path_now.push_back(i);
        parent_table[i] = parent;

        // cout << "\tExplorando " << i << ", pai=" << parent << ", ate_aqui=" << custo_ate_aqui <<  endl;
        for(int j=0; j<graph[i].size(); j++){
            if(graph[i][j].destination != parent){
                dfs(graph[i][j].destination, i, custo_ate_aqui+graph[i][j].cost, ciclos);
            }
        }

    }else if (explorados[i] == 1){
        // cout << "\tCiclo! " << i << ", ate_aqui=" << custo_ate_aqui << endl;

        // Detectamos um ciclo
        processa_ciclo(i, custo_ate_aqui, parent, ciclos);
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
        for(int j=0; j<graph[idx].size(); j++){
            int custo_extra = graph[idx][j].cost;
            if (custo + custo_extra < custos_minimos[graph[idx][j].destination] 
                && idx != graph[idx][j].destination){
                // Achei um caminho melhor
                int novo_custo = custo + custo_extra;
                custos_minimos[graph[idx][j].destination] = novo_custo;
                ii myp(novo_custo, graph[idx][j].destination);
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
        // memset(matrix, 0x3f, MAXV*MAXV*sizeof(int));
        graph.clear();
        memset(explorados, 0, MAXV*sizeof(int));
        memset(custos_minimos, 0x3f, MAXV*sizeof(int));
        memset(parent_table, -1, MAXV*sizeof(int));

        
        for(int i=0; i<V; i++){
            vector<Node> myvec;
            graph.push_back(myvec);
        }

        // Entradas e montagem do grafo
        int E; cin >> E;
        for(int i=0; i<E; i++){
            int u; cin >> u; u--;
            int v; cin >> v; v--;
            int c; cin >> c;

            Node n1; n1.destination=v; n1.cost=c;
            Node n2; n2.destination=u; n2.cost=c;

            graph[u].push_back(n1);
            graph[v].push_back(n2);
        }

        // Processamento das queries
        int n_queries; cin >> n_queries;
        for(int i=0; i<n_queries; i++){
            int idx_start; cin >> idx_start; idx_start--;
            int size; cin >> size;

            // Dijkstra: mínimo para cada outro vértice 
            memset(custos_minimos, 0x3f, MAXV*sizeof(int));
            memset(explorados, 0, MAXV*sizeof(int));
            memset(parent_table, -1, MAXV*sizeof(int));

            custos_minimos[idx_start] = 0;
            dijkstra(idx_start);
            // for(int i=0; i<V; i++){
            //     cout << custos_minimos[i] << ",";
            // }
            // cout << endl;

            // DFS: achar os ciclos
            memset(explorados, 0, MAXV*sizeof(int));
            vector<int> visiting;
            set<pair<int,int>> ciclos;
            parent_table[idx_start] = INF;
            dfs(idx_start, -1, 0, ciclos);

            // for(auto p : ciclos){
            //     cout << p.second << "(" << p.first << ")" << endl;
            //     // print_vector(p.second.second);
            // }

            

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
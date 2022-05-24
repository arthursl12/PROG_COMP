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
#define MAX 1111
#define ii pair<int,int>

int availability_horses[MAX];
int N;
int n_shirts_each, n_compet;
vector<vector<int>> graph;
bool possible;


// Implementacao do Algoritmo de Dinic para fluxo maximo em redes
//
// Para usar, basta declarar com o numero de vertices
// vertices sao indexados com 0, 1, ... n-1
//
// Exemplo:
//
// dinic D(10); // teremos 10 vertices indexados de 0 a 9
// D.add(0, 1, 5); // adiciona aresta de 0 a 1 com capacidade 5
// int flow = D.max_flow(0, 1); // computa o fluxo maximo de 0 a 1
 
#include <vector>
#include <queue>
 
struct dinic {
    struct edge {
        int to, cap, rev, flow;
        bool res;
        edge(int to_, int cap_, int rev_, bool res_)
            : to(to_), cap(cap_), rev(rev_), flow(0), res(res_) {}
    };
 
    vector<vector<edge>> g;
    vector<int> lev, beg;
    long long F;
    dinic(int n) : g(n), F(0) {}
 
    void add(int a, int b, int c) {
        g[a].emplace_back(b, c, g[b].size(), false);
        g[b].emplace_back(a, 0, g[a].size()-1, true);
    }
    bool bfs(int s, int t) {
        lev = vector<int>(g.size(), -1); lev[s] = 0;
        beg = vector<int>(g.size(), 0);
        queue<int> q; q.push(s);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (auto& i : g[u]) {
                if (lev[i.to] != -1 or (i.flow == i.cap)) continue;
                lev[i.to] = lev[u] + 1;
                q.push(i.to);
            }
        }
        return lev[t] != -1;
    }
    int dfs(int v, int s, int f = 0x3f3f3f3f) {
        if (!f or v == s) return f;
        for (int& i = beg[v]; i < g[v].size(); i++) {
            auto& e = g[v][i];
            if (lev[e.to] != lev[v] + 1) continue;
            int foi = dfs(e.to, s, min(f, e.cap - e.flow));
            if (!foi) continue;
            e.flow += foi, g[e.to][e.rev].flow -= foi;
            return foi;
        }
        return 0;
    }
    long long max_flow(int s, int t) {
        while (bfs(s, t)) while (int ff = dfs(s, t)) F += ff;
        return F;
    }
};


int main() {
    ios_base::sync_with_stdio(false);

    int instancia = 1;
    int n_horses, n_soldiers, n_aff;
    while(cin >> n_horses){
        // Input
        cin >> n_soldiers >> n_aff;

        /* 
        Model as Flow in Bipartite Graph
        0: source
        1...n_horses: horses
        n_horses+1...n_soldiers+n_horses: soldiers
        n_soldiers+n_horses+1: sink
        */
        dinic D(2+n_horses+n_soldiers);
        int s = 0;
        int t = n_soldiers+n_horses+1;

        // Input horse capacity as edge between horses and source
        for(int i=1; i<=n_horses; i++){
            int capacity; cin >> capacity;
            D.add(s,i,capacity);
        }

        // Connect each soldier to sink
        for(int i=1; i<=n_soldiers; i++){
            D.add(n_horses+i,t,1);
        }

        // Input affinity as edges between horses and soldiers
        for(int i=1; i<=n_aff; i++){
            int u,v; cin >> u >> v;
            int idx_horse = u;
            int idx_soldier = n_horses+v;
            D.add(idx_horse, idx_soldier, 1);
        }

        // Solve
        int flow = D.max_flow(s, t); // computa o fluxo maximo de s a t

        // Print result
        cout << "Instancia " << instancia << endl;
        instancia++;
        cout << flow << endl;
        cout << endl;
    }

    
    return 0;
}
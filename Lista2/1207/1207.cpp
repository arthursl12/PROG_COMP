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

#define INF 0x3f3f3f3f
#define MAX 1111
#define ii pair<int,int>

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

int costs[MAX];
int edges[MAX];

int main() {
    ios_base::sync_with_stdio(false);

    int n_vodkas, n_categories;
    while(cin >> n_vodkas){
        // Inputs
        cin >> n_categories;

        // Cost of vodkas
        for(int i=1; i<=n_vodkas; i++){
            int c; cin >> c;
            costs[i] = c;
        }

        // How many vodkas per category
        for(int i=1; i<=n_categories; i++){
            int n_e; cin >> n_e;
            edges[i] = n_e;
        }

    
        /* 
        Model as Flow in Bipartite Graph
        0: source
        1...n_categories: categories
        n_categories+1...n_categories+n_vodkas: vodkas
        n_categories+n_vodkas+1: sink
        */
        dinic D(2+n_vodkas+n_categories);
        int s = 0;
        int t = n_vodkas+n_categories+1;

        // Each vodkas per category
        int sum_benefits = 0;
        for(int i=1; i<=n_categories; i++){
            int benefit; cin >> benefit; sum_benefits += benefit;
            D.add(s,i,benefit);     // Connect category to source

            int n_e = edges[i];
            for(int j=1; j<=n_e; j++){
                int idx_vodka; cin >> idx_vodka;
                D.add(i,n_categories+idx_vodka,INF);
            }
        }

        // Connect each vodka to sink
        for(int i=1; i<=n_vodkas; i++){
            D.add(n_categories+i,t,costs[i]);
        }

        // Solve
        int flow = D.max_flow(s, t); // computa o fluxo maximo de s a t
        cout << sum_benefits - flow << endl;
    }

    
    return 0;
}
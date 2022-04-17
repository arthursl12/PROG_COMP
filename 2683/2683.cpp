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

#define INF 0x3f3f3f

using namespace std;

// DSU
int parent[1234567];
int rnk[1234567];

void make_set(int i){
    parent[i] = i;
    rnk[i] = 1;
}

int find(int i){
    int t = i;
    while(parent[i] != i){
        i = parent[i];
    }
    while(parent[t] != t){
        int q = parent[t];
        parent[t] = i;
        t = q;
    }
    return i;
}

void union_set(int i, int j){
    i = find(i);
    j = find(j);
    if (rnk[i] > rnk[j]){
        parent[j] = i;
        rnk[i] += rnk[j];
    }else{
        parent[i] = j;
        rnk[j] += rnk[i];
    }
}



int main() {
    ios_base::sync_with_stdio(false);

    int n_gal; cin >> n_gal;
    vector<pair<int, pair<int,int>>> galleries;
    for(int i=0; i<n_gal; i++){
        int u; cin >> u;
        int v; cin >> v;
        int cost; cin >> cost;
        galleries.push_back({cost, {u,v}});
    }

    // Kruskal to find max spanning tree
    memset(parent, -1, 1234567*sizeof(int));
    memset(rnk, -1, 1234567*sizeof(int));
    sort(galleries.begin(), galleries.end(), greater<pair<int,pair<int,int>>>());
    for(int i=0; i<n_gal; i++){make_set(i);}

    int max_cost = 0;
    for(auto p : galleries){
        int cost = p.first;
        int u = p.second.first;
        int v = p.second.second;
        if (find(u) != find(v)){
            // Não gera ciclo
            max_cost += cost;
            union_set(u,v);
        }
    }
    cout << max_cost << endl;

    // Kruskal to find min spanning tree
    memset(parent, -1, 1234567*sizeof(int));
    memset(rnk, -1, 1234567*sizeof(int));
    sort(galleries.begin(), galleries.end());
    for(int i=0; i<n_gal; i++){make_set(i);}

    int min_cost = 0;
    for(auto p : galleries){
        int cost = p.first;
        int u = p.second.first;
        int v = p.second.second;
        if (find(u) != find(v)){
            // Não gera ciclo
            min_cost += cost;
            union_set(u,v);
        }
    }
    cout << min_cost << endl;
    return 0;
}
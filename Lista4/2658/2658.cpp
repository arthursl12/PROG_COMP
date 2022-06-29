#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

#define INF 0x3f3f3f3f
#define MAX 112345
#define ii pair<int,int>
#define ll long long

typedef struct node {
    int frequency[9];
} node;

int lazy[4*MAX];
node tree[4*MAX];
node NULL_NODE;

// Seg tree with propagate
void constroi(int noh, int ini, int fim){
    for(int i=0; i<9; i++)
        tree[noh].frequency[i] = 0;
    tree[noh].frequency[1] = fim - ini + 1;
    if (ini != fim){
        int meio = (ini + fim) / 2;
        constroi(2*noh, ini, meio);
        constroi(2*noh+1, meio+1, fim);
    }
}

void propaga(int noh, int ini, int fim){
    if (lazy[noh] == 0){
        // Trying to propagate nothing
        return;
    }

    int copy[9];
    for(int i=0; i<9; i++){
        copy[(i+lazy[noh]) % 9] = tree[noh].frequency[i];
    }

    for(int i=0; i<9; i++){
        tree[noh].frequency[i] = copy[i];
    }
    if (ini != fim){
        lazy[2*noh] += lazy[noh];
        lazy[2*noh+1] += lazy[noh];
    }
    lazy[noh] = 0;
}

node add(node n1, node n2){
    node res;
    for(int i=0; i<9;i++){
        res.frequency[i] = n1.frequency[i] + n2.frequency[i];
    }
    return res;
}

node consulta(int noh, int ini, int fim, int l, int r){
    propaga(noh, ini, fim);
    if (l <= ini && fim <= r){
        return tree[noh];
    }
    if (fim < l || r < ini || ini > fim){
        return NULL_NODE;
    }
    int meio = (ini+fim)/2;
    return add(consulta(2*noh, ini, meio, l, r), 
               consulta(2*noh+1, meio+1, fim, l, r));
}

void update(int noh, int ini, int fim, int l, int r, int x){
    propaga(noh, ini, fim);
    if (fim < l || r < ini || ini > fim){
        return;
    }
    if (l <= ini && fim <= r){
        lazy[noh] += x;
        propaga(noh, ini, fim);
        return;
    }
    int meio = (ini+fim) / 2;
    update(2*noh, ini, meio, l, r, x);
    update(2*noh+1, meio+1, fim, l, r, x);
    tree[noh] = add(tree[2*noh], tree[2*noh+1]);
}

int main() {
    ios_base::sync_with_stdio(false);

    // Definining NULL_NODE
    for(int i=0; i<9; i++){
        NULL_NODE.frequency[i] = 0;
    }
    // cout << "In" << endl;

    // Input
    int n_teclas, n_acordes;
    cin >> n_teclas >> n_acordes;
    constroi(1,0,n_teclas-1);
    // cout << "Build" << endl;

    // Process queries
    for(int iii=0; iii<n_acordes; iii++){
        int A, B; cin >> A >> B;
        node res = consulta(1,0,n_teclas-1,A,B);

        int u=0;
        int maxu=-1;
        for(int i=0; i<9;i++){
            if(res.frequency[i] >= maxu){
                u=i;
                maxu=res.frequency[i];
            }
        }
        update(1,0,n_teclas-1, A,B,u);
    }

    for(int i=0; i<n_teclas; i++){
        node tmp = consulta(1,0,n_teclas-1,i,i);
        for(int j=0; j<9; j++){
            if(tmp.frequency[j]){
                cout << j;
            }
        }
        cout << endl;
    }
    return 0;
}
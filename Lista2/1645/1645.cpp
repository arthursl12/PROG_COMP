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
#define MAX 111
#define ii pair<int,int>
#define ll long long

ll M[MAX][MAX];
ll vec[MAX];
ll K, N;

/*
M(i,j) = maior sequencia usando os itens até i, incluindo ele ou não
*/
ll max_sequence(ll i, ll tam){
    if (tam == K){
        // Caso base
        M[i][tam] = 1;
    }else if (M[i][tam] != -1){
        // Caso já computado
        // Nada a fazer
    }else{
        // Caso geral
        M[i][tam] = 0;
        for(ll j=i+1; j<=N; j++){
            if(vec[i] < vec[j]){
                M[i][tam] += max_sequence(j,tam+1);
            }
        }
    }
    return M[i][tam];
}

void print_mat(){
    for(int i=1; i<=N; i++){
        for(int j=0; j<=N; j++){
            cout << M[i][j] << ",";
        }
        cout << endl;
    }
    cout << endl;
}

void print_vec(){
    for(int i=1; i<=N; i++){
        cout << vec[i] << ",";
    }
    cout << endl;
}

// problema da mochila simples
int main() {
    ios_base::sync_with_stdio(false);

    cin >> N; cin >> K;
    while(N != 0){
        memset(M, -1, (MAX)*(MAX)*sizeof(ll));
        memset(vec, -1, (MAX)*sizeof(ll));

        for(int i=1; i<=N; i++){
            ll in; cin >> in;
            vec[i] = in;
        }
        // print_vec();
        // print_mat();
        ll total = 0;
        for(int i=1; i<=N; i++){
            total += max_sequence(i,1);
        }

        cout << total << endl;
        // print_mat();
        cin >> N; cin >> K;
    }
    return 0;
}


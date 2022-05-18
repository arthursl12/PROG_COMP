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
#define MAX 55555
#define ii pair<int,int>
#define ll long long

int M[2][MAX];
int vec[MAX];
int N;

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

int find_max_triangle(){
    // M[0][.]: esquerda p/ direita
    // M[1][.]: direita p/ esquerda

    // Tenta montar o triângulo da esquerda para a direita
    M[0][1] = 1; // Começa com um bloquinho
    for(int i=2; i<=N; i++){
        M[0][i] = min(vec[i], M[0][i-1]+1);
    }
	
    // Volta tentando da direita para a esquerda 
    // (considerando o resultado obtido na primeira passagem)
    M[1][N] = 1; // Termina com um bloquinho
    for(int i=N-1; i>=1; i--){
        M[1][i] = min(vec[i], M[1][i+1]+1);
    }

    // Acha o maior triângulo
    int max_triangle = -1;
    for(int i=N; i>=1; i--){
        max_triangle = max(max_triangle, min(M[0][i], M[1][i]));
    }

    return max_triangle;
}


int main() {
    ios_base::sync_with_stdio(false);

    memset(M, -1, (2)*(MAX)*sizeof(int));
    memset(vec, -1, (MAX)*sizeof(int));

    // Input
    cin >> N;
    for(int i=1; i<=N; i++){
        int in; cin >> in;
        vec[i] = in;
    }

    cout << find_max_triangle() << endl;
    return 0;
}



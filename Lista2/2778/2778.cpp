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
#define MAX 111
#define ii pair<int,int>




#define MAX_ROOMS 1234
#define BIGM 10000000
#define MAX_MANA 105

/*
M[i][j]: menor tempo gasto total a partir da sala i, entrando com j mana
M[0][in_mana] dá a resposta
*/

int matrix[MAX][MAX];
int visited[MAX][MAX];
int pesos[MAX][MAX];

int N,M,max_null,max_neg;
int used_nulls, used_neg;

/*
matrix[i][j]: menor caminho de (1,1) até (i,j), respeitando as regras
matrix[N][M] dá a resposta
*/

int DTW(int i, int j){
    if (i < 1 || j < 1){
        return 0;
    }

    // if (matrix[i][j] != INF){
    //     return matrix[i][j];
    // }

    if(visited[i][j] != -1){
        // Tentando visitar onde já foi
        return INF+1;
    }else if (used_neg > max_neg || used_nulls > max_null){
        // Usando mais negativos ou nulos que o permitido
        return INF+1;
    }

    if (i == 1 && j == 1){
        matrix[i][j] = pesos[i][j];
        return matrix[i][j];
    }

    cout << "Visitando: " << i << "," << j << endl;

    // Visita e tenta a partir disso
    visited[i][j] = 0;
    if (pesos[i][j] == 0){ used_nulls++; }
    if (pesos[i][j] < 0){ used_neg++; }

    int min_cost = INF;
    if (i > 1 && visited[i-1][j] == -1){
        min_cost = min(min_cost, pesos[i][j]+DTW(i-1,j));
    }
    if (j > 1 && visited[i][j-1] == -1){
        min_cost = min(min_cost, pesos[i][j]+DTW(i,j-1));
    } 
    
    if (j <= M-1 && visited[i][j+1] == -1){
        min_cost = min(min_cost, pesos[i][j]+DTW(i,j+1));
    }

    // Desmarca a visita para permitir outros caminhos
    visited[i][j] = -1;
    if (pesos[i][j] == 0){ used_nulls--; }
    if (pesos[i][j] < 0){ used_neg--; }

    matrix[i][j] = min_cost;
    return matrix[i][j];
}

void print_mat(){
    for(int i=0; i<=N; i++){
        for(int j=0; j<=M; j++){
            if (matrix[i][j] == INF)
                cout << "*" << ",";
            else if (matrix[i][j] == INF+1)
                cout << "INF" << ",";
            else
                cout << matrix[i][j] << ",";

                
        }
        cout << endl;
    }
    cout << endl;
}

void print_mat_pesos(){
    for(int i=0; i<=N; i++){
        for(int j=0; j<=M; j++){
            if (pesos[i][j] != INF)
                cout << pesos[i][j] << ",";
            else
                cout << "INF" << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    while(cin >> N >> M >> max_null >> max_neg){
        memset(pesos, INF, MAX*MAX*sizeof(int));
        memset(visited, -1, MAX*MAX*sizeof(int));
        memset(matrix, 0x3f, MAX*MAX*sizeof(int));

        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                int peso; cin >> peso;
                pesos[i][j] = peso;
            }
        }
        // print_mat_pesos();
        // print_mat();
        used_neg = 0; used_nulls = 0;
        cout << DTW(N,M) << endl;
        // print_mat();




        // cout << min_time(0, in_mana) << endl;

    }
    return 0;
}
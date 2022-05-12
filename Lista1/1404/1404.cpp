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

#define INF 0x3f3f3f
#define MAXV 12345
#define MAXE 2*MAXV

#define ii pair<int,int>

// int matrix[MAXV][MAXV];
int explorados[MAXV];
int custos_minimos[MAXV];

using namespace std;

int board[20][20];
int N;
int M;


/*

‘0’ empty house,
‘1’ your pieces, 
'2’ opponent’s piece
*/

int processa(int i, int j, int board[20][20]){
    int max_capt = 0;

    // if (i == 3 && j == 3){
    //     cout << "(3,3)" << endl;
    // }

    // cout << "Processa " << i+1 << "," << j+1 << endl;

    // Recursivamente processa
    // Come no superior direito
    if (i+2 < N && j+2 < M && board[i+1][j+1] == 2 && board[i+2][j+2] == 0){
        int board2[20][20]; memcpy(board2,board, 20*20*sizeof(int));
        board2[i+2][j+2] = 1;
        board2[i+1][j+1] = 0;
        board2[i][j] = 0;
        max_capt = max(1+processa(i+2, j+2, board2), max_capt);
    }

    // if (i == 3 && j == 3){
    //     cout << "\t" << max_capt << endl;
    // }

    // Come no inferior esquerdo
    if (i-2 >= 0 && j-2 >= 0 && board[i-1][j-1] == 2 && board[i-2][j-2] == 0){
        int board2[20][20]; memcpy(board2,board, 20*20*sizeof(int));
        board2[i-2][j-2] = 1;
        board2[i-1][j-1] = 0;
        board2[i][j] = 0;
        max_capt = max(1+processa(i-2, j-2, board2), max_capt);
    }

    // if (i == 3 && j == 3){
    //     cout << "\t" << max_capt << endl;
    // }

    // Come no inferior direito
    if (i-2 >= 0 && j+2 < M && board[i-1][j+1] == 2 && board[i-2][j+2] == 0){
        int board2[20][20]; memcpy(board2,board, 20*20*sizeof(int));
        board2[i-2][j+2] = 1;
        board2[i-1][j+1] = 0;
        board2[i][j] = 0;
        max_capt = max(1+processa(i-2, j+2, board2), max_capt);
    }

    // if (i == 3 && j == 3){
    //     cout << "\t" << max_capt << endl;
    // }

    // Come no superior esquerdo
    if (i+2 < N && j-2 >= 0 && board[i+1][j-1] == 2 && board[i+2][j-2] == 0){
        int board2[20][20]; memcpy(board2,board, 20*20*sizeof(int));
        board2[i+2][j-2] = 1;
        board2[i+1][j-1] = 0;
        board2[i][j] = 0;
        max_capt = max(1+processa(i+2, j-2, board2), max_capt);
    }

    // if (i == 3 && j == 3){
    //     cout << "\t" << max_capt << endl;
    // }
    // cout << "\t Return: " << i+1 << "," << j+1 << endl;

    return max_capt;
}

void print_board(int board[20][20]){
    for(int i=N-1; i>=0; i--){
        for(int j=0; j<M; j++){
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void monta_tabuleiro(){
    memset(board, 0, 20*20*sizeof(int));

    if(M % 2 == 0){
        int pos = 0;
        int j=0;
        bool invertido = false;
        for(int i=0; i<round(((float)N*M)/2); i++){
            int status; cin >> status;
            // cout << "Status: " << status << endl;
            if (!invertido){
                // cout << "\tat (NI) " << j << "," << pos << endl;
                board[j][pos] = status;
            }else{
                // cout << "\tat ( I) " << j << "," << pos << endl;
                board[j][pos] = status;
            }
            pos += 2;
            if(pos == M){
                invertido = true;
                j++;
                pos = 1;
            }else if (pos == M+1){
                invertido = false;
                pos = 0;
                j++;
            }
        }
    }else{
        int pos = 0;
        int j=0;
        bool invertido = false;
        for(int i=0; i<round(((float)N*M)/2); i++){
            int status; cin >> status;
            // cout << "Status: " << status << endl;
            if (!invertido){
                // cout << "\tat (NI) " << j << "," << pos << endl;
                board[j][pos] = status;
            }else{
                // cout << "\tat ( I) " << j << "," << pos << endl;
                board[j][pos] = status;
            }
            pos += 2;
            if(pos == M+1){
                invertido = true;
                j++;
                pos = 1;
            }else if (pos == M){
                invertido = false;
                pos = 0;
                j++;
            }
        }
    }
}

int main(){

    ios_base::sync_with_stdio(false);

    cin >> N;
    cin >> M;
    while(N != 0 && M != 0){
        monta_tabuleiro();
        // print_board(board);

        int max_capt = 0;
        for(int i=N-1; i>=0; i--){
            for(int j=0; j<M; j++){
                if(board[i][j] == 1){
                    max_capt = max(processa(i,j,board),max_capt);
                }
            }
        }
        cout << max_capt << endl;



        cin >> N; cin >> M;
    }

    return 0;
}
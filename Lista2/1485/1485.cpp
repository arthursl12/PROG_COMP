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
#define MAX_SLOTS 300
#define MAX_BALLS 150
#define MIN_VAL -8192
#define ii pair<int,int>


/*
M[i][j]: menor tempo gasto total a partir da sala i, entrando com j mana
M[0][in_mana] dá a resposta
*/

int n_slots, n_balls; 
int slot_val[MAX_SLOTS];
int ball_val[MAX_BALLS];
int double_slot_val[MAX_SLOTS+MAX_SLOTS];
int slot_val_transpose[MAX_SLOTS];
int max_profit[MAX_BALLS][MAX_SLOTS][MAX_SLOTS];

void print_ball(){
    for(int i=0; i<=n_balls; i++){
        cout << ball_val[i] << " ";
    }
    cout << endl;
}

void print_matrix(){
    for(int n=0; n<=n_balls; n++){
        cout << "Ball " << n << ":" << endl;
        for(int i=0; i<=n_slots; i++){
            for(int j=0; j<=n_slots; j++){
                if (max_profit[n][i][j] == -INF){
                    cout << "-I" << " ";
                }else if(max_profit[n][i][j] == INF){
                    cout << "+I" << " "; 
                }else{
                    cout << max_profit[n][i][j] << " ";
                }
            }
            cout << endl;
        }
    }
}

void print_transpose(){
    for(int i=1; i<=n_slots; i++){
        cout << slot_val_transpose[i] << " ";
    }
    cout << endl;
}

int calculate_profit(int balls_left, int i, int j){
    // cout << "Calculating: " << "left=" << balls_left << ", i=" << i << ", j=" << j << endl;
    if (i <= 0 || j <= 0){
        return -INF;
    }else if (balls_left == 0){
        return 0;
    }else if (max_profit[balls_left][i][j] == -INF){
        // Invalid case
        return -INF;
    }else if (max_profit[balls_left][i][j] != INF){
        // Already seen
        return max_profit[balls_left][i][j];
    }

    int ball_idx = n_balls-balls_left+1;
    int curr_max = -INF;
    // cout << "\tCurrMax(" << ball_idx << ")=" << curr_max << endl;
    for(int u=i; u<=j-1; u++){
        int curr_profit = ball_val[ball_idx] * (slot_val_transpose[u]+slot_val_transpose[u+1]);
        curr_max = max(curr_max, -curr_profit+calculate_profit(balls_left-1, u+2, n_slots));
        // cout << "\tCurrMax(" << ball_idx << ")=" << curr_max << endl;
    }
    max_profit[balls_left][i][j] = curr_max;
    return max_profit[balls_left][i][j];
}

void reset_matrix(){
    memset(max_profit, 0x3f, MAX_BALLS*MAX_SLOTS*MAX_SLOTS*sizeof(int));
    for(int i=0; i<=n_slots; i++){
        for(int j=0; j<=n_slots; j++){
            // Lucro 0 se não há mais bolas a jogar
            max_profit[0][i][j] = 0;
            
            for(int n=1; n<=n_balls; n++){
                if (j <= i){
                    // Ultrapassa primeira bola jogada
                    max_profit[n][i][j] = -INF;
                }else if (j-i+1 < 2*n){
                    // Não há slots para as bolas restantes
                    // cout << "Não há: " << "i=" << i << ", j=" << j << ", n=" << n << endl;
                    max_profit[n][i][j] = -INF;
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    cin >> n_slots >> n_balls; 
    while(n_slots != 0 && n_balls != 0){
        memset(slot_val, 0, MAX_SLOTS*sizeof(int));
        memset(double_slot_val, 0, MAX_SLOTS*2*sizeof(int));
        memset(ball_val, 0, MAX_BALLS*sizeof(int));
        memset(slot_val_transpose, 0, MAX_SLOTS*sizeof(int));
        memset(max_profit, 0x3f, MAX_BALLS*MAX_SLOTS*MAX_SLOTS*sizeof(int));

        // Input
        for(int i=1; i<=n_slots; i++){
            int val; cin >> val;
            slot_val[i] = val;
            double_slot_val[i] = val;
            double_slot_val[n_slots+i] = val;
        }
        for(int i=1; i<=n_balls; i++){
            int val; cin >> val;
            ball_val[i] = val;
        }

        for(int i=0; i<=n_slots; i++){
            for(int j=0; j<=n_slots; j++){
                // Lucro 0 se não há mais bolas a jogar
                max_profit[0][i][j] = 0;
                
                for(int n=1; n<=n_balls; n++){
                    if (j <= i){
                        // Ultrapassa primeira bola jogada
                        max_profit[n][i][j] = -INF;
                    }else if (j-i+1 < 2*n){
                        // Não há slots para as bolas restantes
                        // cout << "Não há: " << "i=" << i << ", j=" << j << ", n=" << n << endl;
                        max_profit[n][i][j] = -INF;
                    }
                }
            }
        }
        // print_matrix();
        int curr_max = -INF;
        // cout << "\tCurrMax(" << 1 << ")=" << curr_max << endl;
        for(int i=1; i<=n_slots; i++){
            // Transpose the slot val vector, so it starts where the first ball is
            memset(slot_val_transpose, 0, MAX_SLOTS*sizeof(int));
            for(int k=0;k<n_slots; k++){
                slot_val_transpose[k+1] = double_slot_val[k+i];
            }
            // print_transpose();
            reset_matrix();

            int curr_profit = ball_val[1] * (slot_val_transpose[1]+slot_val_transpose[2]);
            curr_max = max(curr_max, -curr_profit+calculate_profit(n_balls-1, 3, n_slots));
            // cout << "\tCurrMax(" << 1 << ")=" << curr_max << endl;
        }
        // print_matrix();
        cout << curr_max << endl;
        // cout << endl;

        // print_mat_pesos();
        // print_mat();
        // used_neg = 0; used_nulls = 0;
        // cout << DTW(N,M) << endl;
        // print_mat();




        // cout << min_time(0, in_mana) << endl;
        cin >> n_slots >> n_balls; 
    }
    return 0;
}
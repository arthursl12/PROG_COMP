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
#define MAX 12345
#define MAX_DIFF 5
#define ii pair<int,int>

int M[MAX][6][6];
int weight[MAX];
int N;


/*
M[i][wa][wb] : possible to fit until gift 'i', the relative difference between
the two sides index wa and wb
*/

int knapsacks(int idx, int wa, int wb){
    if (abs(wa - wb) > MAX_DIFF){
        // Allocation not possible
        // cout << "Not possible: " << idx << "," << wa << "," << wb << endl;
        return 0;
    }

    // Normalize for indexing purposes
    int menor = min(wa,wb);
    wa = wa - menor;
    wb = wb - menor;

    // Leave wb as smaller, for indexing purposes
    if (wa < wb){
        int temp;
        temp = wa;
        wa = wb;
        wb = temp;
    }

    if (M[idx][wa][wb] != -1){
        // Already seen case
        // nothing to compute
    }else if (idx >= N+1){
        // Reached end of present list
        // cout << "End: " << idx << "," << wa << "," << wb << endl;
        M[idx][wa][wb] = 1;
    }else{
        // Try fitting on left or on right
        M[idx][wa][wb] = (knapsacks(idx+1, wa+weight[idx], wb) 
                         || knapsacks(idx+1, wa, wb+weight[idx]));
        // cout << "OK: " << idx << "," << wa << "," << wb << endl;
        
    }
    return M[idx][wa][wb];
}

// void print_mat(){
//     for(int i=1; i<=N; i++){
//         for(int j=0; j<=N; j++){
//             cout << M[i][j] << ",";
//         }
//         cout << endl;
//     }
//     cout << endl;
// }

// void print_vec(){
//     for(int i=1; i<=N; i++){
//         cout << vec[i] << ",";
//     }
//     cout << endl;
// }

int main() {
    ios_base::sync_with_stdio(false);

    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        memset(M, -1, (MAX)*(6)*(6)*sizeof(int));
        memset(weight, -1, (MAX)*sizeof(int));

        // Input
        cin >> N;
        for(int i=1; i<=N; i++){
            int in; cin >> in;
            weight[i] = in;
        }

        int result = knapsacks(1,0,0);
        if (result == 1){
            cout << "Feliz Natal!" << endl;
        }else{
            cout << "Ho Ho Ho!" << endl;
        }
    }
    return 0;
}


#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

#define INF 0x3f3f3f
#define MAX 50
#define ii pair<int,int>

int M[MAX][MAX];
int col_sum[MAX];

void print_matrix(int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << M[i][j];
        }
        cout << endl;
    }
}

bool try_mat(){
    memset(M, 0, (MAX)*(MAX)*sizeof(int));
        memset(col_sum, 0, (MAX)*sizeof(int));

        int n; cin >> n; int m; cin >> m;
        int a; cin >> a; int b; cin >> b;

        for(int i=0; i<n; i++){
            int line_sum = 0;
            for(int j=0; j<m; j++){
                if (line_sum < a && col_sum[j] < b){
                    M[i][j] = 1;
                    line_sum++;
                    col_sum[j]++;
                }
            }
        }

        for(int i=0; i<n; i++){
            int line_sum = 0;
            for(int j=0; j<m; j++){
                line_sum += M[i][j];
            }
            if(line_sum != a){
                cout << "NO" << endl;
                return 0;
            }
        }
        for(int j=0; j<m; j++){
            if(col_sum[j] != b){
                cout << "NO" << endl;
                return 0;
            }
        }
        cout << "YES" << endl;
        print_matrix(n,m);
        return 1;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        try_mat();
    }

    return 0;
}
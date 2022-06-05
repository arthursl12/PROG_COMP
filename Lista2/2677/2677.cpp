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
#define ii pair<int,int>
#define MAX 1234

int N;
int max_even[MAX][MAX];
int numbers[MAX];

int isEven(int i){
    return (numbers[i] % 2 == 0);
}

void print_vec(){
    for(int i=1; i<=2*N; i++){
        cout << numbers[i] << " ";
    }
    cout << endl;
}

void print_mat(){
    for(int i=1; i<=2*N; i++){
        for(int j=1; j<=2*N; j++){
            if (max_even[i][j] == -1){
                cout << "*" << ",";
            }else{
                cout << max_even[i][j] << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    ios_base::sync_with_stdio(false);
    
    cin >> N;
    while(N != 0){
        memset(numbers, -1, MAX*sizeof(int));

        for(int i=0; i<2*N; i++){
            int numb; cin >> numb;
            numbers[i] = numb;
        }

        // print_vec();
        // print_mat();
        for (int i=0; i<2*N; i++){
            for (int j=0; i+j<2*N; j++){
                int k = i+j;
                if (i == 0)
                    max_even[j][k] = 0;

                if (i % 2 == 0)
                    max_even[j][k] = min(max_even[j + 1][k], max_even[j][k -1]);
                else
                    max_even[j][k] = max(max_even[j + 1][k] + isEven(j), max_even[j][k - 1] + isEven(k));
            }
        }

        cout << max_even[0][2*N - 1] << endl;

        // cout << calculate(1,2*N, true) << endl;
        // print_mat();


        cin >> N;
    }
    return 0;
}
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
#include <cmath>

#define INF 0x3f3f3f
#define ii pair<int,int>

using namespace std;

#define MAX 100000

int bags[MAX];
// int matrix[MAX+1][MAX+1];
vector<map<int,int>> matrix;


void print_vector(int* v, int N){
    for(int i=0; i<N; i++){
        cout << v[i] << ", ";
    }
    cout << endl;
}

/*
C[i][j]: melhor solução com i partições e um conjunto de j elementos possíveis


C[i][j] =
    0   , j=0   (sem elementos, mínimo é 0)
    inf , i=0 && j!=0   (não há partições possíveis, mas há elementos)
    min (1<=r<=j) {
        max{C[i-1][r], sum(s=r -> j){P_s}}
    }
*/

int C(int i, int j){
    if(matrix[i].find(j) != matrix[i].end()){
        return matrix[i][j];
    }


    // Casos base
    if (j == 0){
        matrix[i][j] = 0;
        return 0;
    }else if(i == 0 && j != 0){
        matrix[i][j] = 0;
        return 0;
    }

    int min_case = INF;
    for(int r=1; r<=j; r++){
        int sum = 0;
        for (int s=r; s<=j; s++){
            sum += bags[s];
        }
        int val = max(C(i-1,r), sum);
        min_case = min(min_case, val);
    }
    matrix[i][j] = min_case;
    return min_case;
}


int main() {
    ios_base::sync_with_stdio(false);

    // Input
    int n_bags; cin >> n_bags;
    int n_competitors; cin >> n_competitors;
    int max_rate; cin >> max_rate;

    // Reading bags
    memset(bags, -1, MAX*sizeof(int));
    int total = 0;
    for(int i=0; i<n_bags; i++){
        int val; cin >> val;
        bags[i] = val;
        total += val;
    }
    // double media = ((double) total) / n_competitors;
    // print_vector(bags, n_bags);



    for(int i=0; i<MAX+1; i++){
        map<int,int> mymap;
        matrix.push_back(mymap); 
    }
    // int supermax = MAX+1;
    // memset(matrix, 0x3f, supermax*supermax*sizeof(int));
    cout << "Total Popcorn: " << C(n_competitors,n_bags) << endl;


    for(int i=0; i<=n_competitors; i++){
        map<int,int> mymap = matrix[i];
        cout << i << ":" << endl;
        for(ii p : mymap){
            cout << "\t" << p.first << "=" << p.second << endl;
        }
        cout << endl;
    }

    // Forward Greedy
    // int i = 0; 
    // int partial_sum = 0;
    // int max_eatenF = -1;
    // while(i < n_bags){
    //     if (partial_sum < media){
    //         // This competitor can eat another bag
    //         partial_sum += bags[i];
    //         i++;
    //     }else{
    //         // This competitor has eaten at least the average necessary
    //         max_eatenF = max(max_eatenF, partial_sum);
    //         partial_sum = 0;
    //     }
    // }
    // max_eatenF = max(max_eatenF, partial_sum);
    // // cout << max_eatenF << endl;

    // // Reverse Greedy
    // i = n_bags-1; 
    // partial_sum = 0;
    // int max_eatenB = -1;
    // while(i >= 0){
    //     if (partial_sum < media){
    //         // This competitor can eat another bag
    //         partial_sum += bags[i];
    //         i--;
    //     }else{
    //         // This competitor has eaten at least the average necessary
    //         max_eatenB = max(max_eatenB, partial_sum);
    //         partial_sum = 0;
    //     }
    // }
    // max_eatenB = max(max_eatenB, partial_sum);
    // // cout << max_eatenB << endl;

    // int total_seconds = ceil(((double)min(max_eatenB, max_eatenF))/max_rate);
    // cout << total_seconds << endl;


}
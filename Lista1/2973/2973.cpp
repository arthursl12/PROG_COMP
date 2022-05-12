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

#define MAX 123456

int bags[MAX];

void print_vector(int* v, int N){
    for(int i=0; i<N; i++){
        cout << v[i] << ", ";
    }
    cout << endl;
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
    double media = ((double) total) / n_competitors;
    // print_vector(bags, n_bags);

    // Forward Greedy
    int i = 0; 
    int partial_sum = 0;
    int max_eatenF = -1;
    while(i < n_bags){
        if (partial_sum < media){
            // This competitor can eat another bag
            partial_sum += bags[i];
            i++;
        }else{
            // This competitor has eaten at least the average necessary
            max_eatenF = max(max_eatenF, partial_sum);
            partial_sum = 0;
        }
    }
    max_eatenF = max(max_eatenF, partial_sum);
    // cout << max_eatenF << endl;

    // Reverse Greedy
    i = n_bags-1; 
    partial_sum = 0;
    int max_eatenB = -1;
    while(i >= 0){
        if (partial_sum < media){
            // This competitor can eat another bag
            partial_sum += bags[i];
            i--;
        }else{
            // This competitor has eaten at least the average necessary
            max_eatenB = max(max_eatenB, partial_sum);
            partial_sum = 0;
        }
    }
    max_eatenB = max(max_eatenB, partial_sum);
    // cout << max_eatenB << endl;

    int total_seconds = ceil(((double)min(max_eatenB, max_eatenF))/max_rate);
    cout << total_seconds << endl;


}
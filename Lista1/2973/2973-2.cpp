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
int max_rate;
int n_competitors;
int n_bags;

void print_vector(int* v, int N){
    for(int i=0; i<N; i++){
        cout << v[i] << ", ";
    }
    cout << endl;
}

bool try_divide(int target_popcorn, int n_compet, int n_bags, int& max_eaten){
    // Forward Greedy
    int i = 0; 
    int used_compet = 1;

    int partial_sum = 0;
    int max_eatenF = -1;
    while(i < n_bags && used_compet <= n_compet){
        if (partial_sum + bags[i] <= target_popcorn){
            // This competitor can eat another bag
            partial_sum += bags[i];
            i++;
        }else{
            // This competitor has eaten the max amount possible withing this time limit
            max_eatenF = max(max_eatenF, partial_sum);
            partial_sum = 0;
            used_compet++;
        }
    }
    max_eatenF = max(max_eatenF, partial_sum);
    if (used_compet > n_compet){
        return false;
    }else{
        max_eaten = max_eatenF;
        return true;
    }
    // cout << max_eatenF << endl;
}

int binary_search(int lb_popcorn, int ub_popcorn){
    // cout << "BS: [" << lb_popcorn << "," << ub_popcorn << "]" << endl;
    int max_eaten;
    if (try_divide(lb_popcorn, n_competitors, n_bags, max_eaten)){
        // Lower bound works: this is the minimum
        return max_eaten;
    }
    
    // Binary search
    int meio = ((double)lb_popcorn + ub_popcorn) / 2;
    if (try_divide(meio, n_competitors, n_bags, max_eaten)){
        // Search on lower half (including half)
        return binary_search(lb_popcorn, meio);
    }else{
        // Search on upper half (excluding half)
        return binary_search(meio+1, ub_popcorn);
    }
}


int main() {
    ios_base::sync_with_stdio(false);

    // Input
    cin >> n_bags;
    cin >> n_competitors;
    cin >> max_rate;

    // Reading bags
    memset(bags, -1, MAX*sizeof(int));
    int total = 0;
    int max_bag = -1;
    for(int i=0; i<n_bags; i++){
        int val; cin >> val;
        bags[i] = val;
        total += val;
        max_bag = max(max_bag, val);
    }

    // Someone will eat the largest bag alone
    // This is the theoretical minimum amount of someone to eat
    int theoretical_min_time = ceil( ((double) max_bag) / max_rate );
    int theoretical_min_popcorn = theoretical_min_time * max_rate;

    // This is the theoretical max amount of someone to eat (aka, only 1 competitor)
    int theoretical_max_time = ceil( ((double) total) / max_rate );
    int theoretical_max_popcorn = theoretical_max_time * max_rate;

    // Binary search to find minimum


    int max_eaten = binary_search(theoretical_min_popcorn,theoretical_max_popcorn);
    int time = ceil( ((double) max_eaten) / max_rate );
    cout << time << endl;

    
    // // Try to find the minimum amount of time
    // int target_time = theoretical_min_time;
    // int target_popcorn = theoretical_min_popcorn;
    // int max_eaten;
    // bool possible = false;
    // while(!possible){
    //     possible = try_divide(target_popcorn, n_competitors, n_bags, max_eaten);
    //     target_time++;  // Add a second to target time
    //     target_popcorn = target_time * max_rate; // Find new max amount of popcorn that can be eaten
    // }
    // cout << target_time-1 << endl;


}
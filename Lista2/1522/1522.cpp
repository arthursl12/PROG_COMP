#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <deque>

using namespace std;

#define INF 0x3f3f3f
#define MAX_CARDS 101
#define N_STACKS 3
#define ii pair<int,int>

int cards[MAX_CARDS+1][N_STACKS+1];
int possibilities[MAX_CARDS+1][MAX_CARDS+1][MAX_CARDS+1];

int play(int idx1, int idx2, int idx3){
    // cout << "Trying: " << idx1 << ", " << idx2 << ", " << idx3 << endl;
    // if (idx1 < 1 || idx2 < 1 || idx3 < 1){ return 0; }
    if (idx1 < 0 && idx2 < 0 && idx3 < 0){ return 0; }
    // cout << "Trying: " << idx1 << ", " << idx2 << ", " << idx3 << endl;
    // cout << "\t: " << cards[idx1][1] << ", " << cards[idx2][2] << ", " << cards[idx3][3] << endl;

    // Already seen case
    if ((idx1 >= 1 && idx2 >= 1 && idx3 >= 1) && possibilities[idx1][idx2][idx3] != -1){ 
        return possibilities[idx1][idx2][idx3]; 
    }


    // Base case: end of all stacks
    if (idx1 == 0 && idx2 == 0 && idx3 == 0){ 
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3];
    }
    

    // The top card of a stack is multiple of 3
    if (idx1 >= 1 && cards[idx1][1] % 3 == 0 && play(idx1-1,idx2,idx3)){
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3];
    }
    if (idx2 >= 1 && cards[idx2][2] % 3 == 0 && play(idx1,idx2-1,idx3)){
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3];
    }
    if (idx3 >= 1 && cards[idx3][3] % 3 == 0 && play(idx1,idx2,idx3-1)){
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3]; 
    }

    // Some of two of them is multiple of 3
    if ((idx1 >=1 && idx2 >= 1) && ((cards[idx1][1] + cards[idx2][2]) % 3 == 0) && play(idx1-1,idx2-1,idx3)){
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3]; 
    }
    if ((idx1 >=1 && idx3 >= 1) && ((cards[idx1][1] + cards[idx3][3]) % 3 == 0) && play(idx1-1,idx2,idx3-1)){
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3]; 
    }
    if ((idx2 >=1 && idx3 >= 1) &&  ((cards[idx2][2] + cards[idx3][3]) % 3 == 0) && play(idx1,idx2-1,idx3-1)){
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3]; 
    }

    // The sum of all three is multiple of 3
    if ((idx1 >=1 && idx2 >=1 && idx3 >= 1) && (cards[idx1][1] + cards[idx2][2] + cards[idx3][3]) % 3 == 0 && play(idx1-1,idx2-1,idx3-1)){
        possibilities[idx1][idx2][idx3] = 1;
        return possibilities[idx1][idx2][idx3]; 
    }

    // If we got here, there is no way to solve
    possibilities[idx1][idx2][idx3] = 0;
    return possibilities[idx1][idx2][idx3];
}

void print_cards(int NC){
    for(int i=NC; i>=1; i--){
            for(int j=1; j<=N_STACKS; j++){
                cout << cards[i][j] << ",";
            }
            cout << endl;
        }
        cout << endl;
}


int main() {
    ios_base::sync_with_stdio(false);

    int N_cards;
    cin >> N_cards;
    while(N_cards != 0){
        memset(cards, -1, (MAX_CARDS+1)*(N_STACKS+1)*sizeof(int));
        memset(possibilities, -1, (MAX_CARDS+1)*(MAX_CARDS+1)*(MAX_CARDS+1)*sizeof(int));

        // Input
        for(int i=N_cards; i>=1; i--){
            for(int j=1; j<=N_STACKS; j++){
                int card; cin >> card;
                cards[i][j] = card;
                // cout << "(" << i << "," << j << ") = " << card << endl;
            }
        }
        // print_cards(N_cards);

        int possible = play(N_cards, N_cards, N_cards);
        cout << possible << endl;
        cin >> N_cards;
    }
    return 0;
}
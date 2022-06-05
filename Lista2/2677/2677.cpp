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
#define ii pair<int,int>


#define MAX 1234

int N;
int max_even[MAX][MAX][2];
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
            if (max_even[i][j][true] == -1){
                cout << "*" << ",";
            }else{
                cout << max_even[i][j][true] << ",";
            }

            if (max_even[i][j][false] == -1){
                cout << "*" << "  ";
            }else{
                cout << max_even[i][j][false] << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int max_score;
void run_game(int i, int j, bool vez, int curr_score){
    // cout << "Round(" << vez << "): " << i << "," << j << ", sc=" << curr_score << endl; 
    if(vez){
        if(i == j){
            curr_score += isEven(i);
            max_score = max(max_score,curr_score);
        }else if(isEven(i) && !isEven(j)){
            // Choose i
            run_game(i+1, j, !vez, curr_score+1);
        }else if(isEven(i) && !isEven(j)){
            // Choose j
            run_game(i, j-1, !vez, curr_score+1);
        }else{
            // Try each
            run_game(i+1, j, !vez, curr_score+isEven(i));
            run_game(i, j-1, !vez, curr_score+isEven(j));
        }
    }else{
        if(i == j){
            max_score = max(max_score,curr_score);
        }else if(isEven(i) && !isEven(j)){
            // P2 Choose i
            run_game(i+1, j, !vez, curr_score);
        }else if(isEven(i) && !isEven(j)){
            // P2 Choose j
            run_game(i, j-1, !vez, curr_score);
        }else{
            // Try each
            run_game(i+1, j, !vez, curr_score);
            run_game(i, j-1, !vez, curr_score);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    
    cin >> N;
    while(N != 0){
        max_score = 0;
        memset(numbers, -1, MAX*sizeof(int));

        for(int i=1; i<=2*N; i++){
            int numb; cin >> numb;
            numbers[i] = numb;
        }
        // print_vec();
        // print_mat();
        run_game(1,2*N,true,0);
        cout << max_score << endl;

        // cout << calculate(1,2*N, true) << endl;
        // print_mat();


        cin >> N;
    }
    return 0;
}
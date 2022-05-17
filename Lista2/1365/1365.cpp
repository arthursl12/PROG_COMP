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
#define MAX 333
#define ii pair<int,int>


int vazios[MAX][MAX];

void print_mat(int R, int C){
    for(int i=0; i<=R; i++){
        for(int j=0; j<=C; j++){
            cout << vazios[i][j] << ",";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);

    int R, C, K;
    cin >> R >> C >> K;
    while(R != 0){
        memset(vazios, 0, (MAX)*(MAX)*sizeof(int));

        // Input
        for(int i=1; i<=R; i++){
            for(int j=1; j<=C; j++){
                char pos; cin >> pos;
                if (pos == '.'){
                    vazios[i][j] = vazios[i][j-1] + 1;
                }else{
                    vazios[i][j] = vazios[i][j-1];
                }
            }
        }
        // print_mat(R,C);


        // Try all rectangles intelligently
        int result = INF;
        for(int min_col=1; min_col<=C; min_col++){
            for(int max_col=1; max_col<=C; max_col++){
                if ((max_col-min_col+1)*R < K){
                    // There aren't enough seats in current rectangle
                    continue;
                } 

                // Try all lines possible
                int total_empty = 0;
                deque<int> empties_in_window;
                for(int row=1; row<=R; row++){
                    int row_seats = vazios[row][max_col] - vazios[row][min_col-1];
                    empties_in_window.push_back(row_seats);
                    total_empty += empties_in_window.back();

                    // Try to reduce rectangle size
                    while(total_empty >= K){
                        int total_space_occupied = (max_col-min_col+1)*empties_in_window.size();
                        result = min(result, total_space_occupied);
                        total_empty = total_empty - empties_in_window.front();
                        empties_in_window.pop_front();
                    }
                }
            }
        }
        cout << result << endl;
        cin >> R >> C >> K;
    }
    return 0;
}
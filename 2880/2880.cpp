#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>

using namespace std;

char matrix[12345][12345];

int main() {
    ios_base::sync_with_stdio(false);

    string message; cin >> message;
    int N = message.size();

    string crib; cin >> crib;
    int n = crib.size();

    int used = N-n+1;
    vector<bool> valid(used, true);

    // Fill with invalid
    for(int i=0; i<used; i++){
        for(int j=0; j<N; j++){
            matrix[i][j] = '*';
        }
    }
    
    // Fill with word and offset
    int offset = 0;
    for(int i=0; i<used; i++){
        for(int j=0; j<n; j++){
            matrix[i][offset+j] = crib[j];
        }
        offset++;
    }

    // Print
    // for(int i=0; i<used; i++){
    //     for(int j=0; j<N; j++){
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;


    // Compare
    for(int i=0; i<used; i++){
        for(int j=0; j<N; j++){
            if (!valid[i]){
                continue;
            }else if (matrix[i][j] == '*'){
                continue;
            }else if (matrix[i][j] == message[j]){
                valid[i] = false;
            }
        }
    }

    int total = 0;
    for(int i=0; i<used; i++){
        total += valid[i];
        // cout << valid[i] << " ";
    }
    cout << total << endl;


    // long long int total = 0; 
    // for (int i=0; i<number.size(); i++){
    //     char C = number[i];
    //     int n = stoi(string(1,C));
    //     total += n;
    // }
    // cout << total % 3 << endl;
    return 0;
}
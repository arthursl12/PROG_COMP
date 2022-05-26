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
int max_even_p2[MAX][MAX][2];
int numbers[MAX];


int isEven(int i){
    return (numbers[i] % 2 == 0);
}

int calculate(int i, int j, bool vez){
    cout << "i=" << i << ",j=" << j << ", vez=" << vez << endl;
    if (i < 0 || j < 0 || j < i || i > 2*N || j > 2*N ){
        return -1;
    }
    if (max_even[i][j][vez] != -1){
        cout << "\tMax=" << max_even[i][j][vez] << endl;
        return max_even[i][j][vez];
    }

    // Calcula
    if (vez){
        // É a vez dele
        if (i == j){
            max_even[i][j][vez] = isEven(i);
        }else{
            max_even[i][j][vez] = max(max_even[i][j][vez], isEven(i)+calculate(i+1,j,!vez));
            max_even[i][j][vez] = max(max_even[i][j][vez], isEven(j)+calculate(i,j-1,!vez));
        }
        
        
    }else{
        // Não é a vez dele
        if (i == j){
            max_even[i][j][vez] = 0;
        }else{
            max_even[i][j][vez] = max(max_even[i][j][vez], calculate(i+1,j,!vez));
            max_even[i][j][vez] = max(max_even[i][j][vez], calculate(i,j-1,!vez));
        }
        
        
    }
    cout << "\tMax=" << max_even[i][j][vez] << endl;
    return max_even[i][j][vez];
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



int main() {
    ios_base::sync_with_stdio(false);
    
    cin >> N;
    while(N != 0){
        memset(max_even, -1, MAX*MAX*2*sizeof(int));
        memset(max_even_p2, -1, MAX*MAX*2*sizeof(int));
        memset(numbers, -1, MAX*sizeof(int));

        for(int i=1; i<=2*N; i++){
            int numb; cin >> numb;
            numbers[i] = numb;
        }
        // print_vec();
        // print_mat();

        for(int i=1; i<=2*N; i++){
            max_even[i][i][true] = isEven(i);
            max_even[i][i][false] = 0;

            max_even_p2[i][i][true] = isEven(i);
            max_even_p2[i][i][false] = 0;
        }

        for(int j=1; j<=2*N; j++){
            for(int i=j; i>=1; i--){
                if (i == j) continue;

                max_even[i][j][true] = max(
                    isEven(i)+max_even[i+1][j][false],
                    isEven(j)+max_even[i][j-1][false]
                );
                max_even_p2[i][j][true] = max(
                    isEven(i)+max_even_p2[i+1][j][false],
                    isEven(j)+max_even_p2[i][j-1][false]
                );

                // P1 doesn't play this round
                if (isEven(i)+max_even_p2[i+1][j][true] > isEven(j)+max_even_p2[i][j-1][true]){
                    // P2 will choose 'i'
                    max_even[i][j][false] = max_even[i+1][j][true];
                }else if(isEven(i)+max_even_p2[i+1][j][true] < isEven(j)+max_even_p2[i][j-1][true]){
                    // P2 will choose 'j'
                    max_even[i][j][false] = max_even[i][j-1][true];
                }else{
                    max_even[i][j][false] = max(max_even[i][j-1][true], max_even[i+1][j][true]);
                }

                // P2 doesn't play this round
                if (isEven(i)+max_even[i+1][j][true] > isEven(j)+max_even[i][j-1][true]){
                    // P1 will choose 'i'
                    max_even_p2[i][j][false] = max_even_p2[i+1][j][true];
                }else if(isEven(i)+max_even[i+1][j][true] < isEven(j)+max_even[i][j-1][true]){
                    // P1 will choose 'j'
                    max_even_p2[i][j][false] = max_even_p2[i][j-1][true];
                }else{
                    max_even_p2[i][j][false] = max(max_even_p2[i][j-1][true], max_even_p2[i+1][j][true]);
                }
            }
        }


        cout << max_even[1][2*N][true] << endl;

        // cout << calculate(1,2*N, true) << endl;
        // print_mat();


        cin >> N;
    }
    return 0;
}
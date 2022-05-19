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
#define MAX 2222
#define ii pair<int,int>
#define ll long long

int custo[MAX]; // Qual o menor custo para dar i de dano?
int custo_copy[MAX]; 

int HP,N;

void print_vec(int size){
    for(int i=0; i<=size; i++){
        if (custo[i] == 1061109567){
            cout << "INF" << ",";
        }else{
            cout << custo[i] << ",";
        }
        
    }
    cout << endl;
}



int main() {
    ios_base::sync_with_stdio(false);
    while(cin >> N >> HP){
        memset(custo,0x3f, (MAX)*sizeof(int));
        custo[0] = 0; // Caso base
        for(int k=0; k<N; k++){
            int dmg; cin >> dmg;
            int mana; cin >> mana;

            for(int i=MAX-1; i>=dmg; i--){
                custo[i] = min(custo[i], custo[i-dmg]+mana);
            }

            // for(int i=dmg; i<=(MAX-1); i++){
            //     custo[i] = min(custo[i], custo[i-dmg]+mana);
            //     // print_vec(15);
            // }
        }

        int minimum = INF;
        for(int i=HP; i<MAX; i++){
            minimum = min(minimum, custo[i]);
        }
        if (minimum != INF){
            cout << minimum << endl;
        }else{
            cout << -1 << endl;
        }
        
    }
    return 0;
}



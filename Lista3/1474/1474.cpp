#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

#define INF 0x3f3f3f3f
#define MAX 123456
#define ii pair<int,int>
#define ll long long
// #define MOD 1000000LL
#define MOD 1000000

#define mat_t vector<vector<ll>>

mat_t identity_matrix;
mat_t base_matrix;

// Matrix multiplication with MOD
mat_t mult(mat_t& m1, mat_t& m2){
    mat_t m3;
    // Reset output matrix
    for(int i=0; i<2; i++){
        vector<ll> v;
        for(int j=0; j<2; j++){
            v.push_back(0);
        }
        m3.push_back(v);
    }

    // Multiply 
    for(int k=0; k<2; k++){
        for(int i=0; i<2; i++){
            for(int j=0; j<2; j++){
                m3[i][j] = (m3[i][j] + m1[i][k] * m2[k][j]) % MOD;
            }
        }
    }
    return m3;
}

// Matrix fast exponentiation
mat_t expo(ll exponent){
    if(exponent == 0){
        return identity_matrix;
    }
    if (exponent == 1){
        return base_matrix;
    }
    
    if (exponent % 2 == 0){
        mat_t tmp = expo(exponent/2);
        return mult(tmp,tmp);
    }else{
        mat_t tmp = expo(exponent-1);
        return mult(base_matrix, tmp);
    }
}

void print_result(mat_t& result, ll mic_colors, ll bus_colors){
    ll case1 = mic_colors % MOD;
    ll case2 = ((mic_colors * mic_colors % MOD) + bus_colors % MOD) % MOD;
    ll number = (case1*result[0][0] + case2*result[0][1]) % MOD;

    // Print with padding
    std::cout << std::setfill('0') << std::setw(6) << number << endl;;
}

int main() {
    ios_base::sync_with_stdio(false);

    ll total_length,mic_colors,bus_colors;
    while(cin >> total_length >> mic_colors >> bus_colors){
        // Cleaning input
        total_length = total_length/5;
        mic_colors = mic_colors % MOD;
        bus_colors = bus_colors % MOD;
        
        // Define identity
        for(int i=0; i<2; i++){
            vector<ll> v;
            for(int j=0; j<2; j++){
                v.push_back((i==j));
            }
            identity_matrix.push_back(v);
        }

        // Define base_matrix (over-diagonal matrix)
        for(int i=0; i<2; i++){
            vector<ll> v;
            for(int j=0; j<2; j++){
                v.push_back((i+1==j));
            }
            base_matrix.push_back(v);
        }
        base_matrix[1][0] = bus_colors;
        base_matrix[1][1] = mic_colors;

        // Find result
        mat_t result = expo(total_length-1);
        print_result(result, mic_colors, bus_colors);
    }
    return 0;
}

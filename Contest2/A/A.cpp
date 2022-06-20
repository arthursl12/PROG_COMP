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
#define MAX 40
#define ii pair<int,int>
#define ll long long


int main() {
    ios_base::sync_with_stdio(false);
    
    int n_tests; cin >> n_tests;
    for(int iiii = 0; iiii < n_tests; iiii++){
        ll N; cin >> N;

        ll soma = 3;
        ll k = 2;
        while(soma == 0 || N % soma != 0){
            soma += pow(2,k);
            k++;
        }
        ll x = N / soma;
        cout << x << endl;
    }
    return 0;
}
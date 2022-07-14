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
#include <unordered_map>

using namespace std;

#define INF 0x3f3f3f3f
#define MAX 112345
#define ii pair<int,int>
#define ll long long


int main() {
    ios_base::sync_with_stdio(false);
    
    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        ll price; cin >> price;

        if (price == 1){
            cout << 0 << endl;
        }else{
            ll left_price = price;
            ll tens = 0;
            while (left_price != 0){
                left_price = left_price / 10;
                tens++;
            }
            // tens--;
            cout << fixed << std::setprecision(0);
            cout << price - pow(10, tens-1) << endl;
        }
    }
    return 0;

}


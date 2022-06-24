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

ll pot(ll a, ll b, ll mod){
    if (b == 0){ return 1; }
    ll x = pot(a, b/2, mod);
    x *= x;
    x %= mod;

    if (b % 2 != 0){
        x *= a;
        x %= mod;
    }   
    return x;
}

ll phi(ll n){
    // Euler phi function
    ll result = n;
    for(int i=2; i<=sqrt(n); i++){
        if (n % i == 0) {
            while(n % i == 0){
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

ll inverso_modular(ll a, ll mod){
    // Via T. Euler
    return pot(a, phi(mod) - 1, mod); 
}

int main() {
    ios_base::sync_with_stdio(false);

    ll N,E,enc_msg;
    while(cin >> N >> E >> enc_msg){
        ll msg = pot(enc_msg, inverso_modular(E, phi(N)), N);
        cout << msg << endl;
    }
    return 0;


    return 0;
}
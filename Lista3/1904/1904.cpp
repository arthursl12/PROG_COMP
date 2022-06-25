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
#define MAX 11234567
#define ii pair<int,int>
#define ll long long

vector<ll> isPrime(MAX, true);

bool calc (ll n, ll k) {
    // Parity for C(n,k)
    if ((k & (n-k))){
        return 0;
    }else {
        return 1;
    }
}

void generate_primes(){
    for(int i=2; i<MAX; i++){
        if(isPrime[i]){
            int j=2;
            while(i*j < MAX){
                isPrime[i*j] = false;
                j++;
            }
        }
    }
    isPrime[0] = isPrime[1] = 0;
}

int main() {
    ios_base::sync_with_stdio(false);

    ll A, B; cin >> A >> B;
    if (A > B) {
        // Swap A and B if they A is bigger
        ll tmp = A;
        A = B;
        B = tmp;
    }else if (A == B){
        // If they are equal, we can't decide
        cout << "?" << endl;
        return 0;
    }

    generate_primes();

    // Filling vector 'isPrime'
    for(int i=1; i<MAX; i++){
        isPrime[i] += isPrime[i-1];
    }

    // Stars and Bars Theorem
    ll N = B - A;
    ll ll0 = 0;
    ll R = isPrime[B] - isPrime[max(ll0, A-1)];
    bool result = calc(N + R - 1, N);

    // Print the result
    if (result){
        cout << "Alice" << endl;
    }else{
        cout << "Bob" << endl;
    }
    return 0;
}
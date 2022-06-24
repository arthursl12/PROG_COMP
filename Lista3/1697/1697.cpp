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
#include <bitset>

using namespace std;

#define INF 0x3f3f3f3f
#define MAX 1234567
#define MAX_P 12345678
#define MAX_PP 16000002
#define ii pair<int,int>
#define ll long long

// unordered_map<int,int> numbers_in;
set<int> numbers_in;

int all_primes[MAX_P];
bitset<MAX_PP> isPrime;

int find_all_primes(){
    // First two primes
    all_primes[0] = 1;
    all_primes[1] = 2;
    int prime_counter = 2;

    // Set all numbers as primes, until proven the opposite
    isPrime.set();

    // All evens are not primes
    for (ll i = 4; i <= MAX_PP-2; i += 2){
        isPrime.reset(i);
    }

    // Erathostenes' Sieve
    for(ll i=3; prime_counter<MAX_P && i<=MAX_PP-2; i+=2){
        if(isPrime[i]){
            all_primes[prime_counter] = i;
            prime_counter++;
            for(ll j=i*i; j<=MAX_PP-2; j+=i){
                // All multiples of i are not prime
                isPrime.reset(j);
            }
        }
    }

    return prime_counter;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    memset(all_primes, 0, MAX_P*sizeof(int));
    
    int prime_count = find_all_primes();

    int n_cases; cin >> n_cases;
    for(int iiii=0; iiii<n_cases; iiii++){

        // Input
        int n_numbers; cin >> n_numbers;
        numbers_in.clear();
        for(int i=0; i<n_numbers; i++){
            int num; cin >> num;
            numbers_in.insert(num);
        }

        // Find the largest prime not present in the list
        for(int i=0; i<=prime_count; i++){
            if(numbers_in.find(all_primes[i]) == numbers_in.end()){
                // prime[i] is not in list, so it cannot be generated 
                cout << (all_primes[i] - 1) << endl;
                break;
            }
        }
    }
    return 0;
}
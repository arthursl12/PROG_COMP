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

bool isprime[MAX];

bool superPrime(int N){
    while(N >= 10){
        int remainder = N % 10;
        N = N / 10;
        if (isprime[remainder] == false){
            return false;
        }
    }
    return isprime[N];
}

int main() {
    ios_base::sync_with_stdio(false);

    memset(isprime, true, MAX*sizeof(bool));

    // Find all primes in the set
    isprime[0] = false;
    isprime[1] = false;
    isprime[2] = true;
    for(int i=3; i<MAX; i++){
        if(i % 2 == 0){
            isprime[i] = false;
            continue;
        }
        for(int j=3; j<=sqrt(i); j+=2){
            if (i % j == 0){
                isprime[i] = false;
                break;
            }
        }
    }

    // Input
    int in; 
    while(cin >> in){
        if (isprime[in] && superPrime(in)){
            cout << "Super" << endl;
        }else if (isprime[in]){
            cout << "Primo" << endl;
        }else{
            cout << "Nada" << endl;
        }
    }


    return 0;
}
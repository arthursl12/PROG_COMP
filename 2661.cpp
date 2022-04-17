#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

#define INF 0x3f3f3f
#define MAX 1234
#define ii pair<int,int>
#define ll long long int 


ll fact(ll n){
     return (n==0) || (n==1) ? 1 : n* fact(n-1);
}

ll combination(ll n, ll c){
    return ((fact(n)) / ((fact(c) * (fact(n-c)))));
}

int main(){
    long long int N; cin >> N;
    long long int raizN = sqrt(N); 

    set<long long int> divisores_primos;
    // int divisores_primos = 0;

    // Corner case
    if(N <= 1){
        cout << 0 << endl;
        return 0;
    }

    // Fatora em números primos
    while (N % 2 == 0){
        divisores_primos.insert(2);
        // divisores_primos++;
        N = N/2;
    }
    for(int i=3; i<raizN; i = i+2){
        while(N % i == 0){
            divisores_primos.insert(i);
            N = N/i;
        }
    }
    if(N > 1){
        // O próprio é primo
        divisores_primos.insert(N);
    }

    // Soma as combinações menores
    int i = 2;
    int total = 0;
    int size = divisores_primos.size();
    while (i <= size){
        total += combination(size, i);
        i++;
    }
    cout << total << endl;

    return 0;
}
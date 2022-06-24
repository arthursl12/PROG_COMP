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
#define MAX 2000001
#define ii pair<int,int>
#define ll long long


bool isprime[MAX];      // if 'i' is prime
uint divs[MAX];         // # divisors 'i' has
uint hipprimes[MAX];    // # hiperprimes until 'i'

int main() {
    ios_base::sync_with_stdio(false);

    // Initialization
    memset(isprime, true, MAX*sizeof(bool));
    memset(divs, 0, MAX*sizeof(uint));
    memset(hipprimes, 0, MAX*sizeof(uint));

    // Find how many divisors + Erathostenes Sieve
    for(int i=2; i<MAX; i++){
        if(isprime[i] == true){
            divs[i] = 2; 

            // Erathostenes Sieve
            int divs_counter, size;
            for(int j=2*i; j<MAX; j+=i){
                isprime[j] = false;
                
                // Find divisors (fast)
                // https://pt.stackoverflow.com/questions/302055/como-encontrar-os-divisores-de-um-n%C3%BAmero-de-forma-r%C3%A1pida
                divs_counter = 0;
                size = j;
                while(size % i == 0){
                    size = size / i;
                    divs_counter++;
                }

                // Store the divisors found
                if (divs[j] == 0){
                    divs[j] = divs_counter+1;
                }else{
                    divs[j] = divs[j]*(divs_counter+1);
                }
            }
        }
    }

    // Calculate hiperprimes
    hipprimes[1] = 0;
    for(int i=2; i<=MAX; i++){
        hipprimes[i] = hipprimes[i-1];
        if(isprime[divs[i]]){
            hipprimes[i]++;
        }
    }

    // Read input
    uint N; 
    while(cin >> N){
        cout << hipprimes[N] << endl;
    }
    return 0;
}
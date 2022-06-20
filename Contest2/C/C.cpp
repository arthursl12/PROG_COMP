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
#define MAX 1234567
#define ii pair<int,int>
#define ll long long

int N;
int pi[MAX], used[MAX];

void preffix_function(string& text){
    int j=0;
    for(int i=2; i<=N; i++){
        while(j > 0 && (text[i] != text[j+1])) 
            j = pi[j];
        if(text[i] == text[j+1]) 
            j++;
        pi[i] = j;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    
    string text; cin >> text;
    N = text.size();

    for(int i=0; i<=N; i++){
        used[pi[i]] = 1;
    }
    used[0] = 0;

    for(int i=N; i>0; i=pi[i]){
        if (used[pi[i]]){
            for(int j=1; j<= )
        }
    }

    // Count substrings
    // Small constants, may do it via brute force
    int substrings = 0;
    for(int i=0; i<text.size(); i++){
        if(text[i] == patt[0]){
            int k;
            for(k=0; k<patt.size(); k++){
                if(text[i+k] != patt[k]){
                    break;
                }
            }

            if(k == patt.size()){
                substrings++;
                i=i+k-1;
            }
        }
    }

    cout << substrings << endl;
    return 0;
}
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
    
    string text; cin >> text;
    string patt; cin >> patt;

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
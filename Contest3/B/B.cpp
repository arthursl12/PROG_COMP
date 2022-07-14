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
        string str; cin >> str;

        int days=0;
        set<char> chs;
        for(char c : str){
            chs.insert(c);
            if(chs.size() > 3){
                chs.clear();
                days++;
                chs.insert(c);
            }
        }
        
        if (!chs.empty()){
            days++;
        }   
        cout << days << endl;
    }
    return 0;

}


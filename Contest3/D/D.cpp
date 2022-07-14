

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
#define MAX 212345
#define ii pair<int,int>
#define ll long long

int removed[MAX];


int main() {
    ios_base::sync_with_stdio(false);
    
    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        string str; cin >> str;
        ll max_price; cin >> max_price;

        // Find current value of string
        ll str_sum = 0;
        for(int i=0; i<str.size(); i++){
            str_sum += (str[i] - 'a' + 1);
            removed[i] = 0;
        }
        // cout << str << "," << str_sum << ", max=" << max_price << endl;

        // Try eliminating
        for(int j=26; j>=1; j--){
            char current = (char) (j + 'a' - 1);
            for(int i=0; i<str.size(); i++){
                if(!removed[i] && str[i] == current && str_sum > max_price){
                    str_sum = str_sum - j;
                    removed[i] = 1;
                }
            }
        }
        // cout << str << "," << str_sum << ", max=" << max_price << endl;

        // Print remaining string
        for(int i=0; i<str.size(); i++){
            if (!removed[i]){
                cout << str[i];
            }
        }
        cout << endl;
    }
    return 0;

}


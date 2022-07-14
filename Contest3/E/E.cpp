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

vector<int> all[MAX];
unordered_map<int, int> book, num;

bool find(int x, int k){
    if(!book[x]){
        book[x] = k;
    }else{
        if(book[x] == k)
            return 1;
        else
            return 0;
    }

    for(int i=0; i<all[x].size(); i++){
        int current = all[x][i];
        if(!find(current, 3-k))
            return 0;
    }
    return 1;
}


int main() {
    ios_base::sync_with_stdio(false);
    
    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        book.clear(); num.clear();

        // Input dominoes
        int n_dom; cin >> n_dom;
        for(int i=1; i<=n_dom; i++){
            int a,b; cin >> a >> b;
            num[a] += 1;
            num[b] += 1;

            all[a].push_back(b);
            all[b].push_back(a);
        }

        bool flg = true;
        for(int i=1; i<=n_dom; i++){
            if(!book[i]){
                if (!find(i,1)){
                    flg = false;
                }
            }
            if(num[i] != 2){
                flg = false;
            }
            all[i].clear();
        }

        if(flg){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;

}


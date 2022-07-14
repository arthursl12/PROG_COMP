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

int all[MAX], all2[MAX];
unordered_map<int, int> book;

int main() {
    ios_base::sync_with_stdio(false);
    
    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        book.clear(); 
        int n; cin >> n;

        // Input A
        for(int i=1; i<=n; i++){
            int a; cin >> a;
            all[i] = a;
            while(all[i]%2 == 0 && all[i]){
                all[i] /= 2;
            }
            book[all[i]] += 1;
        }

        // Input B
        for(int i=1; i<=n; i++){
            int b; cin >> b;
            all2[i] = b;
            while(all2[i]%2 == 0 && all2[i]){
                all2[i] /= 2;
            }
            while(all2[i]){
                if(book[all2[i]]){
                    book[all2[i]] -= 1;
                    break;
                }else{
                    all2[i] = all2[i] / 2;
                }
            }
        }

        bool flg = true;
        for(int i=1; i<=n; i++){
            if(book[all[i]]){
                flg = false;
                break;
            }
        }

        if(flg){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;

}


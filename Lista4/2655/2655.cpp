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
#define MAX 112345
#define ii pair<int,int>
#define ll long long

set<int> monsters[51];
int positions[MAX];

int op1(int L, int R, int n_monsters){
    int total = 0;
    for(int i=1; i<=n_monsters; i++){
        auto it = monsters[i].lower_bound(L);
        if (it == monsters[i].end()){
            continue;
        }
        if (*it <= R){
            total++;
        }
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);

    int road_size, n_operations, n_monsters;
    cin >> road_size >> n_operations >> n_monsters;

    // Input monsters in each location
    for(int i=1; i<=road_size; i++){
        int temp; cin >> temp;
        positions[i] = temp;
        monsters[temp].insert(i);
    }

    // Run the operations ("queries")
    for(int iii=0; iii<n_operations; iii++){
        int code, L, R;
        cin >> code >> L >> R;

        if (code == 1){
            // Count different monsters between L and R
            int total = op1(L,R,n_monsters);
            cout << total << endl;
        }else{
            // Update
            monsters[positions[L]].erase(L);
            positions[L] = R;
            monsters[positions[L]].insert(L);
        }
    }
    return 0;
}
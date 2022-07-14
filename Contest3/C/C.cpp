
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
        int n_stations, n_queries;
        cin >> n_stations >> n_queries;

        // Input (build tree)
        vector<int> routes;
        map<int, int> left,right,tree;
        for(int i=0; i<n_stations; i++){
            int stat; cin >> stat; 
            routes.push_back(stat);

            if(tree.count(stat) == 0){
                // unknown station, must create in tree
                tree[stat] == 1;
                left[stat] = right[stat] = i;
            }else{
                // known, just update
                left[stat] = min(left[stat], i);
                right[stat] = max(right[stat], i);
            }
        }

        // Process queries
        for(int i=0; i<n_queries; i++){
            int start, dest; cin >> start >> dest;
            if (tree.count(start) && tree.count(dest) && left[start]<right[dest]){
                cout << "YES" << endl;
            }else{
                cout << "NO" << endl;
            }
        }
    }
    return 0;

}


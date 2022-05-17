#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

#define INF 0x3f3f3f
#define MAX 1234
#define ii pair<int,int>

int main() {
    ios_base::sync_with_stdio(false);

    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        int N; cin >> N;
        vector<int> strengths;
        strengths.clear();
        for(int i=0; i<N; i++){
            int ss; cin >> ss;
            strengths.push_back(ss);
        }
        sort(strengths.begin(), strengths.end());

        int min_diff = INF;
        for(int i=0; i<N-1; i++){
            min_diff = min(abs(strengths[i] - strengths[i+1]), min_diff);
        }
        cout << min_diff << endl;
    }

    return 0;
}
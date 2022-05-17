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
#define MAX 123456
#define ii pair<int,int>

int vec[MAX];
int cost[MAX];


int main() {
    ios_base::sync_with_stdio(false);

    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        memset(vec, 0, (MAX)*sizeof(int));
        memset(vec, -1, (MAX)*sizeof(int));

        int N; cin >> N;
        for(int i=1; i<=N; i++){
            int ss; cin >> ss;
            vec[i] = ss;
        }
        
        int max_punct = -1;
        for(int i=1; i<=N; i++){
            int last = i;
            int next = vec[i] + i;
            int curr_punct = vec[i];
            // cout << "start=" << i << ", last=" << last << ",next=" << next << ", N=" << N << ", curr_punct=" << curr_punct << endl;
            while(next <= N){
                // cout << "\tIN: start=" << i << ", last=" << last << ",next=" << next << ", N=" << N << ", curr_punct=" << curr_punct << endl;
                curr_punct += vec[next];
                int tmp = last;
                last = next;
                next += vec[tmp];
            }
            // cout << "OUT: start=" << i << ", last=" << last << ",next=" << next << ", N=" << N << ", curr_punct=" << curr_punct << endl;
            max_punct = max(max_punct, curr_punct);
        }

        cout << max_punct << endl;

    }

    return 0;
}
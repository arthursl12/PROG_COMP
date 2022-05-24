#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

#define INF 0x3f3f3f
#define MAX 40
#define ii pair<int,int>

int available_shirts[7];
int N;
int n_shirts_each, n_compet;
vector<vector<int>> graph;
bool possible;

// (XXL, XL, L, M , S, or XS).
int size2int(string size){
    if(size == "XXL"){
        return 1;
    }else if(size == "XL"){
        return 2;
    }else if(size == "L"){
        return 3;
    }else if(size == "M"){
        return 4;
    }else if(size == "S"){
        return 5;
    }else if(size == "XS"){
        return 6;
    }else{
        exit(1);
    }
}

void print_vec(){
    for(int i=1; i<=7; i++){
        cout << available_shirts[i] << ",";
    }
    cout << endl;
}


void assign(int i){
    // print_vec();
    if (i == n_compet){
        // It was possible to fit everything
        possible = true;
    }
    if (possible){
        return;
    }

    // Try using one option of shirt
    if (available_shirts[graph[i][0]] > 0){
        available_shirts[graph[i][0]] -= 1;
        assign(i+1);
        available_shirts[graph[i][0]] += 1;
    }

    // Try using other option of shirt
    if (available_shirts[graph[i][1]] > 0){
        available_shirts[graph[i][1]] -= 1;
        assign(i+1);
        available_shirts[graph[i][1]] += 1;
    }


}




int main() {
    ios_base::sync_with_stdio(false);

    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        memset(available_shirts, 0, 7*sizeof(int));

        // Input
        int n_shirts; cin >> n_shirts;
        n_shirts_each = n_shirts / 6;
        for(int i=1; i<=6; i++){
            available_shirts[i] = n_shirts_each;
        }
        // print_vec();
        cin >> n_compet;

        // Bipartite graph from competitors -> accepted sizes
        graph.clear();
        for(int i=0; i<n_compet; i++){
            string size1; cin >> size1; 
            string size2; cin >> size2;

            vector<int> accepted;
            accepted.push_back(size2int(size1));
            accepted.push_back(size2int(size2));

            graph.push_back(accepted);
        }
        possible = false;
        assign(0);

        if (possible){
            cout << "YES" << endl;
        }else{
            cout << "NO" << endl;
        }
    }
    return 0;
}
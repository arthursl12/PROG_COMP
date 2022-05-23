// #define MAXN 31
// int capacidade,n,TC;
// map<string,int> conversao;
// vector<int> grafo[MAXN],vis;
// vector< vector<int> > match;
// int augmenting_path(int l){
// 	if(vis[l]) return 0;
// 	vis[l] = 1;
// 	for(int i=0;i<grafo[l].size();i++){
// 		int r = grafo[l][i];
// 		if(match[r].size() < capacidade){
// 			match[r].push_back(l);
// 			return 1;
// 		}
// 		for(int j = 0; j < match[r].size();j++){
// 			int k = match[r][j];
// 			if(augmenting_path(k)){
// 				match[r][j] = l;
// 				return 1;
// 			}
// 		}
// 	}
// 	return 0;
// }
// int main(){
// 	ios_base::sync_with_stdio(0);
// 	cin.tie(0);
// 	cout.tie(0);
// 	cin >> TC;
// 	conversao["XXL"] = 31;
// 	conversao["XL"] = 32;
// 	conversao["L"] = 33;
// 	conversao["M"] = 34;
// 	conversao["S"] = 35;
// 	conversao["XS"] = 36;
// 	while(TC--){
// 		cin >> capacidade >> n;
// 		capacidade = capacidade / 6;
// 		for(int i=1;i<=n;i++){
// 			string a,b;
// 			cin >> a >> b;
// 			grafo[i].clear();
// 			grafo[i].push_back(conversao[a]);
// 			grafo[i].push_back(conversao[b]);
// 		}
// 		vector<int> temp;
// 		match.assign(40,temp);
// 		int resp = 0;
// 		for(int i=1;i<=n;i++){
// 			vis.assign(40,0);
// 			resp += augmenting_path(i);
// 		}
// 		if(resp == n) cout << "YES" << endl;
// 		else cout << "NO" << endl;
// 	}
// 	return 0;
// }

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
#define MAX 12345
#define MAX_DIFF 5
#define ii pair<int,int>

int M[MAX][6][6];
int weight[MAX];
int N;


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

int main() {
    ios_base::sync_with_stdio(false);

    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        // Input
        int n_shirts; cin >> n_shirts;
        int n_compet; cin >> n_compet;

        // Bipartite graph from competitors -> accepted sizes
        vector<vector<int>> graph;
        for(int i=0; i<n_compet; i++){
            string size1; cin >> size1; 
            string size2; cin >> size2;

            vector<int> accepted;
            accepted.push_back(size2int(size1));
            accepted.push_back(size2int(size2));

            graph.push_back(accepted);
        }


    }
    return 0;
}
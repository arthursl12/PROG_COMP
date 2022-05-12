#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include <stack>
#include <queue>


using namespace std;

string select_string(string toerase, string selection){
    string newstring = "";

    for (uint i=0; i<toerase.size(); i++){
        char C = toerase[i];
        int res = selection.find(C);
        if (res != -1){
            newstring += C;
        }
    }

    return newstring;
}

void find_post_order(string& pre, string& in){
    char root = pre[0];
    int root_idx = in.find(root);
    // cout << "PostOrder: " << root << " at " << root_idx << " inside " << in << endl;

    if (root_idx != 0){
        string L_subin = in.substr(0, root_idx);
        if (L_subin != ""){
            string L_subpre = select_string(pre, L_subin);
            find_post_order(L_subpre, L_subin);
        }
        
        string R_subin = in.substr(root_idx+1,string::npos); 
        if (R_subin != ""){
            string R_subpre = select_string(pre, R_subin);
            find_post_order(R_subpre, R_subin);
        }

    }
    cout << root;
    // cout << "PRINT: " << root << endl;

}



int main() {
    ios_base::sync_with_stdio(false);
    int n_tests;
    cin >> n_tests;
    for(int i=0; i<n_tests; i++){
        int n_nodes;
        string pre, in;
        cin >> n_nodes >> pre >> in;
        // cout << n_nodes << "," << pre << "," << in << endl;
        find_post_order(pre, in);
        cout << endl;
    }
    return 0;
}
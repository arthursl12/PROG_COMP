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
#define MAX 123456
#define ii pair<int,int>
#define ll long long

vector<string> string_set;

bool ehConjuntoRuim(string& str, int str_idx){
    bool conj_ruim = false;
    for(int i=0; i<string_set.size(); i++){
        string curr_str = string_set[i];
        if(
            ((str == curr_str) 
            || (str == curr_str.substr(0,str.size())) 
            || (curr_str == str.substr(0,curr_str.size())))     
            && i != str_idx
        ){
            // 'curr_str' or 'str' are a prefix of eachother, but are not the same
            conj_ruim = true;
            break;
        }
    }
    return conj_ruim;
}


int main() {
    ios_base::sync_with_stdio(false);

    int n_strings; cin >> n_strings;
    while(n_strings != 0){
        // Input
        string_set.clear();
        for(int i=0; i<n_strings; i++){
            string s; cin >> s;
            string_set.push_back(s);
        }

        // Process
        bool conj_ruim = false;
        for(int i=0; i<n_strings; i++){
            if(ehConjuntoRuim(string_set[i], i)){
                conj_ruim = true;
                break;
            }
        }

        // Print output
        if (conj_ruim){
            cout << "Conjunto Ruim" << endl;
        }else{
            cout << "Conjunto Bom" << endl;
        }

        // Repeat
        n_strings; cin >> n_strings;
    }
    return 0;
}


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
#define MAX 40
#define ii pair<int,int>
#define ll long long

bool is_suffix(string& potential, string& text){
    int i=0;
    int n = text.size();
    int m = potential.size();
    for (int i=0; i<potential.size(); i++){
        if (potential[m-i-1] != text[n-i-1]){
            return  false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    string text; cin >> text;
    string capped = text.substr(1);
    capped.pop_back();

    string le_substring = "";
    int size = 0;
    while(size < text.size()){
        string potential = text.substr(0,size);
        if (is_suffix(potential, text)){
            size_t middle = capped.find(potential);
            if (middle != string::npos){
                // Achou
                le_substring = potential;
            }
        }
        size++;
    }
    if (le_substring == ""){
        cout << "Just a legend" << endl;
    }else{
        cout << le_substring << endl;
    }
    return 0;
}
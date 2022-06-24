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
#define MAX 2000001
#define ii pair<int,int>
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);

    string s; cin >> s;
    // Convert to lowercase
    for(int i=0; i<s.size(); i++){
        s[i] = tolower(s[i]);
    }

    if(s.find("zelda") != string::npos){
        cout << "Link Bolado" << endl;
    }else{
        cout << "Link Tranquilo" << endl;
    }


    return 0;
}
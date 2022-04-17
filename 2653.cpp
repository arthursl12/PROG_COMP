#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>

using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);

    string jewel;
    set<string> jewel_set;

    while(cin >> jewel){
        jewel_set.emplace(jewel);
    }
    cout << jewel_set.size() << endl;

    return 0;
}
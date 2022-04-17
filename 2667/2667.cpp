#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);

    string number;
    cin >> number;
    
    long long int total = 0; 
    for (int i=0; i<number.size(); i++){
        char C = number[i];
        int n = stoi(string(1,C));
        total += n;
    }
    cout << total % 3 << endl;
    return 0;
}
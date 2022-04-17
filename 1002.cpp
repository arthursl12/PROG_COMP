#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cout << fixed;
    cout << setprecision(2);

    double total;
    cin >> total;
    
    cout << "NOTAS:" << endl;
    int notes[6] = {100,50,20,10,5,2};
    for (int i=0; i < 6; i++){
        int n = total / notes[i];
        total = total - n*notes[i];
        cout << n << " nota(s) de R$ " << notes[i] << ".00" << endl;
    }
    
    cout << "MOEDAS:" << endl;
    float coins[6] = {100,50,25,10,5,1};
    total = total * 100;
    for (int i=0; i < 6; i++){
        int n = total / coins[i];
        total = total - n*coins[i];

        if (coins[i] == 1)
            cout << n << " moeda(s) de R$ " << coins[i]/100 << endl;
        else
            cout << n << " moeda(s) de R$ " << coins[i]/100 << endl;
    }
 
    return 0;
}
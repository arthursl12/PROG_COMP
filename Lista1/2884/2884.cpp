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
#define MAX 1234
#define ii pair<int,int>

int status[MAX];
vector<vector<int>> mapa;


void print_array(int* array, int N){
    for(int i=0; i<N; i++){
        cout << array[i];
        if (i != N-1)
            cout << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int n_interrup; cin >> n_interrup; // interruptores
    int n_lampadas; cin >> n_lampadas; // lampadas

    // Status inicial das lampadas
    memset(status, 0, n_lampadas*sizeof(int));
    int acesas; cin >> acesas;
    for(int i=0; i<acesas; i++){
        int idx; cin >> idx;
        status[idx-1] = 1;
    }

    // Descobre quais interruptores fazem o que
    for(int i=0; i<n_interrup; i++){
        vector<int> interruptor;
        int afetadas; cin >> afetadas;
        for (int j=0; j<afetadas; j++){
            int idx_afect; cin >> idx_afect;
            interruptor.push_back(idx_afect-1);
        }
        mapa.push_back(interruptor);
    }

    // for(int i=0; i<n_interrup; i++){
    //     cout << "Interruptor " << i << endl;
    //     for(int lamp_toggle_idx : mapa[i])
    //         cout << "\t" << lamp_toggle_idx << endl;
    // }
    // exit(1);

    int tentativas = 0;
    while(acesas > 0 && tentativas < 10*n_interrup){
        int inter_idx = tentativas % n_interrup;
        for(int lamp_toggle_idx : mapa[inter_idx]){
            // cout << "\t Afetada: " << lamp_toggle_idx << endl;
            int curr_status = status[lamp_toggle_idx];
            if (curr_status == 0){
                status[lamp_toggle_idx] = 1;
                acesas++;
            }else{
                status[lamp_toggle_idx] = 0;
                acesas--;
            }
        }
        // print_array(status, n_lampadas);
        // cout << "; Acesas=" << acesas << endl;
        tentativas++;
    }
    if (tentativas >= 10*n_interrup){
        cout << -1 << endl;
    }else{
        cout << tentativas << endl;
    }




}
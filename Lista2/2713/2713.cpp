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

#define MAX_ROOMS 1234
#define BIGM 10000000

int monster_hp[MAX_ROOMS];
int dmg_increase[MAX_ROOMS];
int n_rooms, in_mana, base_dmg;

/*
M[i][0]: menor tempo gasto total a partir da sala i sem usar mana nela
M[i][1]: menor tempo gasto total a partir da sala i gastando mana nela

min (M[n_rooms][0], M[n_rooms][1]) dá a resposta
*/

float M[MAX_ROOMS][2];

float min_time(int i, int mana){
    if (M[i][0] != BIGM && M[i][1] != BIGM){
        // Already seen case
        return min(M[i][0], M[i][1]);
    }
    
    if (i >= n_rooms){
        // End of dungeon
        return 0;
    }
    
    int enemy_hp = monster_hp[i];
    if(mana >= 1){
        float mana_time = ((float) enemy_hp) / (base_dmg+dmg_increase[i]);
        M[i][1] = min(M[i][1], mana_time+min_time(i+1, mana-1));
    }else{
        float base_time = ((float) enemy_hp) / base_dmg;
        M[i][0] = min(M[i][0], base_time+min_time(i+1, mana));
    }
    return min(M[i][0], M[i][1]);

}

int main() {
    ios_base::sync_with_stdio(false);
    cout << fixed;
    cout << setprecision(3);
    
    while(cin >> n_rooms >> in_mana >> base_dmg){
        // memset(M, BIGM, 7*sizeof(int));
        for(int i=0; i<n_rooms; i++){
            M[i][0] = BIGM;
            M[i][1] = BIGM;
        }

        memset(monster_hp, -1, MAX_ROOMS*sizeof(int));
        memset(dmg_increase, -1, MAX_ROOMS*sizeof(int));
        for(int i=0; i<n_rooms; i++){
            int hp, increase; cin >> hp >> increase;
            monster_hp[i] = hp;
            dmg_increase[i] = increase;
        }

        cout << min_time(0, in_mana) << endl;

    }
    return 0;
}
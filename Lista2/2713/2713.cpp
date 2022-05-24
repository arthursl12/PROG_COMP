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
#define MAX_MANA 105

int monster_hp[MAX_ROOMS];
int dmg_increase[MAX_ROOMS];
int n_rooms, in_mana, base_dmg;

/*
M[i][j]: menor tempo gasto total a partir da sala i, entrando com j mana
M[0][in_mana] dá a resposta
*/

double M[MAX_ROOMS][MAX_MANA];

double min_time(int i, int mana){
    if (M[i][mana] != BIGM){
        // Already seen case
        return M[i][mana];
    }
    
    if (i >= n_rooms){
        // End of dungeon
        return 0;
    }
    
    int enemy_hp = monster_hp[i];
    double base_time = ((double) enemy_hp) / base_dmg;
    if(mana >= 1){
        double mana_time = ((double) enemy_hp) / (base_dmg+dmg_increase[i]);
        M[i][mana] = min(base_time+M[i][mana], mana_time+min_time(i+1, mana-1));
    }

    M[i][mana] = min(base_time+M[i][mana], base_time+min_time(i+1, mana));
    
    return M[i][mana];

}

int main() {
    ios_base::sync_with_stdio(false);
    cout << fixed;
    cout << setprecision(4);
    
    while(cin >> n_rooms >> in_mana >> base_dmg){
        // memset(M, BIGM, 7*sizeof(int));
        for(int i=0; i<n_rooms; i++){
            for (int j=0; j<=in_mana; j++){
                M[i][j] = BIGM;
                M[i][j] = BIGM;
            }
        }

        memset(monster_hp, -1, MAX_ROOMS*sizeof(int));
        memset(dmg_increase, -1, MAX_ROOMS*sizeof(int));
        for(int i=0; i<n_rooms; i++){
            int hp, increase; cin >> hp >> increase;
            monster_hp[i] = hp;
            dmg_increase[i] = increase;
        }

        // Filling last room times
        int idx = n_rooms-1;
        int enemy_hp = monster_hp[idx];
        double base_time = ((double) enemy_hp) / base_dmg;
        M[idx][0] = base_time;
        double mana_time = ((double) enemy_hp) / (base_dmg+dmg_increase[idx]);
        for(int mana=1; mana<=in_mana; mana++){
            M[idx][mana] = mana_time;
        }

        for(int i=n_rooms-2; i>=0; i--){
            enemy_hp = monster_hp[i];
            base_time = ((double) enemy_hp) / base_dmg;

            // Without mana, there is no choice
            M[i][0] = base_time+M[i+1][0];

            // With mana available, one must choose using it or not
            mana_time = ((double) enemy_hp) / (base_dmg+dmg_increase[i]);
            for(int mana=1; mana<=in_mana; mana++){
                M[i][mana] = min(base_time+M[i+1][mana],mana_time+M[i+1][mana-1]);
            }
            
        }

        cout << M[0][in_mana] << endl;





        // cout << min_time(0, in_mana) << endl;

    }
    return 0;
}
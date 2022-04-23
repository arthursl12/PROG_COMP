#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <cstring>
#include <map>
#include <cmath>

#define INF 0x3f3f3f
#define ii pair<int,int>

using namespace std;

vector<pair<ii,int>> sensors;


// DSU
int parent[1234];
int rnk[1234];

void make_set(int i){
    parent[i] = i;
    rnk[i] = 1;
}

int find(int i){
    int t = i;
    while(parent[i] != i){
        i = parent[i];
    }
    while(parent[t] != t){
        int q = parent[t];
        parent[t] = i;
        t = q;
    }
    return i;
}

void union_set(int i, int j){
    i = find(i);
    j = find(j);
    if (rnk[i] > rnk[j]){
        parent[j] = i;
        rnk[i] += rnk[j];
    }else{
        parent[i] = j;
        rnk[j] += rnk[i];
    }
}

double euclid(int x1, int y1, int x2, int y2){
    double mid = pow(x2-x1,2) + pow(y2-y1,2);
    // cout << "\t" << mid << endl;
    return sqrt(mid);
}

void group_sensors(int x, int y, int r){
    int idx_last = sensors.size()-1;
    for(int i=0; i<sensors.size(); i++){
        if (i == idx_last){continue;}
        auto p = sensors[i];
        ii coord = p.first;
        int rad = p.second;
        double distance = euclid(coord.first, coord.second, x, y);

        // cout << i+1 << "(" << coord.first << "," << coord.second << "), r=" << rad << " => ";
        // cout << idx_last+1 << "(" << x << "," << y << "), r= " << r << " == " << distance << endl; 
        // cout << "\tDistances OK? " << (distance <= (rad + r)) << endl;
        if ((distance <= (rad + r)) && (distance > 0)){
            // cout << "\t unionize" << endl;
            union_set(i,idx_last);
        }

    }
}

void find_groups(int n_sensors, vector<pair<ii,int>> sensors, map<int, vector<pair<ii,int>>>& groups_of_sensors){
    set<int> parents_of_groups;
    for(int i=0; i<n_sensors; i++){
        parents_of_groups.insert(parent[i]);
    }

    for(int i=0; i<n_sensors; i++){
        groups_of_sensors[parent[i]].push_back(sensors[i]);
    }
}

// Dado um grupo, ele bloqueia a dimensão?
bool group_block(int room_width, vector<pair<ii,int>> group, int& min_val, int& max_val){
    // ?Verificação que os da ponta (O(N)) tocam ou não a parede. Não!

    // Ordena por coordenada x (primeiro do par)
    sort(group.begin(), group.end());
    // Tratar o caso da primeira
    int min_x = group[0].first.first - group[0].second;
    int max_x = group[0].first.first + group[0].second;
    int aggregate_x = group[0].first.first;
    // cout << "\tmin=" << min_x << ", max=" << max_x << ", aggr=" << aggregate_x << endl;

    // Computar duas-a-duas
    for(int i=1; i<group.size()-1; i++){
        aggregate_x += group[i].first.first - group[i-1].first.first;
        min_x = min(min_x, group[i].first.first - group[i].second);
        max_x = max(max_x, group[i].first.first + group[i].second);
        // cout << "\tmin=" << min_x << ", max=" << max_x << ", aggr=" << aggregate_x << endl;
    }
    // Tratar o caso da última
    int i = group.size()-1;
    min_x = min(min_x, group[i].first.first - group[i].second);
    max_x = max(max_x, group[i].first.first + group[i].second);
    // cout << "\tmin=" << min_x << ", max=" << max_x << ", aggr=" << aggregate_x << endl;
    min_val = min_x; max_val = max_x;
    if (min_x <= 0 && max_x >= room_width){
        return true;
    }else{
        return false;
    }
}

void reverte_XY(vector<pair<ii,int>> group, vector<pair<ii,int>>& alt_group){
    for(int i=0; i<group.size(); i++){
        alt_group.push_back({
            {group[i].first.second, group[i].first.first},
            group[i].second
        }
        );
    }
}

// Dado um grupo, ele bloqueia a dimensão Y?
/*
bool group_block_Y(int room_height, vector<pair<ii,int>> group){
    // Inverte as coordenadas X e Y (para usar o comparador padrão no sort)
    vector<pair<ii,int>> alt_group;
    for(int i=0; i<group.size(); i++){
        alt_group.push_back({
            {group[i].first.second, group[i].first.first},
            group[i].second
        }
        );
    }


    // Ordena por coordenada Y (primeiro do par agora)
    sort(alt_group.begin(), alt_group.end());
    // Tratar o caso da primeira
    int min_x = alt_group[0].first.first - alt_group[0].second;
    int max_x = alt_group[0].first.first + alt_group[0].second;
    int aggregate_x = alt_group[0].first.first;
    // cout << "\tmin=" << min_x << ", max=" << max_x << ", aggr=" << aggregate_x << endl;

    // Computar duas-a-duas
    for(int i=1; i<group.size()-1; i++){
        aggregate_x += alt_group[i].first.first - alt_group[i-1].first.first;
        min_x = min(min_x, alt_group[i].first.first - alt_group[i].second);
        max_x = max(max_x, alt_group[i].first.first + alt_group[i].second);
        // cout << "\tmin=" << min_x << ", max=" << max_x << ", aggr=" << aggregate_x << endl;
    }
    // Tratar o caso da última
    int i = alt_group.size()-1;
    min_x = min(min_x, alt_group[i].first.first - alt_group[i].second);
    max_x = max(max_x, alt_group[i].first.first + alt_group[i].second);
    // cout << "\tmin=" << min_x << ", max=" << max_x << ", aggr=" << aggregate_x << endl;
    if (min_x <= 0 && max_x >= room_height){
        return true;
    }else{
        return false;
    }
}
*/

bool does_it_block(int M, int N, map<int, vector<pair<ii,int>>>& groups_of_sensors){
    for(auto p : groups_of_sensors){
        // cout << "Grupo (pai) " << p.first+1 << ": ";
        // cout << "bloca X? " << endl;
        int min_x, max_x;
        bool blocaX = group_block(M, p.second, min_x, max_x);
        // cout << blocaX << endl;
        // cout << "bloca Y? " << endl;
        vector<pair<ii,int>> alt_group; reverte_XY(p.second, alt_group);
        int min_y, max_y;
        bool blocaY = group_block(N, alt_group, min_y, max_y);
        // cout << blocaY << endl;
        bool blocaDiagonal = ((min_x <= 0) && (min_y <= 0)) ||
                             ((max_x >= M) && (max_y >= N)) ;
        if (blocaX || blocaY || blocaDiagonal){
            return true;
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);

    int M; cin >> M;
    int N; cin >> N;
    int n_sensors; cin >> n_sensors;
    for(int i=0; i<n_sensors; i++){make_set(i);}

    for(int i=0; i<n_sensors; i++){
        int x; cin >> x;
        int y; cin >> y;
        int r; cin >> r;
        sensors.push_back({{x,y},r});
        group_sensors(x,y,r);
    }

    // Regroup
    // for(int i=0; i<sensors.size(); i++){
    //     for(int j=0; j<sensors.size(); j++){
    //         if (i == j){continue;}
    //         auto p1 = sensors[i];
    //         ii c1 = p1.first;
    //         int r1 = p1.second;

    //         auto p2 = sensors[i];
    //         ii c2 = p2.first;
    //         int r2 = p2.second;
    //         double distance = euclid(c1.first, c1.second, c2.first, c2.second);

    //         // cout << i+1 << "(" << coord.first << "," << coord.second << ") => ";
    //         // cout << idx_last+1 << "(" << x << "," << y << ") == " << distance << endl; 
            
    //         if ((distance <= r1 || distance <= r2) && (distance > 0)){
    //             union_set(i,j);
    //         }
    //     }
    // }


    // for(int i=0; i<n_sensors; i++){
    //     cout << i+1 << ": parent=" << parent[i]+1 << endl;
    // }

    map<int, vector<pair<ii,int>>> groups_of_sensors;
    find_groups(n_sensors, sensors, groups_of_sensors);
    // for(auto p : groups_of_sensors){
    //     cout << "Grupo (pai) " << p.first+1 << ": " << endl;
    //     for(auto sens : p.second){
    //         cout << "\t(" << sens.first.first << "," << sens.first.second << "), r= " << sens.second << endl;
    //     }
    // }

    if (does_it_block(M,N,groups_of_sensors)){
        cout << "N" << endl;
    }else{
        cout << "S" << endl;
    }

    




    // vector<pair<int, pair<int,int>>> galleries;
    // for(int i=0; i<n_gal; i++){
    //     int u; cin >> u;
    //     int v; cin >> v;
    //     int cost; cin >> cost;
    //     galleries.push_back({cost, {u,v}});
    // }

    return 0;
}
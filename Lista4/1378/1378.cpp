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
#include <unordered_map>

using namespace std;

#define INF 0x3f3f3f3f
#define MAX 1123
#define ii pair<int,int>
#define ll long long

struct point_t{
    ll x;
    ll y;
};

ll squared_distance(const point_t &p1, const point_t &p2){
    ll a = p2.x - p1.x;
    ll b = p2.y - p1.y;
    return a*a + b*b;
}


unsigned count_isoceles_triangles(vector<point_t>& points){
    unsigned nb_triangles = 0;

    for (point_t& p1: points){
        unordered_map<ll, unsigned> distances;
        for (point_t& p2: points){
            ll dist = squared_distance(p1, p2);
            distances[dist] += 1;
        }

        for (auto&& dist: distances){
            unsigned count = dist.second;
            nb_triangles += count * (count - 1) / 2;
        }
    }

    return nb_triangles;
}

int main() {
    ios_base::sync_with_stdio(false);

    uint N; cin >> N;
    while(N != 0){
        vector<point_t> points;

        // Input
        for(int i=0; i<N; i++){
            ll x,y; cin >> x >> y;
            point_t P; P.x = x; P.y = y;
            points.push_back(P);
        }

        cout << count_isoceles_triangles(points) << endl;
        cin >> N;
    }
    return 0;
}
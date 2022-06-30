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
#define MAX 5
#define ii pair<int,int>
#define ll long long

typedef struct Point{
    int x;
    int y;
} Point;


int signed_area(Point U, Point V){
    return U.x*V.y - U.y*V.x;
}

Point sub(Point P1, Point P2){
    Point P3;
    P3.x = P1.x - P2.x;
    P3.y = P1.x - P2.y;
    return P3;
}

bool point_comparator(Point P1, Point P2){
    if (P1.x > P2.x){
        return false;
    }else if (P1.x < P2.x){
        return true;
    }else{
        return P1.y < P2.y;
    }
}

bool point_equal(Point P1, Point P2){
    return P1.x == P2.x && P1.y == P2.y;
}

int orientation(Point P1, Point P2, Point P3){
    // int sa = signed_area(sub(P2,P1), sub(P3,P1));
    int sa = P1.x*(P2.y-P3.y) + P2.x*(P3.y-P1.y) + P3.x*(P1.y-P2.y);

    if (sa > 0){
        return 1;
    }else if (sa == 0){
        return 0;
    }else{
        return -1;
    }
}

void convex_hull(vector<Point> Ps, vector<Point>& CH){
    // Graham 
    sort(Ps.begin(), Ps.end(), point_comparator);
    int N = Ps.size();
    vector<Point> hull(2*N);
    
    int k=0;
    for(int i=0; i<N; i++){
        while(k>=2 && (orientation(hull[k-2], hull[k-1], Ps[i]) <= 0)){
            k--;
        }
        hull[k] = Ps[i];
        k++;
    }
    int t = k+1;
    for(int i=N-2; i>=0; i--){
        while(k>=t &&  (orientation(hull[k-2], hull[k-1], Ps[i]) <= 0)){
            k--;
        }
        hull[k] = Ps[i];
        k++;
    }
    hull.resize(k-1);
    CH = hull;
}


int main() {
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    while(N != 0){
        // Input points
        vector<Point> points;
        for(int i=0; i<N; i++){
            int x,y; cin >> x >> y;
            Point P;
            P.x = x;
            P.y = y;
            points.push_back(P);
        }

        // Compute convex-hull progressively smaller
        int n_layers = 0;
        int curr_size = points.size();
        while(curr_size > 2){
            vector<Point> CH;
            convex_hull(points, CH);
            // cout << "CH:" << CH.size() << endl;

            // Valid convex_hull, i.e. valid layer 
            if (CH.size() > 2){
                n_layers++;
            }

            // Remove layer, i.e., select points not in current convex hull
            vector<Point> new_layer;
            for(int i=0; i<points.size(); i++){
                bool mark = false;
                for(int j=0; j<CH.size(); j++){
                    if(point_equal(points[i], CH[j])){
                        // In current CH
                        mark = true;
                        break;
                    }
                    if (j != 0 && orientation(CH[j-1], CH[j], points[i]) == 0){
                        // Special case, colinear
                        mark = true;
                        break;
                    }
                }
                if (!mark){
                    new_layer.push_back(points[i]);
                }
            }
            swap(points, new_layer);
            curr_size = points.size();
        }

        // cout << n_layers << endl;
        if (n_layers % 2 == 0){
            cout << "Do not take this onion to the lab!" << endl;
        }else{
            cout << "Take this onion to the lab!" << endl;
        }
        cin >> N;
    }
    return 0;
}
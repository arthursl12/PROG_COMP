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

bool finish(vector<Point>& ps){
    for(Point p : ps){
        if (p.x != 0 || p.y != 0){
            return false;
        }
    }
    return true;
}

int quad_area(Point P1, Point P2, Point P3, Point P4){
    
    int f1 = P1.x*P2.y + P2.x*P3.y + P3.x*P4.y + P4.x*P1.y;
    int f2 = P2.x*P1.y + P3.x*P2.y + P4.x*P3.y + P1.x*P4.y;

    int area = f1 - f2;
    return area / 2;
}

int main() {
    ios_base::sync_with_stdio(false);

    while(1){
        // Input
        vector<Point> points;
        points.clear();
        for(int i=0; i<MAX; i++){
            int x,y; cin >> x >> y;
            Point P;
            P.x = x;
            P.y = y;
            points.push_back(P);
        }

        // Check for end of input
        if (finish(points)){ break; }

        // Sort for ease of use
        sort(points.begin(), points.end(), point_comparator);
        vector<Point> CH;
        convex_hull(points, CH);

        if (CH.size() == 4){
            // Straighforward: just calculate the area
            int area = quad_area(CH[0], CH[1], CH[2], CH[3]);
            cout << area << endl;
        }else if (CH.size() == 5){
            // Find best area removing a single point
            int max_area = -1;
            max_area = max(max_area, quad_area(CH[0], CH[1], CH[2], CH[3]));
            max_area = max(max_area, quad_area(CH[0], CH[1], CH[2], CH[4]));
            max_area = max(max_area, quad_area(CH[0], CH[1], CH[3], CH[4]));
            max_area = max(max_area, quad_area(CH[0], CH[2], CH[3], CH[4]));
            max_area = max(max_area, quad_area(CH[1], CH[2], CH[3], CH[4]));
            cout << max_area << endl;
        }else if (CH.size() == 3){
            // Two inner points must be chosen
            // Find the best area with any of the triangle's vertices

            // Find the two points inside
            vector<Point> not_in;
            for(int i=0; i<MAX; i++){
                bool mark = false;
                for(int j=0; j<CH.size(); j++){
                    if (point_equal(points[i], CH[j])){
                        mark = true;
                        break;
                    }
                }
                if (!mark){
                    not_in.push_back(points[i]);
                }
            }
            if(not_in.size() != 2){
                exit(1);
            }

            // Try removing each triangle vertex
            vector<Point> trying = not_in;
            trying.push_back(CH[0]); trying.push_back(CH[1]);
            vector<Point> otherCH;
            convex_hull(trying, otherCH);

            if (otherCH.size() == 4){
                int area = quad_area(otherCH[0], otherCH[1], otherCH[2], otherCH[3]);
                cout << area << endl;
                continue;
            }else{
                trying = not_in;
                trying.push_back(CH[0]); trying.push_back(CH[2]);
                otherCH.clear();
                convex_hull(trying, otherCH);
                if (otherCH.size() == 4){
                    int area = quad_area(otherCH[0], otherCH[1], otherCH[2], otherCH[3]);
                    cout << area << endl;
                    continue;
                }else{
                    trying = not_in;
                    trying.push_back(CH[1]); trying.push_back(CH[2]);
                    otherCH.clear();
                    convex_hull(trying, otherCH);
                    if (otherCH.size() == 4){
                        int area = quad_area(otherCH[0], otherCH[1], otherCH[2], otherCH[3]);
                        cout << area << endl;
                        continue;
                    }else{
                        cout << "ERRO" << endl;
                        exit(1);
                    }
                }
            }


        }

        
    }
    return 0;
}
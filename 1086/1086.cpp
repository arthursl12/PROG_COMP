#include <iostream>
#include <map>
#include <vector> 
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;


int try_fit2(int goal_size, int total_height, int L, vector<int>& sorted_planks){
    int used_planks = 0;
    int filled_lines = 0;
    int lines = round(( (float) total_height) / L);

    float difference = ((((float) total_height) / L) - (total_height / L));
    // cout << "Diff=" << difference << endl;
    if (difference != 0){
        return -1;
    }


    // cout << "Lines = " << lines << "; Largura = " << L << "; Goal = " << goal_size << endl;

    int start = 0;
    int end = sorted_planks.size() - 1;

    while(1){
        // cout << "start=" << start << ", end=" << end << ", filled=" << filled_lines << ", lines=" << lines << endl;
        if (start >= end) return -1; // Ran out of planks
        if (filled_lines == lines) return used_planks;


        if (sorted_planks[end]*100 > goal_size){
            // Too big
            end--;
        }else if(sorted_planks[end]*100 == goal_size){
            // Exact size
            used_planks++;
            filled_lines++;
            end--;
        }else{
            // Too small, try to fit two
            if (start != end){
                while(1){
                    if(sorted_planks[start]*100 + sorted_planks[end]*100 == goal_size){
                        // Fit with two exact
                        start++;
                        used_planks++;
                        used_planks++;
                        filled_lines++;
                        break;
                    }
                    if (sorted_planks[start]*100 + sorted_planks[end]*100 > goal_size){
                        // Too big
                        break;
                    }
                    start++;
                }
                end--;
            }
        }
    }
    return used_planks;
}
        

int main() {
    ios_base::sync_with_stdio(false);
    
    int N;
    while(cin >> N){
        if (N == 0){break;}

        int M;
        cin >> M;
        N = N*100;
        M = M*100;

        int L;
        cin >> L;
        int K;
        cin >> K;
        
        vector<int> sorted_planks;
        for (int i = 0; i < K; i++){
            int size; cin >> size;
            sorted_planks.push_back(size);
        }
        sort(sorted_planks.begin(), sorted_planks.end());
        vector<int> sorted_planks_copy = sorted_planks;

        // Try to fit in N
        int used_planks_N = 0;
        used_planks_N = try_fit2(N, M, L, sorted_planks);

        // Try to fit in M
        int used_planks_M = 0;
        used_planks_M = try_fit2(M, N, L, sorted_planks_copy);
        // cout << used_planks_M << ", " << used_planks_N << endl;
        if (used_planks_M + used_planks_N == -2){
            cout << "impossivel" << endl;
        }else if (used_planks_M < 0){
            cout << used_planks_N << endl;
        }else if (used_planks_N < 0){
            cout << used_planks_M << endl;
        }else{
            cout << min(used_planks_N, used_planks_M) << endl;
        }
    }
    return 0;
}
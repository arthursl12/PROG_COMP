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
#define MAX 123456
#define ii pair<int,int>
#define ll long long
#define ss pair<string,string>

/*
- Tem que fazer um leitor, que seja amparado na enarmonia (converta tudo para um padrão, por exemplo de sustenidos)
- Converte as notas em uma string de intervalos, é procurar substring.
*/

vector<int> intervals_music, intervals_snip;
map<string, string> correlations;
map<string, ii>    value;
map<string, int>    scaled;


void montar_correlations(){
    correlations["C#"] = "C#";
    correlations["D#"] = "D#";
    correlations["E#"] = "F";
    correlations["F#"] = "F#";
    correlations["G#"] = "G#";
    correlations["A#"] = "A#";
    correlations["B#"] = "C";

    correlations["Cb"] = "B";
    correlations["Db"] = "C#";
    correlations["Eb"] = "D#";
    correlations["Fb"] = "E";
    correlations["Gb"] = "F#";
    correlations["Ab"] = "G#";
    correlations["Bb"] = "A#";

    correlations["C"] = "C";
    correlations["D"] = "D";
    correlations["E"] = "E";
    correlations["F"] = "F";
    correlations["G"] = "G";
    correlations["A"] = "A";
    correlations["B"] = "B";

    // value["C"]  = 1;
    // value["C#"] = 2;
    // value["D"]  = 3;
    // value["D#"] = 4;
    // value["E"]  = 5;
    // value["F"]  = 6;
    // value["F#"] = 7;
    // value["G"]  = 8;
    // value["G#"] = 9;
    // value["A"]  = 10;
    // value["A#"] = 11;
    // value["B"]  = 12;
    value["C"]  = {1,13};
    value["C#"] = {2,14};
    value["D"]  = {3,15};
    value["D#"] = {4,16};
    value["E"]  = {5,17};
    value["F"]  = {6,18};
    value["F#"] = {7,19};
    value["G"]  = {8,20};
    value["G#"] = {9,21};
    value["A"]  = {10,22};
    value["A#"] = {11,23};
    value["B"]  = {12,24};
}

int distancia(string& n1, string& n2){
    int m1 = abs(value[n2].first-value[n1].first);
    int m2 = abs(value[n2].first-value[n1].second);
    int m3 = abs(value[n2].second-value[n1].first);

    int smallest = min(min(m1,m2),m3);
    if (smallest == 6){
        return 6;
    }else if (smallest == m1){
        return value[n2].first-value[n1].first;
    }else if (smallest == m2){
        return value[n2].first-value[n1].second;
    }else{
        return value[n2].second-value[n1].first;
    }



    // int m1 = abs(value[n2] - value[n1]);
    // int m2 = abs(value[n1] - value[n2]);
    // if (m1 > m2){
    //     return value[n1] - value[n2];
    // }else{
    //     return value[n2] - value[n1];
    // }
    return scaled[n2]-scaled[n1];
}

void montar_scaled_value(string& nota0){
    scaled.clear();
    vector<string> order = {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B","C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
    int i=0;
    for(; i<12; i++){
        if (order[i] == nota0){
            break;
        }
    }

    for(int j=1; j<=12; j++){
        scaled[order[i]] = j;
        cout << "scaled[" << order[i] << "]=" << j << endl;
        i++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    montar_correlations();

    int n_music, n_snip;
    while(cin >> n_music >> n_snip){
        if (n_music == 0){
            break;
        }

        string n1, n2;

        // Input music
        intervals_music.clear();
        cin >> n1;
        n1 = correlations[n1];
        // montar_scaled_value(n1);
        for(int i=1; i<n_music; i++){
            cin >> n2;
            n1 = correlations[n1];
            n2 = correlations[n2];
            intervals_music.push_back(distancia(n1,n2));
            n1 = n2;
        }

        // cout << endl;

        // Input snippet
        cin >> n1;
        intervals_snip.clear();
        n1 = correlations[n1];
        // montar_scaled_value(n1);
        for(int i=1; i<n_snip; i++){
            cin >> n2;
            n1 = correlations[n1];
            n2 = correlations[n2];
            intervals_snip.push_back(distancia(n1,n2));
            n1 = n2;
        }

        // for(int i=0; i<n_music-1; i++){
        //     cout << intervals_music[i] << ",";
        // }
        // cout << endl;
        // for(int i=0; i<n_snip-1; i++){
        //     cout << intervals_snip[i] << ",";
        // }
        // cout << endl;

        // Try to find
        bool copy = false;
        for(int i=0; i<n_music-1; i++){
            if(intervals_music[i] == intervals_snip[0] && ((n_music-1-i)>=(n_snip-1))){
                int j=i;
                int k=0;
                while(j<n_music-1 && k<n_snip-1 && intervals_music[j] == intervals_snip[k]){
                    j++; k++;
                    if (k >= (n_snip-1)){
                        // cout << "HERE: i=" << i << endl; 
                        copy = true;
                        break;
                    }
                }
            }
        }

        if (copy){
            cout << "S" << endl;
        }else{
            cout << "N" << endl;
        }

    }
    return 0;
}
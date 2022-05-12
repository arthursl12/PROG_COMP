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
#include <stack>

using namespace std;


#define INF 0x3f3f3f
#define MAXV 12345
#define MAXE 2*MAXV

#define ii pair<int,int>


int q_certas_time[100];
int total_tp_time_20[100];
int total_tp_time_other[100];
int tp_importa_time[100];

int other_ep = -1;




/*
Desempenho do time 'i':
    Cada questão, com (Attempts,TP)
*/
vector<vector<ii>> tabela;

int questoes_certas(int i){
    if (q_certas_time[i] != -1){
        return q_certas_time[i];
    }
    vector<ii> desempenho = tabela[i];
    int q_certas = 0;
    for(ii p : desempenho){
        if (p.second == -1){
            // Não acertou a questão
        }else{
            q_certas++;
        }
    }
    q_certas_time[i] = q_certas;
    return q_certas;
}

int penalty_time(int tp, int ep, int fa){
    return tp + ep * fa;
}

int total_penalty_time(int i, int ep){
    if (ep == other_ep && total_tp_time_other[i] != -1){
        return total_tp_time_other[i];
    }else if (ep == 20 && total_tp_time_20[i] != -1){
        return total_tp_time_20[i];
    }else if (ep != 20 && ep != other_ep){
        exit(1);
    }

    // TP não importa para esse time
    if(tp_importa_time[i] != -1 && tp_importa_time[i] == 0){
        return 0;
    }

    vector<ii> desempenho = tabela[i];
    int total_tp = 0;
    bool tp_importa = false;
    for(ii p : desempenho){
        if (p.second == -1 && p.first == 0){
            // Não acertou a questão nem tentou
        }else if(p.second == -1 && p.first != 0){
            // Não acertou a questão, mas tentou 
            total_tp += penalty_time(0, ep, p.first);
            tp_importa = true;
        }else{
            total_tp += penalty_time(p.second, ep, p.first-1);
            if (p.first != 1){
                tp_importa = true;
            }
        }
    }
    if (ep == 20){
        total_tp_time_20[i] = total_tp;
    }else{
        total_tp_time_other[i] = total_tp;
    }
    return total_tp;
}

void print_times(int T, int Q){
    for(int i=0; i<T; i++){
        vector<ii> desempenho = tabela[i];
        cout << "<" << i+1 << ">";
        cout << "\t";
        for(int j=0; j<Q; j++){
            cout << j+1 << ":";
            cout << desempenho[j].first << "/" << desempenho[j].second;
            cout << "; ";
        }
        cout << endl;
    }
}

void print_vector(int* array, int i){
    for(int j=0; j<i; j++){
        cout << array[j] << ",";
    }
    cout << endl;
}

struct custom_greater
{
    inline bool operator() (const ii& par1, const ii& par2)
    {
        if(par1.first == par2.first){
            return par1.second > par2.second;
        }else{
            return par1.first < par2.first;
        }
    }
};

void rank_teams_fn(int T, int* tp_vector, vector<int>& times_ranking, vector<vector<int>>& ties){
    map<ii,int> mapa_desempenho_time;
    vector<ii> mapa_inverso;
    vector<ii> ranking;
    for(int i=0; i<T; i++){
        ii par = {q_certas_time[i], tp_vector[i]};
        mapa_desempenho_time[par]++;
        mapa_inverso.push_back(par);
        if (mapa_desempenho_time[par] == 1){
            ranking.push_back(par);
        }
    }
    sort(ranking.begin(), ranking.end(), custom_greater());
    times_ranking.clear();
    ties.clear();
    for(ii par : ranking){
        if(mapa_desempenho_time[par] == 1){
            // Sem empate aqui
            int idx = distance(mapa_inverso.begin(), find(mapa_inverso.begin(),mapa_inverso.end(),par));
            times_ranking.push_back(idx);
        }else{
            // Há empates aqui
            vector<int> empatados;
            empatados.clear();
            auto it = find(mapa_inverso.begin(),mapa_inverso.end(),par);
            int idx = distance(mapa_inverso.begin(), it);
            empatados.push_back(idx);
            times_ranking.push_back(idx);

            it = find(it+1,mapa_inverso.end(),par);
            while(it != mapa_inverso.end()){
                idx = distance(mapa_inverso.begin(), it);
                empatados.push_back(idx);
                it = find(it+1,mapa_inverso.end(),par);
            }
            ties.push_back(empatados);
        }
    }
}

void rank_other(int T, int ep){
    map<ii,int> mapa_desempenho_time;
    vector<ii> ranking;
    for(int i=0; i<T; i++){
        ii par = {q_certas_time[i], total_tp_time_20[i]};
        mapa_desempenho_time.insert({par,i});
        ranking.push_back(par);
    }
    sort(ranking.begin(), ranking.end(), greater<ii>());
}

int isTied(int idx, vector<vector<int>>& ties){
    for(int i=0; i<ties.size(); i++){
        for(int j=0; j<ties[i].size(); j++){
            if(idx == ties[i][j]){
                return i;
            }
        }
    }
    return -1;
}

void print_ranking(int T, vector<int>& times_ranking, vector<vector<int>>& ties){
    for(int idx_team : times_ranking){
        int idx_tie = isTied(idx_team, ties);
        // cout << "isTie? " << idx_tie << endl;
        if (idx_tie != -1){
            cout << "{";
            for(int j=0; j<ties[idx_tie].size(); j++){
                cout << ties[idx_tie][j]+1 << " ";
            }
            cout << "}";
        }else{
            cout << idx_team+1;
        }
        
        cout << ", ";
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    int Q; cin >> Q;
    string delim = "/";
    while(T != 0 && Q != 0){
        // Inicialização
        memset(q_certas_time, -1, 100*sizeof(int));
        memset(total_tp_time_20, -1, 100*sizeof(int));
        memset(total_tp_time_other, -1, 100*sizeof(int));
        memset(tp_importa_time, -1, 100*sizeof(int));

        // Processa Entrada
        for(int i=0; i<T; i++){
            vector<ii> desempenho;
            for(int j=0; j<Q; j++){
                string one_question; cin >> one_question;
                size_t pos = one_question.find(delim);
                int attempts = stoi(one_question.substr(0, pos));

                one_question.erase(0, pos + delim.length());
                int time_p;
                if (one_question == "-"){
                    time_p = -1;
                }else{
                    time_p = stoi(one_question);
                }
                
                desempenho.push_back({attempts, time_p});
            }
            tabela.push_back(desempenho);
        }
        print_times(T,Q);

        for(int i=0; i<T; i++){
            questoes_certas(i);
            total_penalty_time(i, 20);
        }
        print_vector(q_certas_time, T);
        print_vector(total_tp_time_20, T);

        vector<int> times_ranking;
        vector<vector<int>> ties;
        rank_teams_fn(T, total_tp_time_20, times_ranking, ties);
        print_ranking(T, times_ranking, ties);

        vector<int> times_ranking2;
        vector<vector<int>> ties2;
        other_ep = 20000;
        for(int i=0; i<T; i++){
            total_penalty_time(i, other_ep);
        }
        print_vector(total_tp_time_other, T);
        rank_teams_fn(T, total_tp_time_other, times_ranking2, ties2);
        print_ranking(T, times_ranking2, ties2);



        // BigM
        // Busca binária para achar os limites


        T; cin >> T;
        Q; cin >> Q;
    }
    return 0;
}
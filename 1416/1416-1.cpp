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
#define ii pair<int,int>

#define INF 0x3f3f3f
#define MAXT 100
#define MAXP 10
#define BIGM 100000

int questoes[MAXT];
int TP_20[MAXT];
vector<vector<ii>> tabela; // Desempenho do time 'i': Cada questão, com (Attempts,TP)

int questoes_certas(int i){
    if (questoes[i] != -1){
        return questoes[i];
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
    questoes[i] = q_certas;
    return q_certas;
}

int penalty_time(int tp, int ep, int fa){
    return tp + ep * fa;
}

int total_penalty_time(int i, int ep, int* array){
    if (array[i] != -1){
        return array[i];
    }

    vector<ii> desempenho = tabela[i];
    int total_tp = 0;
    bool tp_importa = false;
    for(ii p : desempenho){
        if (p.second == -1 && p.first == 0){
            // Não acertou a questão nem tentou
        }else if(p.second == -1 && p.first != 0){
            // Não acertou a questão, mas tentou 
        }else{
            total_tp += penalty_time(p.second, ep, p.first-1);
        }
    }
    array[i] = total_tp;
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

bool novo_ep_valido(int T, int novo_ep){
    int TP_ALT[MAXT]; memset(TP_ALT, -1, MAXT*sizeof(int));
    for(int i=0; i<T; i++){
        total_penalty_time(i, novo_ep, TP_ALT);
    }
    // cout << "EP=" << novo_ep << ": ";
    // print_vector(TP_ALT, T);


    for(int i=0; i<T; i++){
        for (int j=0; j<T; j++){
            if (questoes[i] != questoes[j]){
                // Continue, as questões não mudam, nada verificar!
                continue;
            }else if (TP_20[i] == TP_20[j] && TP_ALT[i] != TP_ALT[j]){
                // Estava empatado, não está mais
                return false;
            }else if (TP_20[i] < TP_20[j] && TP_ALT[i] >= TP_ALT[j]){
                // Era menor, ficou maior ou igual
                return false;
            }else if (TP_20[i] > TP_20[j] && TP_ALT[i] <= TP_ALT[j]){
                // Era maior, ficou menor ou igual
                return false;
            }
        }
    }
    // Se chegou aqui é porque tá OK
    return true;
}

void monta_tabela(int T, int Q){
    // Processa Entrada
    string delim = "/";
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
    // print_times(T,Q);
}

int busca_binaria_UB_rec(int minval, int maxval, int T){
    if(maxval - minval == 1){
        return minval;
    }

    int meio = ((float)minval + maxval) / 2;
    if(novo_ep_valido(T, meio)){
        return busca_binaria_UB_rec(meio, maxval, T);
    }else{
        return busca_binaria_UB_rec(minval, meio, T);
    }
}

int busca_binaria_UB(int bigM, int T){
    if(novo_ep_valido(T, bigM)){
        return INF;
    }
    return busca_binaria_UB_rec(20, bigM, T);
}

int busca_binaria_LB_rec(int minval, int maxval, int T, int i){
    if (i == 30){
        return maxval;
    }
    if(abs(maxval - minval) == 1){
        return maxval;
    }
    cout << "[MIN: " << minval << ", MAX: " << maxval << "] ";
    int meio = ((float)minval + maxval) / 2;
    if(novo_ep_valido(T, meio)){
        return busca_binaria_LB_rec(minval, meio, T, i+1);
    }else{
        return busca_binaria_LB_rec(meio, maxval, T, i+1);
    }
}

int busca_binaria_LB(int UB, int T){
    if(novo_ep_valido(T, 1)){
        return 1;
    }
    return busca_binaria_LB_rec(1,UB,T, 0);
}

int brute_force_LB(int T){
    if(novo_ep_valido(T, 1)){
        return 1;
    }
    int i = 2;
    while(!novo_ep_valido(T,i)){
        i++;
    }
    return i;
}


int main(){
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    int Q; cin >> Q;
    while(T != 0 && Q != 0){
        // Inicialização
        tabela.clear();
        memset(questoes, -1, MAXT*sizeof(int));
        memset(TP_20, -1, MAXT*sizeof(int));
        // memset(total_tp_time_other, -1, 100*sizeof(int));
        // memset(tp_importa_time, -1, 100*sizeof(int));

        // Leitura Entrada
        monta_tabela(T,Q);

        // Processa do EP=20
        for(int i=0; i<T; i++){
            questoes_certas(i);
            total_penalty_time(i, 20, TP_20);
        }
        // print_vector(questoes, T);
        // print_vector(TP_20, T);

        // int ub = busca_binaria_UB(BIGM, T);
        // int lb = busca_binaria_LB(lb, T);

        int lb = brute_force_LB(T);
        int ub = busca_binaria_UB(BIGM, T);

        cout << lb << " ";
        if (ub == INF){
            cout << "*" << endl;
        }else{
            cout << ub << endl;
        }
        // bool resp = novo_ep_valido(T, 24);
        // cout << resp << endl;
        // resp = novo_ep_valido(T, 25);
        // cout << resp << endl;





        cin >> T;
        cin >> Q;
    }
    return 0;
}

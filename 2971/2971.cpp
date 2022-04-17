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

#define INF 0x3f3f3f
#define JOKER 'X'

using namespace std;

/*
- Quem começa pega o curinga, obrigatoriamente
Se mais de um ganhar, ganha o com menor índice

- Regras de passagem:
    1. Curinga (exceto se for a 1ª rodada)
    2. Carta que menos aparece na mão
    3. Dentre as que menos aparecem, a menor
*/

int curinga_counter = 0;

int anybodyWon(vector<string>& players){
    for(int i=0; i<players.size(); i++){
        string mao = players[i];
        if(mao[0] == mao[1] && mao[0] == mao[2] && mao[0] == mao[3]){
            return i+1;
        }
    }
    return 0;
}

char untieCards(string mao){
    map<char,int> cartas_bin;
    for(char c : mao){
        cartas_bin[c]++;
    }

    vector<char> todas_;
    for(auto p : cartas_bin){
        if (p.second == 3){
            return p.first;
        }else if (p.second == 2){
            cartas_com_2.push_back(p.first);
        }
    }
    if (cartas_com_2[0] == 'A'){
        return cartas_com_2[1];
    }else if (cartas_com_2[0] == 'J' 
              || cartas_com_2[0] == 'Q'
              || cartas_com_2[0] == 'K')
        return cartas_com_2[1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);

    int n_players; cin >> n_players;
    int idx_start; cin >> idx_start;

    vector<string> players;
    for(int i=0; i<n_players; i++){
        string mao; cin >> mao;
        players.push_back(mao);
    }

    int idxWinner = anybodyWon(players);

    char received = JOKER;
    char passed = ' ';
    int idxCurr = idx_start;
    while(!idxWinner){
        // Processa turno
        players[idxCurr] += received;
        string mao = players[idxCurr];
        if (received == JOKER){
            curinga_counter = 0;
        }

        size_t joker_pos = mao.find(JOKER);
        if(joker_pos != string::npos && curinga_counter != 0){
            // Passa o curinga
            passed = JOKER;
            players[idxCurr].erase(joker_pos,joker_pos+1);
        }else{
            idxWinner = anybodyWon(players);
            if (idxWinner){
                break;
            }
            // Passa a carta com menos ocorrência

        }
        


        // Quando voltar a ser esse cara, ele pode passar o curinga
        if (curinga_counter == 0){
            curinga_counter++;
        }

        // Prepara para processar o seguinte
        received = passed;
        idxCurr++; idxCurr = idxCurr % n_players;
        idxWinner = anybodyWon(players);
    }
    cout << idxWinner << endl;



    vector<pair<int, pair<int,int>>> galleries;
    for(int i=0; i<n_gal; i++){
        int u; cin >> u;
        int v; cin >> v;
        int cost; cin >> cost;
        galleries.push_back({cost, {u,v}});
    }

    // Kruskal to find max spanning tree
    memset(parent, -1, 1234567*sizeof(int));
    memset(rnk, -1, 1234567*sizeof(int));
    sort(galleries.begin(), galleries.end(), greater<pair<int,pair<int,int>>>());
    for(int i=0; i<n_gal; i++){make_set(i);}

    int max_cost = 0;
    for(auto p : galleries){
        int cost = p.first;
        int u = p.second.first;
        int v = p.second.second;
        if (find(u) != find(v)){
            // Não gera ciclo
            max_cost += cost;
            union_set(u,v);
        }
    }
    cout << max_cost << endl;

    // Kruskal to find min spanning tree
    memset(parent, -1, 1234567*sizeof(int));
    memset(rnk, -1, 1234567*sizeof(int));
    sort(galleries.begin(), galleries.end());
    for(int i=0; i<n_gal; i++){make_set(i);}

    int min_cost = 0;
    for(auto p : galleries){
        int cost = p.first;
        int u = p.second.first;
        int v = p.second.second;
        if (find(u) != find(v)){
            // Não gera ciclo
            min_cost += cost;
            union_set(u,v);
        }
    }
    cout << min_cost << endl;
    return 0;
}
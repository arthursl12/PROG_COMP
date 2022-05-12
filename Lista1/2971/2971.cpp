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

int curinga_counter;

int anybodyWon(vector<string>& players){
    for(int i=0; i<players.size(); i++){
        string mao = players[i];
        if(mao[0] == mao[1] && mao[0] == mao[2] && mao[0] == mao[3]){
            return i+1;
        }
    }
    return 0;
}

void printplayers(vector<string>& players){
    for(int i=0; i<players.size(); i++){
        string mao = players[i];
        cout << i << ": " << mao << endl;
    }
}

map<char,int> tradutor{
    {'A', 1},
    {'1', 2},
    {'2', 3},
    {'3', 4},
    {'4', 5},
    {'5', 6},
    {'6', 7},
    {'7', 8},
    {'8', 9},
    {'9', 10},
    {'D', 10},
    {'Q', 11},
    {'J', 12},
    {'K', 13},
    {'X', 14}
};



char untieCards(string mao){
    map<char,int> cartas_bin;
    for(char c : mao){
        cartas_bin[c]++;
    }

    vector<char> cartas_com_1;
    vector<char> cartas_com_2;

    bool hasJoker = false;
    for(auto p : cartas_bin){
        if (p.first == JOKER){
            hasJoker = true;
            break;
        }
    }

    for(auto p : cartas_bin){
        if (p.first == JOKER){continue;}
        if (p.second == 1){
            cartas_com_1.push_back(p.first);
        }else if (p.second == 2){
            cartas_com_2.push_back(p.first);
        }else if (p.second == 4 && hasJoker){
            // O cara pegou o curinga e tava no winning state
            return p.first;
        }
    }

    if (cartas_com_1.size() > 0){
        if (cartas_com_1.size() < 2){
            return cartas_com_1[0];
        }else{
            char min_char = ' ';
            int min_char_val = INF;
            for(int i=0; i<cartas_com_1.size(); i++){
                if(tradutor[cartas_com_1[i]] < min_char_val){
                    min_char = cartas_com_1[i];
                    min_char_val = tradutor[cartas_com_1[i]];
                }
            }
            return min_char;
        }
    }

    if (cartas_com_2.size() < 2){
        return cartas_com_2[0];
    }else{
        if (tradutor[cartas_com_2[0]] < tradutor[cartas_com_2[1]]){
            return cartas_com_2[0];
        }else {
            return cartas_com_2[1];
        }
    }    
}

int main() {
    ios_base::sync_with_stdio(false);

    int n_players; cin >> n_players;
    int idx_start; cin >> idx_start; idx_start--;

    vector<string> players;
    for(int i=0; i<n_players; i++){
        string mao; cin >> mao;
        players.push_back(mao);
    }

    int idxWinner = 0;
    char received = JOKER;
    curinga_counter = 0;
    char passed = ' ';
    int idxCurr = idx_start;
    int i=0;
    while(!idxWinner){
        // Processa turno
        players[idxCurr] += received;
        string mao = players[idxCurr];
        // cout << "Player: " << idxCurr+1 << ", mao=" << mao << endl;
        if (received == JOKER){
            curinga_counter = 0;
        }
        // cout << "\treceived=" << received << ", curinga_counter=" << curinga_counter << endl;
        size_t joker_pos = mao.find(JOKER);
        if(joker_pos != string::npos && curinga_counter != 0){
            // Passa o curinga
            passed = JOKER;
            // cout << "\tErase joker" << endl;
            players[idxCurr].erase(joker_pos,1);
        }else{
            // Passa a carta com menos ocorrência
            passed = untieCards(mao);
            // cout << "\tCard to pass:" << passed << ", from " << mao << endl;
            size_t pos = mao.find_first_of(passed);
            // cout << "\tErase comum" << endl;
            players[idxCurr].erase(pos,1);
        }
        
        // cout << "\tpassed=" << passed << endl;
        // Quando voltar a ser esse cara, ele pode passar o curinga
        if (curinga_counter == 0){
            curinga_counter++;
        }

        // Prepara para processar o seguinte
        received = passed;
        idxCurr++; idxCurr = idxCurr % n_players;
        idxWinner = anybodyWon(players);

        // i++;

        // if (i == 10){
        //     break;
        // }
    }
    cout << idxWinner << endl;
    return 0;
}
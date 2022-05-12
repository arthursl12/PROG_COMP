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
#define MAX 15
#define ll long long 

void print_vector(int* array, int i){
    for(int j=0; j<i; j++){
        cout << array[j] << ",";
    }
    cout << endl;
}
void print_vector(vector<ll> v){
    for(int j=0; j<v.size(); j++){
        cout << v[j] << ",";
    }
    cout << endl;
}

void dobra(vector<ll> v, int pos, vector<ll>& res){
    res.clear();
    if(pos == 0){
        // Edge case
        res = v;
        reverse(res.begin(), res.end());
    }else{
        vector<ll> copy;
        int size = v.size();
        for(int k=0; k<pos; k++){
            if (pos+k < size){
                int val = v[pos-k-1];
                val += v[pos+k];
                copy.push_back(val);

            }
        }
        // cout << "\t";
        // print_vector(copy);
        
        if (2*pos < size){
            for(int i = 2*pos; i<v.size(); i++){
                copy.push_back(v[i]);
            }
        }else{
            for(int i = pos-(size-pos)-1; i>=0; i--){
                copy.push_back(v[i]);
            }
        }
        
        res = copy;
        // cout << "\t";
        // print_vector(copy);
    }

}

void add_possibilities(vector<ll> v,
                       queue<vector<ll>>& vectors_to_process, 
                       set<vector<ll>>& valid){
    for(int i=0; i<v.size(); i++){
        // Faz uma dobra possível
        vector<ll> result;
        result.clear();
        dobra(v, i, result);

        // Vê se o resultado já foi guardado
        auto it = valid.find(result);
        if (it == valid.end()){
            // Novo resultado possível, adicione à fila e ao conjunto válido
            vectors_to_process.emplace(result);
            valid.insert(result);
        }else{
            // Resultado já conhecido e já explorado/na pilha para explorar
        }
    }
}

void processa(vector<ll> start_vector, set<vector<ll>>& valid){
    queue<vector<ll>> vectors_to_process;
    vectors_to_process.emplace(start_vector);
    int k=0;
    while(!vectors_to_process.empty()){
        vector<ll> top = vectors_to_process.front();
        vectors_to_process.pop();
        // cout << "Q=" << vectors_to_process.size() << ", Processa: ";
        // print_vector(top);
        add_possibilities(top, vectors_to_process, valid);
        // if (k==10){
        //     break;
        // }
        // k++;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    // set<vector<int>> myset;

    // vector<int> vec1 = {1,2,3,4,5};
    // vector<int> vec2 = {6,7,8};
    // vector<int> vec3 = {1,2,3,4,5};
    // vector<int> vec4 = {1,2,3,4,5,6,7,8};
    // vector<int> vec5 = {1,2,3,4,5};
    // vector<int> vec6 = {9,10,11};
    // vector<int> vec7 = {6,7,8};

    // myset.insert(vec1);
    // myset.insert(vec2);
    // myset.insert(vec3);
    // myset.insert(vec4);
    // myset.insert(vec5);

    // cout << myset.size() << endl;
    // cout << (myset.find(vec6) != myset.end()) << endl;
    // cout << (myset.find(vec7) != myset.end()) << endl;

    int N; 
    while(cin >> N){
        // Entrada
        vector<ll> status_inicial;
        for(int i=0; i<N; i++){
            int val; cin >> val;
            status_inicial.push_back(val);
        }
        reverse(status_inicial.begin(), status_inicial.end());
        // print_vector(status_inicial);

        // Descobre as possibilidades
        set<vector<ll>> valid;
        processa(status_inicial, valid);

        // Lê a saída
        int N_saida; cin >> N_saida;
        vector<ll> status_final;
        for(int i=0; i<N_saida; i++){
            int val; cin >> val;
            status_final.push_back(val);
        }
        reverse(status_final.begin(), status_final.end());

        // print_vector(status_final);

        // Verifica se é válida
        auto it = valid.find(status_final);
        if (it != valid.end()){
            cout << "S" << endl;
        }else{
            cout << "N" << endl;
        }
    }
    return 0;
}
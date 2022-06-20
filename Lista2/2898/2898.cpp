#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

#define INF 0x3f3f3f
#define MAX 12345
#define MAX_DIFF 5
#define ii pair<int,int>

// Lista de adjacências (destino, capacidade)
vector<vector<ii>> grafo;
vector<int> nivel;
vector<int> athletes_in_airport;
int beijing;
int got_there;

void viaja(int u, int v, int capacity){
    if (athletes_in_airport[u] <= capacity){
        // Only some will go
        athletes_in_airport[v] += athletes_in_airport[u];
    }else{
        // All passenger will go to next
        athletes_in_airport[v] += capacity;
    }
}

void bfs_limitada(int source, int lim){
    int passos = 0;
    int incoming = INF;
    int current_node = source;
    nivel[source] = 0;

    queue<int> nodes_to_visit;
    nodes_to_visit.emplace(current_node);
    while(!nodes_to_visit.empty()){
        current_node = nodes_to_visit.front();
        nodes_to_visit.pop();
        // cout << "Explorando: " << current_node << endl;
        if (nivel[current_node] == lim){
            break;
        }

        for(ii par : grafo[current_node]){
            int destination, capacity;
            destination = par.first; capacity = par.second;
            viaja(current_node, destination, capacity);
            nivel[destination] = nivel[current_node]++;
            if (destination != beijing)
                nodes_to_visit.emplace(destination);
            else
                got_there += capacity;
        }
    }
}

void print_flooding(){
    for(int i=0; i<athletes_in_airport.size(); i++){
        cout << athletes_in_airport[i] << ",";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n_airports, n_flights, n_athletes;
    cin >> n_airports;
    while(n_airports != 0){
        cin >> n_flights >> n_athletes;
        beijing = n_airports-1;

        // Build graph
        grafo.clear();
        athletes_in_airport.clear();
        nivel.clear();
        for(int i=0; i<n_airports; i++){
            vector<ii> lista;
            grafo.push_back(lista);
            athletes_in_airport.push_back(0);
            nivel.push_back(0);
        }

        // Input edges
        for(int k=0; k<n_flights; k++){
            int u,v,cap; cin >> u >> v >> cap;
            u--; v--;
            grafo[u].push_back({v, cap});
        }

        // Assume infinite flux entering tumbolian airport
        // Loop until all athletes get to destination
        got_there = 0;
        int n_days = 0;
        while(got_there < n_athletes){
            bfs_limitada(0, n_days);
            n_days++;
            print_flooding();
        }
        print_flooding();
        cout << n_days << endl;

        cin >> n_airports;
    }
    return 0;
}

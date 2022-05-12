#include <iostream>
#include <map>
#include <vector> 
#include <stack>
#include <algorithm>

using namespace std;

 
void visit(char v, map<char, vector<char>>& grafo, map<char, int>& visited, 
           stack<char>& current_visit, vector<char>& current_component)
{
    visited[v] = 1;

    for (char viz : grafo[v]){
        if (visited[viz] == 0){
            // Visit next node first
            current_visit.emplace(viz);
            visit(viz, grafo, visited, current_visit, current_component);
        }else{
            continue;
        }
    }
    current_component.push_back(v);
    char verify = current_visit.top();
    if (verify != v){
        cout << "Erro!\n";
    }
    current_visit.pop();
    visited[v] = 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    
    int tttt;
    cin >> tttt;
    for(int caso = 0; caso < tttt; caso++){
        cout << "Case #" << caso+1 << ":" << endl;

        int V,E;
        cin >> V;
        cin >> E;

        // Graph as a list
        map<char, vector<char>> grafo;
        map<char, int> visited;
        char first = 'a';
        for (int i=0; i<V; i++){
            visited[first+i] = 0;
            grafo[first+i] = vector<char>();
        }
        for (int i=0; i < E; i++){
            char vA, vB;
            cin >> vA;
            cin >> vB;
            grafo[vA].push_back(vB);
            grafo[vB].push_back(vA);
        }
        
        // "DFS"
        bool all_visited = false;
        int components = 0;
        while(!all_visited){
            char current;
            for (pair<char,int> par : visited){
                if (par.second != 2){
                    current = par.first;
                    break;
                }
            }

            // Visit
            stack<char> current_visit;
            vector<char> current_component = vector<char>();
            current_visit.emplace(current);
            visit(current, grafo, visited, current_visit, current_component);

            // Got component
            sort(current_component.begin(), current_component.end());
            for (char v : current_component){
                cout << v << ",";
            }
            cout << endl;
            components++;
            
            // Check all visited
            // 0: not visited yet; 1: visiting; 2: visited
            all_visited = true;
            for (pair<char,int> par : visited){
                if (par.second != 2){
                    all_visited = false;
                    break;
                }
            }
        }
        cout << components << " connected components" << endl << endl;
    }
    return 0;
}
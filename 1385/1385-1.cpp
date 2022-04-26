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
#include <cmath>

using namespace std;

#define INF 0x3f3f3f
#define MAXV 1234
// #define MAXE 2*MAXV

#define ii pair<int,int>

void print_vector(int* array, int i){
    for(int j=0; j<i; j++){
        cout << array[j] << ",";
    }
    cout << endl;
}
void print_vector(vector<int> v){
    for(int j=0; j<v.size(); j++){
        cout << v[j] << ",";
    }
    cout << endl;
}

vector<int> number_sizes_not_last = {1,2,3};
vector<int> number_sizes = {1,2,3,4};

int size_sum(vector<int> v){
    int total=0;
    for(int j=0; j<v.size(); j++){
        total += v[j];
    }
    return total;
}

void findAll(const vector<vector<int> > &allVecs, size_t vecIndex, 
             vector<int> vecSoFar, vector<vector<int>>& possibilities, int target){
    if (vecIndex >= allVecs.size()){
        // cout << strSoFar << endl;
        // print_vector(vecSoFar);
        if (size_sum(vecSoFar) == target){
            possibilities.push_back(vecSoFar);
        }
        return; 
    }
    for (size_t i=0; i<allVecs[vecIndex].size(); i++){
        vector<int> nextVec = vecSoFar;
        nextVec.push_back(allVecs[vecIndex][i]);
        findAll(allVecs, vecIndex+1, nextVec, possibilities, target);

    }
}

int process_header(string s, string& s_pretty){
    s_pretty.clear();
    int i=0;
    int p_num = 1;
    while(s[i] == 'P'){
        s_pretty.append("P");
        s_pretty.append(to_string(p_num));
        s_pretty.append(" ");
        i += 2;
        p_num++;
    }
    s_pretty.append("Totals");
    return p_num-1;
}

void read_clients(vector<string>& names, vector<string>& numbers){
    names.clear(); numbers.clear();

    string client_line; cin >> client_line;
    while(client_line[0] != 'T' && client_line[1] != 'P'){
        int name_j = client_line.find_first_of("1234567890");
        string client_name = client_line.substr(0,name_j);
        string number_str = client_line.substr(name_j);
        // cout << client_name << " => " << number_str << endl;
        names.push_back(client_name);
        numbers.push_back(number_str);
        cin >> client_line;
    }
    int name_j = client_line.find_first_of("1234567890");
    string client_name = client_line.substr(0,name_j);
    string number_str = client_line.substr(name_j);
    // cout << client_name << " => " << number_str << endl;
    names.push_back(client_name);
    numbers.push_back(number_str);
}

void break_string(string s, vector<int> break_sizes, vector<int>& res){
    int last = 0;
    for(int i=0; i<break_sizes.size(); i++){
        int target_size = break_sizes[i];
        string new_s = s.substr(last, target_size);
        last += target_size;

        int myval = stoi(new_s);
        res.push_back(myval);
    }
}

bool valid_sum(vector<int> v){
    int total = 0;
    for(int i=0; i<v.size()-1; i++){
        total += v[i];
    }
    return total == v[v.size()-1];
}

void filter_horizontal_sum(string s, vector<vector<int>> all_permutations, 
                           vector<vector<int>>& valids_sum)
{
    valids_sum.clear();
    for(auto it=all_permutations.begin(); it!=all_permutations.end(); it++){
        vector<int> result;
        break_string(s, *it, result);
        if (valid_sum(result)){
            valids_sum.push_back(result);
        }
    }
}

void process_horizontal(string s, int target_size,
                        vector<vector<int>>& filtered_valids_sum){

    // Combinational Sum
    int target = s.size();
    // vector<vector<int>> valids;
    // vector<int> current_stack;

    vector<vector<int>> allVectors;
    for(int i=0; i<target_size; i++){
        allVectors.push_back(number_sizes);
    }
    vector<int> temp;
    vector<vector<int>> possibilities;
    findAll(allVectors, 0, temp, possibilities, s.size());
    // for(auto v : possibilities){
    //     print_vector(v);
    // }
    // combinationalSum(number_sizes, target, valids, current_stack, 0);
    // for(int i=0; i<valids.size(); i++){
    //     print_vector(valids[i]);
    // }

    // Filtra só as somas com tamanho N
    // cout << endl;
    // vector<vector<int>> filtered_valids;
    // filter_size(possibilities, target_size, filtered_valids);
    // for(int i=0; i<filtered_valids.size(); i++){
    //     print_vector(filtered_valids[i]);
    // }

    // Acha as permutações das somas possíveis
    // cout << endl;
    // set<vector<int>> all_permutations;
    // get_permutations(possibilities, all_permutations);
    // for(auto it=all_permutations.begin(); it!=all_permutations.end(); it++){
    //     print_vector(*it);
    // }

    // Filtra as permutações que a soma horizontal é possível
    // cout << endl;
    // vector<int> result;
    // break_string(s, *(all_permutations.begin()), result);
    // print_vector(result);
    // vector<vector<int>> filtered_valids_sum;
    filter_horizontal_sum(s, possibilities, filtered_valids_sum);
    // for(int i=0; i<filtered_valids_sum.size(); i++){
    //     print_vector(filtered_valids_sum[i]);
    // }
}


bool valid_vertical_sum(vector<vector<int>>& one_sum){
    for(int i=0; i<one_sum[0].size(); i++){
        vector<int> vertical_sum;
        for(vector<int> v : one_sum){
            vertical_sum.push_back(v[i]);
        }
        if (!valid_sum(vertical_sum)){
            return false;
        }
    }
    return true;
}

void process_vertical(vector<string> ss, 
                      vector<vector<vector<int>>>& all_valid_sums, 
                      vector<vector<int>>& possible_outcome)
{  
    // Lista de vetores
    vector<vector<int>> v1, v2, v3, v4, v5;
    int size = all_valid_sums.size();
    v1 = all_valid_sums[0];
    v2 = all_valid_sums[1];
    if (size >= 3){
        v3 = all_valid_sums[2];
        if (size >= 4){
            v4 = all_valid_sums[3];
            if (size == 5){
                v5 = all_valid_sums[4];
            }
        }
    }

    // Loop para achar uma solução válida
    if (size < 3){
        for(auto i1 = v1.begin(); i1 != v1.end(); ++i1){
            for(auto i2 = v2.begin(); i2 != v2.end(); ++i2){
                vector<vector<int>> one_valid_sum;
                one_valid_sum.push_back(*i1);
                one_valid_sum.push_back(*i2);

                if (valid_vertical_sum(one_valid_sum)){
                    possible_outcome.clear();
                    possible_outcome = one_valid_sum;
                    return;
                }         
            }
        }
    }else if (size == 3){
        for(auto i1 = v1.begin(); i1 != v1.end(); ++i1){
            for(auto i2 = v2.begin(); i2 != v2.end(); ++i2){
                for(auto i3 = v3.begin(); i3 != v3.end(); ++i3){
                    vector<vector<int>> one_valid_sum;
                    one_valid_sum.push_back(*i1);
                    one_valid_sum.push_back(*i2);
                    one_valid_sum.push_back(*i3);

                    if (valid_vertical_sum(one_valid_sum)){
                        possible_outcome.clear();
                        possible_outcome = one_valid_sum;
                        return;
                    }
                }
            }
        }
    }else if (size == 4){
        for(auto i1 = v1.begin(); i1 != v1.end(); ++i1){
            for(auto i2 = v2.begin(); i2 != v2.end(); ++i2){
                for(auto i3 = v3.begin(); i3 != v3.end(); ++i3){
                    for(auto i4 = v4.begin(); i4 != v4.end(); ++i4){
                        vector<vector<int>> one_valid_sum;
                        one_valid_sum.push_back(*i1);
                        one_valid_sum.push_back(*i2);
                        one_valid_sum.push_back(*i3);
                        one_valid_sum.push_back(*i4);

                        if (valid_vertical_sum(one_valid_sum)){
                            possible_outcome.clear();
                            possible_outcome = one_valid_sum;
                            return;
                        }
                    }
                }
            }
        }
    }else{
        for(auto i1 = v1.begin(); i1 != v1.end(); ++i1){
            for(auto i2 = v2.begin(); i2 != v2.end(); ++i2){
                for(auto i3 = v3.begin(); i3 != v3.end(); ++i3){
                    for(auto i4 = v4.begin(); i4 != v4.end(); ++i4){
                        for(auto i5 = v5.begin(); i5 != v5.end(); ++i5){

                            vector<vector<int>> one_valid_sum;
                            one_valid_sum.push_back(*i1);
                            one_valid_sum.push_back(*i2);
                            one_valid_sum.push_back(*i3);
                            one_valid_sum.push_back(*i4);
                            one_valid_sum.push_back(*i5);

                            if (valid_vertical_sum(one_valid_sum)){
                                possible_outcome.clear();
                                possible_outcome = one_valid_sum;
                                return;
                            }
                                    
                        }
        
                    }
                }
            }
        }
    }   

    
}

void process_number_strings(vector<string> ss, int target_size,
                            vector<vector<int>>& possible_outcome)
{
    vector<vector<vector<int>>> all_valid_sums;
    for(string s : ss){
        vector<vector<int>> valid_sum_for_s;
        process_horizontal(s, target_size, valid_sum_for_s);
        all_valid_sums.push_back(valid_sum_for_s);
    }

    // int k=0;
    // for(string s : ss){
    //     cout << s << endl;
    //     for(int i=0; i<all_valid_sums[k].size(); i++){
    //         print_vector(all_valid_sums[k][i]);
    //     }
    //     k++;
    //     cout << endl;
    // }

    // vector<vector<int>> possible_outcome;
    process_vertical(ss, all_valid_sums, possible_outcome);
    // for(int i=0; i<possible_outcome.size(); i++){
    //     print_vector(possible_outcome[i]);
    // }
}


void print_clients(vector<string> names, vector<vector<int>> outcome){
    for (int i=0; i<names.size(); i++){
        cout << names[i] << " ";
        for(int j=0; j<outcome[i].size(); j++){
            cout << outcome[i][j];
            if (j != outcome[i].size()-1){
                cout << " ";
            }
        }
        cout << endl;
    }
}


int main(){
    ios_base::sync_with_stdio(false);
    
    int n_tests; cin >> n_tests;
    for(int iiii=0; iiii<n_tests; iiii++){
        // Process Header
        string header; cin >> header;
        string pretty_header;
        int P = process_header(header, pretty_header);
        cout << pretty_header << endl;
        // cout << "P=" << P << endl;

        // VectorCombination
        // vector<vector<int>> allVectors;
        // for(int i=0; i<P+1; i++){
        //     if (i != P)
        //         allVectors.push_back(number_sizes_not_last);
        //     else
        //         allVectors.push_back(number_sizes);
        // }
        // vector<int> temp;
        // vector<vector<int>> possibilities;
        // findAll(allVectors, 0, temp, possibilities ,9);
        // for(auto v : possibilities){
        //     print_vector(v);
        // }

        // Read clients
        vector<string> names, numbers;
        read_clients(names, numbers);

        // Find an outcome
        vector<vector<int>> possible_outcome;
        // cout << "HERE1" << endl;

        process_number_strings(numbers, P+1, possible_outcome);
        // for(int i=0; i<possible_outcome.size(); i++){
        //     print_vector(possible_outcome[i]);
        // }

        // Print recovered report
        // cout << "HERE2" << endl;

        print_clients(names, possible_outcome);

        cout << endl;
    }


    // vector<string> ss = {"121100131", "5141772", "14121238", "1862629241"};
    // vector<vector<int>> possible_outcome;

    // process_number_strings(ss, possible_outcome);
    // for(int i=0; i<possible_outcome.size(); i++){
    //     print_vector(possible_outcome[i]);
    // }

    return 0;
}
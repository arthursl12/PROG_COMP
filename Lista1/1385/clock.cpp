
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
#include <random>

using namespace std;

#define VS o1_valid_vertical_sum

int max_n_len = 6;

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

int vec_sum(vector<int>& v){
    int total = 0;
    for(int j=0; j<v.size(); j++){
        total += v[j];
    }
    return total;
}
int o1_vec_sum(vector<int>& v){
    int size = v.size();
    switch (size){
        case 0: return 0;
        case 1: return v[0];
        case 2: return v[0]+v[1];
        case 3: return v[0]+v[1]+v[2];
        case 4: return v[0]+v[1]+v[2]+v[3];
        case 5: return v[0]+v[1]+v[2]+v[3]+v[4];
        case 6: return v[0]+v[1]+v[2]+v[3]+v[4]+v[5];
        case 7: return v[0]+v[1]+v[2]+v[3]+v[4]+v[5]+v[6];
    }
}

void flip_clock(vector<int>& clock, int max){
    for(int i=0; i<clock.size(); i++){
        if (clock[i] < max){
            continue;
        }else if (i < clock.size()-1){
            clock[i+1] += 1;
            clock[i] = 1;
        }else{
            clock[i] = 1;
        }
    }
}
bool last_too_small(vector<int> v){
    int last = v.back();
    int max_others = *max_element(v.begin(), v.end()-2);
    return max_others > last;
}

bool break_smart_valid_sum(vector<int>& break_sizes, string s, vector<int>& result){
    int last_val = stoi(s.substr(s.size()-break_sizes.back(), break_sizes.back()));

    int total_sum = 0;
    int last = 0;
    // print_vector(break_sizes);
    for(int i=0; i<break_sizes.size(); i++){
        int target_size = break_sizes[i];
        string new_s = s.substr(last, target_size);
        last += target_size;

        int myval = stoi(new_s);
        result.push_back(myval);
        if (i != break_sizes.size()-1){
            total_sum += myval;
            if (total_sum > last_val){
                // Soma intermediária já passou o último
                return false;
            }

        }else{
            if (total_sum != myval){
                // cout << "Here3" << endl;
                return false;
            }
        }
    }
    return true;
}
void correct_sum_horizontal(int n_numbers, string s, vector<vector<int>>& correct_sum){
    vector<int> clock(n_numbers, 1);
    int target = s.size();
    int i=0;
    // cout << "HERE" << endl;
    while(o1_vec_sum(clock) <= ((max_n_len-1)*n_numbers)){
        flip_clock(clock, max_n_len);
        // print_vector(clock);
        
        if (o1_vec_sum(clock) == target && !last_too_small(clock)){
            // É uma soma válida (de tamanhos)
            vector<int> possible;
            if (break_smart_valid_sum(clock, s, possible)){
                // É uma soma válida dos números da string
                correct_sum.push_back(possible);
            }   
        }
        clock[0] += 1;
    }
    // for(auto v : correct_sum){ print_vector(v); }
}

int o1_vertical_sum(vector<vector<int>>& vv, int i){
    int size = vv.size();
    switch (size){
        case 0: return 0;
        case 1: return vv[0][i];
        case 2: return vv[0][i]+vv[1][i];
        case 3: return vv[0][i]+vv[1][i]+vv[2][i];
        case 4: return vv[0][i]+vv[1][i]+vv[2][i]+vv[3][i];
        case 5: return vv[0][i]+vv[1][i]+vv[2][i]+vv[3][i]+vv[4][i];
        case 6: return vv[0][i]+vv[1][i]+vv[2][i]+vv[3][i]+vv[4][i]+vv[5][i];
        case 7: return vv[0][i]+vv[1][i]+vv[2][i]+vv[3][i]+vv[4][i]+vv[5][i]+vv[6][i];
    }
}
bool o1_valid_vertical_sum(vector<vector<int>>& vv, int i){
    int last_i = vv.back()[i];
    return (o1_vertical_sum(vv,i)-last_i) == last_i;
}
bool o1_all_valid_vertical_sum(vector<vector<int>>& vv){
    int size = vv[0].size();
    switch (size){
        case 0: return true;
        case 1: return VS(vv,0);
        case 2: return VS(vv,0) && VS(vv,1);
        case 3: return VS(vv,0) && VS(vv,1) && VS(vv,2);
        case 4: return VS(vv,0) && VS(vv,1) && VS(vv,2) && VS(vv,3);
        case 5: return VS(vv,0) && VS(vv,1) && VS(vv,2) && VS(vv,3) && VS(vv,4);
        case 6: return VS(vv,0) && VS(vv,1) && VS(vv,2) && VS(vv,3) && VS(vv,4) && VS(vv,5);
        case 7: return VS(vv,0) && VS(vv,1) && VS(vv,2) && VS(vv,3) && VS(vv,4) && VS(vv,5) && VS(vv,6);
    }
}

bool o1_someone_greater(vector<int>& v1, vector<int>& v4){
    int size = v1.size();
    switch (size){
        case 0: return true;
        case 1: return (v1[0] > v4[0]);
        case 2: return (v1[0] > v4[0]) && (v1[1] > v4[1]);
        case 3: return (v1[0] > v4[0]) && (v1[1] > v4[1]) && (v1[2] > v4[2]);
        case 4: return (v1[0] > v4[0]) && (v1[1] > v4[1]) && (v1[2] > v4[2]) && (v1[3] > v4[3]);
        case 5: return (v1[0] > v4[0]) && (v1[1] > v4[1]) && (v1[2] > v4[2]) && (v1[3] > v4[3]) && (v1[4] > v4[4]);
        case 6: return (v1[0] > v4[0]) && (v1[1] > v4[1]) && (v1[2] > v4[2]) && (v1[3] > v4[3]) && (v1[4] > v4[4]) && (v1[5] > v4[5]);
        case 7: return (v1[0] > v4[0]) && (v1[1] > v4[1]) && (v1[2] > v4[2]) && (v1[3] > v4[3]) && (v1[4] > v4[4]) && (v1[5] > v4[5]) && (v1[6] > v4[6]);
    }
}
bool o1_someone_greater_2_vec(vector<int>& v1, vector<int>& v2, vector<int>& v4){
    int size = v1.size();
    switch (size){
        case 0: return true;
        case 1: return (v1[0]+v2[0] > v4[0]);
        case 2: return (v1[0]+v2[0] > v4[0]) && (v1[1]+v2[1] > v4[1]);
        case 3: return (v1[0]+v2[0] > v4[0]) && (v1[1]+v2[1] > v4[1]) && (v1[2]+v2[2] > v4[2]);
        case 4: return (v1[0]+v2[0] > v4[0]) && (v1[1]+v2[1] > v4[1]) && (v1[2]+v2[2] > v4[2]) && (v1[3]+v2[3] > v4[3]);
        case 5: return (v1[0]+v2[0] > v4[0]) && (v1[1]+v2[1] > v4[1]) && (v1[2]+v2[2] > v4[2]) && (v1[3]+v2[3] > v4[3]) && (v1[4]+v2[4] > v4[4]);
        case 6: return (v1[0]+v2[0] > v4[0]) && (v1[1]+v2[1] > v4[1]) && (v1[2]+v2[2] > v4[2]) && (v1[3]+v2[3] > v4[3]) && (v1[4]+v2[4] > v4[4]) && (v1[5]+v2[5] > v4[5]);
        case 7: return (v1[0]+v2[0] > v4[0]) && (v1[1]+v2[1] > v4[1]) && (v1[2]+v2[2] > v4[2]) && (v1[3]+v2[3] > v4[3]) && (v1[4]+v2[4] > v4[4]) && (v1[5]+v2[5] > v4[5]) && (v1[6]+v2[6] > v4[6]);
    }
}

bool someone_greater(vector<int>& v1, vector<int>& v4){
    int size = v1.size();
    for(int i=0; i<v1.size(); i++){
        if ((v1[i] > v4[i])){
            return false;
        }
    }
    return true;
}

bool someone_greater_2_vec(vector<int>& v1, vector<int>& v2, vector<int>& v4){
    int size = v1.size();
    for(int i=0; i<v1.size(); i++){
        if ((v1[i]+v2[i] > v4[i])){
            return false;
        }
    }
    return true;
}

bool on_four_valid_vertical(vector<int>& v1, vector<int>& v2, 
                            vector<int>& v3, vector<int>& v4)
{
    int size = v1.size();
    for(int i=0; i<v1.size(); i++){
        if ((v1[i]+v2[i]+v3[i] != v4[i])){
            return false;
        }
    }
    return true;
}

bool on_five_valid_vertical(vector<int>& v1, vector<int>& v2, 
                            vector<int>& v3, vector<int>& v4,
                            vector<int>& v5)
{
    int size = v1.size();
    for(int i=0; i<v1.size(); i++){
        if ((v1[i]+v2[i]+v3[i]+v4[i] != v5[i])){
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
        for(auto i1 = v1.rbegin(); i1 != v1.rend(); ++i1){
            for(auto i2 = v2.rbegin(); i2 != v2.rend(); ++i2){
                vector<vector<int>> one_valid_sum;
                one_valid_sum.push_back(*i1);
                one_valid_sum.push_back(*i2);

                if (o1_all_valid_vertical_sum(one_valid_sum)){
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

                    if (o1_all_valid_vertical_sum(one_valid_sum)){
                        possible_outcome.clear();
                        possible_outcome = one_valid_sum;
                        return;
                    }
                }
            }
        }
    }else if (size == 4){
        for(auto i1 = v1.begin(); i1 != v1.end(); ++i1){
            // if (someone_greater(*i1, *i4)){ continue; }
            for(auto i2 = v2.begin(); i2 != v2.end(); ++i2){
                // if (someone_greater_2_vec(*i1, *i2, *i4)){ continue; }
                for(auto i3 = v3.begin(); i3 != v3.end(); ++i3){
                    for(auto i4 = v4.begin(); i4 != v4.end(); ++i4){
                        
                        if (on_four_valid_vertical(*i1, *i2, *i3, *i4)){
                            vector<vector<int>> one_valid_sum;

                            one_valid_sum.push_back(*i1);
                            one_valid_sum.push_back(*i2);
                            one_valid_sum.push_back(*i3);
                            one_valid_sum.push_back(*i4);

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
            // if (o1_someone_greater(*i1, *i5)){ continue; }
            for(auto i2 = v2.begin(); i2 != v2.end(); ++i2){
                // if (o1_someone_greater_2_vec(*i1, *i2, *i5)){ continue; }
                for(auto i3 = v3.begin(); i3 != v3.end(); ++i3){
                    for(auto i4 = v4.begin(); i4 != v4.end(); ++i4){
                        for(auto i5 = v5.begin(); i5 != v5.end(); ++i5){
                            
                            if (on_five_valid_vertical(*i1, *i2, *i3, *i4, *i5)){
                                vector<vector<int>> one_valid_sum;
                                one_valid_sum.push_back(*i1);
                                one_valid_sum.push_back(*i2);
                                one_valid_sum.push_back(*i3);
                                one_valid_sum.push_back(*i4);
                                one_valid_sum.push_back(*i5);

                            // if (o1_all_valid_vertical_sum(one_valid_sum)){
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
void process_number_strings(vector<string>& ss, int n_numbers,
                            vector<vector<int>>& possible_outcome)
{
    vector<vector<vector<int>>> all_valid_sums;
    bool all_equal = true;;
    string s0 = ss[0];
    for(string s : ss){
        if (s != s0){
            all_equal = false;
        }
    }


    // cout << "HERE1" << endl;
    // if (all_equal){
    for(string s : ss){
        vector<vector<int>> valid_sum_for_s;
        correct_sum_horizontal(n_numbers, s, valid_sum_for_s);
        sort(valid_sum_for_s.begin(), valid_sum_for_s.end());
        if ((ss.size() == 2 && ss[0][0] == '1') || ss.size() == 3){
            reverse(valid_sum_for_s.begin(), valid_sum_for_s.end());
        }
        all_valid_sums.push_back(valid_sum_for_s);
    }
    // }else{
    //     // cout << "Equals" << endl;
    //     vector<vector<int>> valid_sum_for_s0;
    //     correct_sum_horizontal(n_numbers, s0, valid_sum_for_s0);
    //     all_valid_sums.push_back(valid_sum_for_s0);

    //     random_device rd;
    //     mt19937 g(rd());
    //     for(int i=1; i<ss.size()-1; i++){
    //         // shuffle(valid_sum_for_s0.begin(), valid_sum_for_s0.end(), g);
    //         all_valid_sums.push_back(valid_sum_for_s0);
    //     }

    //     vector<vector<int>> valid_sum_for_s_last;
    //     correct_sum_horizontal(n_numbers, ss.back(), valid_sum_for_s_last);
    //     all_valid_sums.push_back(valid_sum_for_s_last);
    // }
    

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
        // cout << "HERE6" << endl;

        vector<string> names, numbers;
        read_clients(names, numbers);
        // cout << "HERE7" << endl;

        // Find an outcome
        vector<vector<int>> possible_outcome;
        // cout << "HERE5" << endl;

        process_number_strings(numbers, P+1, possible_outcome);
        // for(int i=0; i<possible_outcome.size(); i++){
        //     print_vector(possible_outcome[i]);
        // }

        // Print recovered report
        // cout << "HERE2" << endl;

        print_clients(names, possible_outcome);

        // cout << endl;
    }


    return 0;
}
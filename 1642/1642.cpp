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

#define INF 0x3f3f3f

using namespace std;


void find_best_to_remove(string& substring, set<char>& chars_in_subbstring, 
                         size_t& pos_to_delete, char& chosen)
{
    // Which char to remove from substring, considering a way to minimize losses
    int min_pos = INF;
    char best_char = ' ';
    
    for (char c : chars_in_subbstring){
        size_t last_pos = substring.find_last_of(c);
        if (last_pos < min_pos){
            best_char = c;
            min_pos = last_pos;
        }
    }
    pos_to_delete = min_pos;
    chosen = best_char;
}

void print_set(set<char>& myset){
    cout << "{";
    for(char c: myset){
        cout << c << ",";
    }
    cout << "}" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);

    int m_keys; cin >> m_keys;
    while(m_keys != 0){
        char message_char[1234567];
        string message; getline(cin, message); getline(cin, message);
        // cout << "Message:" << message << ", keys=" << m_keys << endl;

        int max_substring = 0;
        int current_size = 0;
        int susbtring_char_bin[128];
        memset(susbtring_char_bin, 0, 128*sizeof(int));
        // vector<int> susbtring_char_bin{128,0};
        set<char> susbtring_char_set;


        int a=0; int b=0; // Ends of susbtring

        // string substring = "";
        for(int i=0; i<message.size(); i++){

            // Adiciona o novo caractere na substring
            // cout << "Next=" << message[i];
            // cout << ", substr=(" << a << "," << b << ")";
            // cout << ", set=" << susbtring_char_set.size() << endl;
            char next_char = message[i];
            susbtring_char_bin[next_char]++;
            susbtring_char_set.insert(next_char);
            b=i;

            while (susbtring_char_set.size() > m_keys){
                // cout << "\tsubstr=(" << a << "," << b << ")";
                // cout << ", set=" << susbtring_char_set.size() << endl;
                // print_set(susbtring_char_set);
                susbtring_char_bin[message[a]]--;
                if(susbtring_char_bin[message[a]] == 0){
                    susbtring_char_set.erase(message[a]);
                }
                a++;
                
            }
            if (b-a+1 > max_substring){
                max_substring = b-a+1;
            }





            // auto it = chars_in_substring.find(next_char);
            // if (it == chars_in_substring.end()){
            //     // cout << "\tNew char, substr=" << substring << ", max=" << max_substring << ", set=" << chars_in_substring.size() << endl;
            //     // New char
                
            //     // if (chars_in_substring.size() == m_keys){
            //     //     // We must delete some char from current
            //     //     size_t last_pos; char chosen_char;
            //     //     find_best_to_remove(substring, chars_in_substring, last_pos, chosen_char);

                    
            //     //     // Delete susbtring until last ocurrence of this char
            //     //     // char first_char = substring[0];
            //     //     // size_t last_pos = substring.find_last_of(first_char);
            //     //     substring.erase(0,last_pos+1);

            //     //     // Remove said char from set
            //     //     chars_in_substring.erase(chosen_char);
            //     // }
                
            //     // Insert the new char
            //     chars_in_substring.insert(next_char);
            // }else{
            //     // cout << "Seen char: '" << next_char << "'" << endl;
            //     // Char already in string, just add it
            // }
            // // Add next char to string
            // substring += next_char;
            // if (substring.size() > max_substring){max_substring = substring.size();}
            // // cout << "\tOUT: substr=" << substring << ", max=" << max_substring << ", set=" << chars_in_substring.size() << endl;
        }
        cout << max_substring << endl;
        cin >> m_keys;
    }
    return 0;
}
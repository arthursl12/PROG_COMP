#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>

#define INF 0x3f3f3f

using namespace std;


void find_best_to_remove(string& substring, unordered_set<char>& chars_in_subbstring, 
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

int main() {
    ios_base::sync_with_stdio(false);

    int m_keys; cin >> m_keys;
    while(m_keys != 0){
        char message_char[1234567];
        string message; getline(cin, message); getline(cin, message);
        // cout << "Message:" << message << ", keys=" << m_keys << endl;
        int max_substring = 0;
        string substring = "";
        unordered_set<char> chars_in_substring;
        for(int i=0; i<message.size(); i++){
            char next_char = message[i];
            auto it = chars_in_substring.find(next_char);
            if (it == chars_in_substring.end()){
                // cout << "\tNew char, substr=" << substring << ", max=" << max_substring << ", set=" << chars_in_substring.size() << endl;
                // New char
                
                if (chars_in_substring.size() == m_keys){
                    // We must delete some char from current
                    size_t last_pos; char chosen_char;
                    find_best_to_remove(substring, chars_in_substring, last_pos, chosen_char);

                    
                    // Delete susbtring until last ocurrence of this char
                    // char first_char = substring[0];
                    // size_t last_pos = substring.find_last_of(first_char);
                    substring.erase(0,last_pos+1);

                    // Remove said char from set
                    chars_in_substring.erase(chosen_char);
                }
                
                // Insert the new char
                chars_in_substring.insert(next_char);
            }else{
                // cout << "Seen char: '" << next_char << "'" << endl;
                // Char already in string, just add it
            }
            // Add next char to string
            substring += next_char;
            if (substring.size() > max_substring){max_substring = substring.size();}
            // cout << "\tOUT: substr=" << substring << ", max=" << max_substring << ", set=" << chars_in_substring.size() << endl;
        }
        cout << max_substring << endl;
        cin >> m_keys;
    }
    return 0;
}
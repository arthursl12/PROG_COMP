#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_KEYS 128
#define INF 0x3f3f3f

int char_bin[MAX_KEYS];


int main() {
    ios_base::sync_with_stdio(false);

    int m_keys; cin >> m_keys;
    while(m_keys != 0){
        char message_char[1234567];
        memset(char_bin, 0, MAX_KEYS*sizeof(int));
        string message; getline(cin, message); getline(cin, message);
        cout << "Message:" << message << ", keys=" << m_keys << endl;
        
        int substr_ini = 0;
        int substr_end = 1;
        int substr_size = 0;
        int max_size = -1;
        int used_keys = 0;
        for(int i=1; i<message.size(); i++){
            // Add chars until not possible anymore
            while(used_keys <= m_keys){
                cout << "\t Loop" << ": ini=" << substr_ini << ", end=" << substr_end << endl;
                char next_char = message[i];
                substr_end = i;
                substr_size++;
                if(char_bin[next_char] == 0){
                    // New char
                    used_keys++;
                }
                char_bin[next_char]++;
                i++;
                cout << "\t ELoop" << ": ini=" << substr_ini << ", end=" << substr_end << endl;
            }
            cout << "ini=" << substr_ini << ", end=" << substr_end << ", size=" << substr_size << ",max=" << max_size << endl;
            if (used_keys > m_keys){
                substr_ini++;
                substr_size--;
            }
            if (substr_size > max_size){
                max_size = substr_size;
            }

            // Remove an instance of removed char
            if (char_bin[message[substr_ini-1]] > 0){
                char_bin[message[substr_ini-1]] -= 1;
                if(char_bin[message[substr_ini-1]] == 0){
                    used_keys--;
                }
            }
            cout << "ini=" << substr_ini << ", end=" << substr_end << ", size=" << substr_size << ",max=" << max_size << endl;

            if (i >= 20)
                exit(1);
        }
        cout << max_size << endl;
    }
    return 0;
}
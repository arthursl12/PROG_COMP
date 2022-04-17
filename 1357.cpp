#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>

using namespace std;


void print_vector(vector<string>& vec){
    for (uint i=0; i<vec.size(); i++){
        cout << vec[i];
        if (i != vec.size() - 1){
            cout << " ";
        }else{
            cout << endl;
        }
    }
}

void from_braille(vector<string>& top,
                  vector<string>& mid, 
                  vector<string>& bot)
{
    string message = "";
    for(uint i=0; i<top.size(); i++){
        string itop = top[i];
        string imid = mid[i];
        if (itop == ".*"){
            if (imid == "**") message += "0";
            else message += "9";
        }else if (itop == "*."){
            if (imid == "..") message += "1";
            else if (imid == "*.") message += "2";
            else if (imid == ".*") message += "5";
            else message += "8"; 
        }else if (itop == "**"){
            if (imid == "..") message += "3";
            else if (imid == ".*") message += "4";
            else if (imid == "*.") message += "6";
            else message += "7";
        }else{
            exit(1);
        }
    }
    cout << message << endl;
}



void to_braille(string& braile){

    vector<string> top_braile{".*","*.","*.","**","**","*.","**","**","*.",".*"};
    vector<string> mid_braile{"**","..","*.","..",".*",".*","*.","**","**","*."};
    vector<string> bot_braile{"..","..","..","..","..","..","..","..","..",".."};


    vector<string> top, middle, bottom;

    for(uint i=0; i<braile.size(); i++){
        top.push_back(top_braile[stoi(string(1,braile[i]))]);
        middle.push_back(mid_braile[stoi(string(1,braile[i]))]); 
        bottom.push_back(bot_braile[stoi(string(1,braile[i]))]); // dá pra economizar aqui
    }

    print_vector(top);
    print_vector(middle);
    print_vector(bottom);
}


int main() {
    ios_base::sync_with_stdio(false);

    int D;
    while(cin >> D){
        if (D == 0){ break; }

        char op;
        cin >> op;
        if (op == 'S'){
            // Message to vector
            vector<int> message;
            string tmp;
            cin >> tmp;
            to_braille(tmp);
        }else{
            // op == 'B'
            vector<string> top, mid, bot;
            for(int i=0; i<D; i++){
                string tmp; cin >> tmp;
                top.push_back(tmp);
            }
            for(int i=0; i<D; i++){
                string tmp; cin >> tmp;
                mid.push_back(tmp);
            }
            for(int i=0; i<D; i++){
                string tmp; cin >> tmp;
                bot.push_back(tmp);
            }
            from_braille(top, mid, bot);
        }


    }

    return 0;
}
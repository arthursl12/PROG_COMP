#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <set>
#include <string>
#include <vector>

#include <stack>
#include <queue>


using namespace std;


int main() {
    ios_base::sync_with_stdio(false);

    int n_lines;
    while(cin >> n_lines){
        stack<int> mystack;
        queue<int> myqueue;
        priority_queue<int> myPqueue;

        bool canStack = true, canQueue = true, canPqueue = true;

        for(int i=0; i< n_lines; i++){
            int command;
            cin >> command;

            if (command == 1){
                int number;
                cin >> number;

                if (canStack) mystack.emplace(number);
                if (canQueue) myqueue.emplace(number);
                if (canPqueue) myPqueue.emplace(number);
            }else {
                // command == 2
                int number;
                cin >> number;
                
                if (canStack){
                    int resStack = mystack.top();
                    mystack.pop();
                    if (resStack != number) canStack = false;
                }
                if (canQueue){
                    int resQueue = myqueue.front();
                    if (resQueue != number) canQueue = false;
                    myqueue.pop();
                }
                if (canPqueue){
                    int resPqueue = myPqueue.top();
                    myPqueue.pop();

                    if (resPqueue != number) canPqueue = false;
                }
            }
        }

        if (canStack + canQueue + canPqueue == 0){
            cout << "impossible" << endl;
        }else if (canStack + canQueue + canPqueue >= 2){
            cout << "not sure" << endl;
        }else if (canStack){
            cout << "stack" << endl;
        }else if (canQueue){
            cout << "queue" << endl;
        }else if (canPqueue){
            cout << "priority queue" << endl;
        }
    }
    return 0;
}
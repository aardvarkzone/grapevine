#include <iostream> 
#include <map> 
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>
#include <tuple>

using namespace std; 

int main() {
    std::ios::sync_with_stdio(false);
    int people = 0;
    int connections = 0; 
    int days = 0; 

    cin >> people >> connections >> days;

    unordered_map<string, tuple<int, unordered_set<string>>> peopleMap;
    for (int i = 0; i < people; i++) {
        string name; 
        int skept;
        cin >> name >> skept;
        unordered_set <string> heard;
        peopleMap[name] = make_tuple(skept,heard);
    }
 
    unordered_map<string, unordered_set<string>> connectionsMap;  
    for (int i = 0; i < connections; i++) {
        string source; 
        string listener;
        cin >> source >> listener;
        if ((connectionsMap.find(source)) == connectionsMap.end()) {
            unordered_set <string> stringSet;
            stringSet.insert(listener);
            connectionsMap[source] = stringSet;
        } else {
            connectionsMap[source].emplace(listener);
        }
        if ((connectionsMap.find(listener)) == connectionsMap.end()) {
            unordered_set <string> stringSet;
            stringSet.insert(source);
            connectionsMap[listener] = stringSet;
        } else {
            connectionsMap[listener].emplace(source);
        }
    } 

    string source;
    cin >> source;
    queue<string> spreaders;
    spreaders.emplace(source);
    unordered_set<string> listeners;

    for (int i = 0; i < days; i++){
        queue<string> nextSpreaders;
        while (!spreaders.empty()){
            string spreader = spreaders.front();
            for (const auto& listener: connectionsMap[spreader]){
                listeners.emplace(listener);
                get<1>(peopleMap[listener]).emplace(spreader);
                if (get<0>(peopleMap[listener]) <= get<1>(peopleMap[listener]).size()){
                    nextSpreaders.emplace(listener);
                }
            }
            spreaders.pop();
        }
        spreaders = nextSpreaders;
    }



    listeners.erase(source);
    cout << (listeners.size()) << endl;
    return 0;
}

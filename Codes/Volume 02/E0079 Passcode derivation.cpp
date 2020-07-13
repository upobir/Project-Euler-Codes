# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 A common security method used for online banking is to ask the user for three random characters from a passcode. For example, if the 
 passcode was 531278, they may ask for the 2nd, 3rd, and 5th characters; the expected reply would be: 317.

 The text file, keylog.txt, contains fifty successful login attempts.

 Given that the three characters are always asked for in order, analyse the file so as to determine the shortest possible secret passcode 
 of unknown length.
*/

string shortestUniqueSuperSequence(string filePath){
    vector<string> sequences;
    fstream file(filePath, fstream::in);
    if(file.is_open()){
        while(file.good()){
            string s;
            file>>s;
            sequences.push_back(s);
        }
        file.close();
    }

    set<int> nodes;
    vector<vector<int>> adjacencyList(10);
    vector<int> indegree(10);
    for(string &s : sequences){
        for(char c : s) nodes.insert(c-'0');
    }
    for(string &s : sequences){
        for(int i = 1; i<s.size(); i++){
            int u = s[i-1]-'0';
            int v = s[i]-'0';
            adjacencyList[u].push_back(v);
            indegree[v]++;
        }
    }

    queue<int> q;
    for(int node = 0; node < 10; node++){
        if(indegree[node] == 0 && nodes.count(node) > 0) q.push(node);
    }

    string ans;
    while(q.size() > 0){
        int node = q.front();
        q.pop();
        ans.push_back(node+'0');
        for(int neighbour: adjacencyList[node]){
            indegree[neighbour]--;
            if(indegree[neighbour] == 0) q.push(neighbour);
        }
    }

    return ans;
}

int main(){
    Time(
        cout<<shortestUniqueSuperSequence("..\\..\\Data\\D0079 Passcode derivation.txt")<<endl;
    )
    return 0;
}

/*
Notes:
 This problem is a little bad in the sense that original passcode has unique characters which wasn't said, and without this assurance the 
 problem becomes np-hard. But with this assurance all this is just a dependancy graph and we need to just create a topological sorted order
 of the graph of dependancies.
 Complexity: O(|S|)
*/
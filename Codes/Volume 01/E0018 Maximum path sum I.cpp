# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
<FORMATTED>
 3
 7 4
 2 4 6
 8 5 9 3
 
 That is, 3 + 7 + 4 + 9 = 23.
 
 Find the maximum total from top to bottom of the triangle below:
 <FORMATTED>
 75
 95 64
 17 47 82
 18 35 87 10
 20 04 82 47 65
 19 01 23 75 03 34
 88 02 77 73 07 63 67
 99 65 04 28 06 16 70 92
 41 41 26 56 83 40 80 70 33
 41 48 72 33 47 32 37 16 94 29
 53 71 44 65 25 43 91 52 97 51 14
 70 11 33 28 77 73 17 78 39 68 17 57
 91 71 52 38 17 14 91 43 58 50 27 29 48
 63 66 04 68 89 53 67 30 73 16 69 87 40 31
 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

 NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same 
 challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
*/

char input[] = "\
75\n\
95 64\n\
17 47 82\n\
18 35 87 10\n\
20 04 82 47 65\n\
19 01 23 75 03 34\n\
88 02 77 73 07 63 67\n\
99 65 04 28 06 16 70 92\n\
41 41 26 56 83 40 80 70 33\n\
41 48 72 33 47 32 37 16 94 29\n\
53 71 44 65 25 43 91 52 97 51 14\n\
70 11 33 28 77 73 17 78 39 68 17 57\n\
91 71 52 38 17 14 91 43 58 50 27 29 48\n\
63 66 04 68 89 53 67 30 73 16 69 87 40 31\n\
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23\n\
";

vector<string> tokenizeWithChar(string &text, char delim){
    vector<string> ret;
    stringstream ss(text);
    std::string parts;
    while(getline(ss, parts, delim))
        ret.push_back(parts);
    return ret;
}

vector<vector<int>> parseGrid(char *grid){
    string str(grid);
    vector<vector<int>> retGrid;
    vector<string> rows = tokenizeWithChar(str, '\n');
    for(string &row : rows){
        vector<string> values = tokenizeWithChar(row, ' ');
        retGrid.push_back(vector<int>());
        for(string &value : values){
            retGrid.back().push_back(stoi(value));
        }
    }
    return retGrid;
}

ll maxPathSumTriangle(char *triangle){
    vector<vector<int>> grid = parseGrid(triangle);
    vector<vector<ll>> sumMemo(grid.size());
    
    for(int row = int(grid.size())-1; row >=0; row--){
        sumMemo[row].resize(grid[row].size());
        for(int i = 0; i<grid[row].size(); i++){
            sumMemo[row][i] = grid[row][i];
            if(row+1 < grid.size()){
                sumMemo[row][i] += max(sumMemo[row+1][i], sumMemo[row+1][i+1]);
            }
        }
    }
    return sumMemo[0][0];
}

int main(){
    Time(
        cout<<maxPathSumTriangle(input)<<endl;
    )
    return 0;
}

/*
Notes:
 This is a textbook dp problem, for every entry we calculate the maximum sum achievable if we start there, this way in the end we get that 
 maximum path sum for the topmost entry too. 
 Complexity: O(n*m)
*/
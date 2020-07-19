# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and down, is indicated 
 in bold red and is equal to 2427.

 131 673 234 103  18
 201  96 342 965 150
 630 803 746 422 111
 537 699 497 121 956
 805 732 524  37 331

 Find the minimal path sum from the top left to the bottom right by only moving right and down in matrix.txt, a 31K text file containing an 
 80 by 80 matrix.
*/

vector<string> tokenizeWithChar(string &text, char delim){
    vector<string> ret;
    stringstream ss(text);
    std::string parts;
    while(getline(ss, parts, delim))
        ret.push_back(parts);
    return ret;
}

vector<vector<int>> readNumbersCSV(string filePath){
    fstream file(filePath, fstream::in);
    vector<vector<int>> ret;
    if(file.is_open()){
        while(file.good()){
            string fullString;
            file>>fullString;
            vector<string> tokens = tokenizeWithChar(fullString, ',');
            ret.emplace_back();
            for(string &t : tokens){
                ret.back().push_back(stoi(t));
            }
            if(ret.back().size() == 0) ret.pop_back();
        }
        file.close();
    }
    return ret;
}

ll minGridMonotonePathSum(string filePath){
    vector<vector<int>> grid = readNumbersCSV(filePath);
    vector<vector<ll>> memo(grid.size(), vector<ll>(grid[0].size()));

    for(int row = 0; row<memo.size(); row++){
        for(int col = 0; col < memo[row].size(); col++){
            if(row == 0 && col == 0) 
                memo[row][col] = grid[row][col];
            else if(row == 0 || col == 0) 
                memo[row][col] = grid[row][col] + ((row == 0)?memo[row][col-1] : memo[row-1][col]);
            else
                memo[row][col] = grid[row][col] + min(memo[row-1][col], memo[row][col-1]);
        }
    }
    return memo.back().back();
}

int main(){
    Time(
        cout<<minGridMonotonePathSum("..\\..\\Data\\D0081 Path sum two ways.txt")<<endl;
    )
    return 0;
}

/*
Notes:
 We solve this via dynamic programming, memo[i][j] is the min path sum to get to (i, j) from (0, 0). then memo[i][j] depends on only 
 memo[i-1][j] and memo[i][j-1].
 Complexity: O(|S|)
*/
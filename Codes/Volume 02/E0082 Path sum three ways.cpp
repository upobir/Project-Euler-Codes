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

ll minGridLeftToRightPathSum(string filePath){
    vector<vector<int>> grid = readNumbersCSV(filePath);
    vector<vector<ll>> memoUp(grid.size(), vector<ll>(grid.size())), memoDown(grid.size(), vector<ll>(grid.size()));
    vector<vector<ll>> memo(grid.size(), vector<ll>(grid.size()));

    for(int col = 0; col<grid[0].size(); col++){
        for(int row = 0; row < grid.size(); row++){
            memoUp[row][col] = INT_MAX; 
            if(row > 0)
                memoUp[row][col] = min(memoUp[row][col], grid[row][col] + memoUp[row-1][col]);
            memoUp[row][col] = min(memoUp[row][col], grid[row][col] + ((col > 0)? memo[row][col-1] : 0));
        }
        for(int row = (int)grid.size()-1; row >= 0; row--){
            memoDown[row][col] = INT_MAX;
            if(row+1 < grid.size())
                memoDown[row][col] = min(memoDown[row][col], grid[row][col] + memoDown[row+1][col]);
            memoDown[row][col] = min(memoDown[row][col], grid[row][col] + ((col > 0)? memo[row][col-1] : 0));
        }
        for(int row = 0; row < grid.size(); row++){
            memo[row][col] = min(memoUp[row][col], memoDown[row][col]);
        }
    }

    ll ans = LLONG_MAX;
    for(int row = 0; row <grid.size(); row++)
        ans = min(ans, memo[row].back());

    return ans;
}

int main(){
    Time(
        cout<<minGridLeftToRightPathSum("..\\..\\Data\\D0082 Path sum three ways.txt");
    )
    return 0;
}

/*
Notes:
 We do a dp in this problem too. Here we compute memo value for each column, in column first we build two dp values, one representing coming
 from up another representing coming from down (since we won't U-turn in a row), then we mix those into one dp value.
 Complexity: O(|S|)
*/
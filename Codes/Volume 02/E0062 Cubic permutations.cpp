# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the 
 smallest cube which has exactly three permutations of its digits which are also cube.
 
 Find the smallest cube for which exactly five permutations of its digits are cube.
*/

string digitSignature(ll number){
    string ret = to_string(number);
    sort(ret.begin(), ret.end());
    return ret;
}

ll minCubeWithPermutaionCount(int count){
    unordered_map<string, pair<int, ll>> memory;
    ll bound = LLONG_MAX;
    ll ans = -1;
    for(ll num = 1 ; num; num++){
        ll cubed = num*num*num;
        if(cubed >= bound) break;
        string signature = digitSignature(cubed);

        if(memory.count(signature) == 0) memory[signature].second = cubed;
        memory[signature].first++;

        if(memory[signature].first == count){
            if(ans == -1){
                for(bound = 1; bound <= cubed; bound*=10);
                ans = memory[signature].second;
            }
            else{
                ans = min(ans, memory[signature].second);
            }
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<minCubeWithPermutaionCount(5)<<endl;
    )
    return 0;
}

/*
Notes:
 We create the cubes one by one and just insert their digit signatures one by one in an unordered map, this way we get the first count and 
 put a bound on numbers to compute after which we can return the smallest cube.
 Complexity: O(X^(1/3))
*/
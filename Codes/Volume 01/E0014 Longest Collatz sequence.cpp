# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The following iterative sequence is defined for the set of positive integers:

 n → n/2 (n is even)
 n → 3n + 1 (n is odd) 

 Using the rule above and starting with 13, we generate the following sequence:

 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1
 It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

 Which starting number, under one million, produces the longest chain?
 
 NOTE: Once the chain starts the terms are allowed to go above one million.
*/

int collatzChainLength(ll num, unordered_map<ll, int> &memo){
    if(memo.count(num)){
        if(memo[num] == -1) assert(!"Found cycle!");
        return memo[num];
    } 

    int ret = memo[num] = -1;
    if(num == 1)
        ret = 1;
    else if(num % 2 == 0)
        ret = collatzChainLength(num/2, memo) + 1;
    else
        ret = collatzChainLength((3*num+1)/2, memo) + 2;

    memo[num] = ret;
    return ret;
}

int longestCollatzChainerUntil(int maxNum){
    unordered_map<ll, int> collatzMemo;
    int ans = -1, best = -1;
    for(int num = 1; num<maxNum; num++){
        int chainLength = collatzChainLength(num, collatzMemo);
        if(chainLength > best){
            best = chainLength;
            ans = num;
        }
    }
    return ans;
}

int x[3];

int main(){
    Time(
        cout<<longestCollatzChainerUntil(1000*1000)<<endl;
    );
    return 0;
}

/*
Notes:
 Using a recursive dp we find the collartz chain length of numbers, since one number may come up many times. Also note that the solution is
 slower due to usage of map. using a static memo array with backtrack for larger number is actually faster, but used the map for generality.
 Complexity: O(n+x)
*/
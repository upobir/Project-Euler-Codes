# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The number 145 is well known for the property that the sum of the factorial of its digits is equal to 145:
 
 1! + 4! + 5! = 1 + 24 + 120 = 145
 
 Perhaps less well known is 169, in that it produces the longest chain of numbers that link back to 169; it turns out that there are only 
 three such loops that exist:
 
 169 → 363601 → 1454 → 169
 871 → 45361 → 871
 872 → 45362 → 872
 
 It is not difficult to prove that EVERY starting number will eventually get stuck in a loop. For example,
 
 69 → 363600 → 1454 → 169 → 363601 (→ 1454)
 78 → 45360 → 871 → 45361 (→ 871)
 540 → 145 (→ 145)
 
 Starting with 69 produces a chain of five non-repeating terms, but the longest non-repeating chain with a starting number below one million 
 is sixty terms.
 
 How many chains, with a starting number below one million, contain exactly sixty non-repeating terms?
*/

ll sumFuncDigits(ll num, vector<ll> &funcMap){
    ll sum = 0;
    while(num){
        int digit = num % 10;
        sum += funcMap[digit];
        num /= 10;
    }
    return sum;
}

pair<int, int> computeDigitFuncChain(ll num, vector<ll> &funcMap, unordered_map<ll, pair<int, int>> &memo){
    ll cur = num;
    vector<ll> seen;
    while(memo.count(cur) == 0){
        memo[cur] = {-1, seen.size()};
        seen.push_back(cur);
        cur = sumFuncDigits(cur, funcMap);
    }

    int index = seen.size();
    int period;

    if(memo[cur].first == -1){
        period = seen.size() - memo[cur].second;
        do{
            index--;
            memo[seen[index]] = {0, period};
        }while(seen[index] != cur);
    }

    int len = memo[cur].first;
    period = memo[cur].second;
    while(index != 0){
        index--;
        len++;
        memo[seen[index]] = {len, period};
    }

    return memo[num];
}

int countNumWithNonRepeatingDigitFactorialChain(int bound, int chainLength){
    unordered_map<ll, pair<int, int>> memo;
    vector<ll> funcMap(10);
    for(int digit = 0; digit < 10; digit++){
        funcMap[digit] = (digit == 0)? 1 : funcMap[digit-1]*digit;
    }

    int ans = 0;
    for(int num = 1; num <= bound; num++){
        pair<int, int> chain = computeDigitFuncChain(num, funcMap, memo);
        if(chain.first + chain.second == chainLength) 
            ans++;
    }
    return ans;
}

int main(){
    Time(
        cout<<countNumWithNonRepeatingDigitFactorialChain(1000000, 60)<<endl;
    )
    return 0;
}

/*
Notes:
 We use the old sumFuncDigit function to sum factorial of digits, we also use a dp style function to compute the non-repeating and 
 repeating parts of the chains by storing (non-repeating part, repeating part) in the memo map.
 Complexity: O(X)
*/
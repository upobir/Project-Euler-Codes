# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a 
 rather interesting sub-string divisibility property.

 Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

 * d2d3d4=406 is divisible by 2
 * d3d4d5=063 is divisible by 3
 * d4d5d6=635 is divisible by 5
 * d5d6d7=357 is divisible by 7
 * d6d7d8=572 is divisible by 11
 * d7d8d9=728 is divisible by 13
 * d8d9d10=289 is divisible by 17

 Find the sum of all 0 to 9 pandigital numbers with this property.
*/

# define bit(pos) (1ll << (pos))

vector<ll> listPandigitalWithDivisiveSubstrings(int len, vector<ll> divisors){
    ll mod = 1;
    for(int i = 0; i<len; i++) mod *= 10;

    vector<ll> pandigitals;
    queue<pair<ll, int>> bfsQueue;
    for(int digit = 1; digit < 10; digit++) 
        bfsQueue.emplace(digit, bit(digit));
    
    while(!bfsQueue.empty()){
        ll number;
        int mask;
        tie(number, mask) = bfsQueue.front();
        bfsQueue.pop();

        int numLen = __builtin_popcount(mask);
        if(numLen >= len){
            if(number % mod % divisors[numLen-len] != 0)
                continue;
        }

        if(numLen == 10){
            pandigitals.push_back(number);
            continue;
        }

        for(int digit = 0; digit < 10; digit++){
            if(bit(digit)&mask) continue;
            bfsQueue.emplace(number*10+digit, mask | bit(digit));
        }
    }
    return pandigitals;
}


ll sumPandigitalWithDivisiveSubstrings(int len, vector<ll> divisors){
    vector<ll> pandigitals = listPandigitalWithDivisiveSubstrings(len, divisors);
    ll sum = accumulate(pandigitals.begin(), pandigitals.end(), 0ll);
    return sum;
}

int main(){
    Time(
        cout<<sumPandigitalWithDivisiveSubstrings(3, {1, 2, 3, 5, 7, 11, 13, 17})<<endl;
    )
    return 0;
}

/*
Notes:
 We use a bfs that creates prefix of the numbers, along with numbers we keep track of masks so that, as nodes, we can easily get the length
 of the numbers as well as which digits are used, and when bfs reaches to a node, we check if the suffix is divisible by proper number, this
 way we find only required pandigital numbers.
 Complexity: O(X)
*/
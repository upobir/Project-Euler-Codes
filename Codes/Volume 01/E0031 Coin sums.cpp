# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 In the United Kingdom the currency is made up of pound (£) and pence (p). There are eight coins in general circulation:

 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p), and £2 (200p).
 It is possible to make £2 in the following way:

 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
 How many different ways can £2 be made using any number of coins?
*/

vector<ll> countKnapsackUnconstrained(vector<int> &weights, int maxSum){
    vector<ll> count(maxSum+1);
    count[0] = 1;
    for(int w : weights){
        for(int sum = w; sum <= maxSum; sum++){
            count[sum] += count[sum-w];
        }
    }
    return count;
}

ll countCoinSumWay(vector<int> coins, int value){
    vector<ll> dpCount = countKnapsackUnconstrained(coins, value);
    return dpCount[value];
}

int main(){
    Time(
        cout<<countCoinSumWay({1, 2, 5, 10, 20, 50, 100, 200}, 200)<<endl;
    )
    return 0;
}

/*
Notes:
 Basic problem of unconstriained knapsack, so we just use a dp to get the values, using each weight we update the count table in normal
 order, this ensures that a weight can be used as many times as required.
 Complexity: O(|w|n)
*/
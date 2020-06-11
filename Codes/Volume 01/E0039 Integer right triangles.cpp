# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

 {20,48,52}, {24,45,51}, {30,40,50}

 For which value of p ≤ 1000, is the number of solutions maximised?
*/

vector<vector<int>> divisorSieveTill(int maxNum){
    vector<vector<int>> divisors(maxNum+1);
    for(int divisor = 1; divisor <= maxNum; divisor++){
        for(int multiple = divisor; multiple <= maxNum; multiple += divisor)
            divisors[multiple].push_back(divisor);
    }
    return divisors;
}

vector<tuple<ll, ll, ll>> pythagoreanTriplesWithSum(ll sum, vector<ll> &divisors){
    vector<tuple<ll, ll, ll>> triples;

    for(int i = 0, j = 0; i<divisors.size(); i++){
        ll MplusN = divisors[i];
        if(MplusN % 2 == 0) continue;

        while(divisors[j] <= MplusN/2) j++;

        for(int k = j; k<i; k++){
            ll M = divisors[k];

            if((sum/MplusN) % M != 0) continue;
            if(__gcd(M, MplusN) != 1) continue;

            ll G = sum/(MplusN*M);
            ll N = MplusN - M;

            ll a = (M*M - N*N)*G;
            ll b = 2*M*N*G;
            ll c = (M*M + N*N)*G;
            triples.emplace_back(a, b, c);
        }
    }
    return triples;
}

int maxPythogoreanTripleWithSumTill(int maxNum){
    vector<vector<int>> divisors = divisorSieveTill(maxNum);
    int best = 0, ans = -1;
    for(int sum = 3; sum <= maxNum; sum++){
        vector<ll> lDivisors(divisors[sum].begin(), divisors[sum].end());
        vector<tuple<ll, ll, ll>> triples = pythagoreanTriplesWithSum(sum, lDivisors);

        if(triples.size() >= best){
            best = triples.size();
            ans = sum;
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<maxPythogoreanTripleWithSumTill(1000)<<endl;
    )
    return 0;
}

/*
Notes:
 Like problem 0009, we use the rep. of pythagorean triples for this, we use a sieve to first get divisor list for all numbers upto maxNum, 
 then just use that and the function from 0009 to get all solutions with given sum.
 Complexity: O(n * log^3 n)
*/
# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

 1/2	= 	0.5
 1/3	= 	0.(3)
 1/4	= 	0.25
 1/5	= 	0.2
 1/6	= 	0.1(6)
 1/7	= 	0.(142857)
 1/8	= 	0.125
 1/9	= 	0.(1)
 1/10	= 	0.1
 Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

 Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

// computes x^e mod m, m should fit in integer
ll modExpo(ll x, ll e, ll m){
    if(m == 1) return 0;
    ll ret = 1;
    while(e > 0){
        if(e & 1) ret = ret * x % m;
        x = x * x % m;
        e >>= 1;
    }
    return ret;
}

// returns multiplicative order of a mod m, primesOfPhiM are (prime, exponent) factorization of phi(m)
ll multiplicativeOrder(ll a, ll m, vector<pair<ll, int>> primesOfPhiM){
    ll order = 1;
    for(auto p : primesOfPhiM)
        for(int i = 0; i<p.second; i++) order *= p.first;
    for(auto p : primesOfPhiM){
        ll prime = p.first;
        for(int i = 0; i<p.second; i++){
            if(modExpo(a, order/prime, m) == 1) order /= prime;
            else break;
        }
    }
    return order;
}

vector<int> phiSieveTill(int maxNum){
    vector<int> phi(maxNum+1);
    iota(phi.begin(), phi.end(), 0);
    for(int p = 2; p <= maxNum; p+= 1 + (p > 2)){
        if(phi[p] != p) continue;
        for(int m = p; m <=maxNum; m+=p)
            phi[m] -= phi[m]/p;
    }
    return phi;
}

vector<vector<pair<int, int>>> primeFactorSieveTill(int maxNum){
    vector<vector<pair<int, int>>> primeFactors(maxNum+1);
    for(int p = 2; p<=maxNum; p += 1 + (p > 2)){
        if(!primeFactors[p].empty()) continue;
        for(int m = p, m2 = p; m<=maxNum; m+=p, m2 = m){
            primeFactors[m].emplace_back(p, 0);
            while(m2 % p == 0){
                primeFactors[m].back().second++;
                m2 /= p;
            }
        }
    }
    return primeFactors;
}

int longestRecurringCycleInverseUntil(int maxNum){
    vector<int> phi = phiSieveTill(maxNum-1);
    vector<vector<pair<int, int>>> primeFactors = primeFactorSieveTill(maxNum-1);

    int ans = -1, best = -1;
    for(int num = 1; num < maxNum; num++){
        int reducedNum = num;
        while(reducedNum % 2 == 0) reducedNum /= 2;
        while(reducedNum % 5 == 0) reducedNum /= 5;

        int phiVal = phi[reducedNum];
        vector<pair<ll, int>> primes(primeFactors[phiVal].begin(), primeFactors[phiVal].end());
        int period = multiplicativeOrder(10, reducedNum, primes);
        if(reducedNum == 1) period = 0;

        if(period > ans)
            ans = period, best = num;
    }
    return best;
}

int main(){
    Time(
        cout<<longestRecurringCycleInverseUntil(1000)<<endl;
    )
    return 0;
}

/*
Notes:
 the process of finding decimal rep. of 1/d basically imitates that of finding period of 10^k modulo d, which reduces to take away 2s and 5s
 from d and find 10's multiplicative order modulo that, so we use sieve to get phi values and prime factorizing of numbers as finding order
 requires testing divisors of the phi value. 
 Complexity: O(n * log^2 n)
*/
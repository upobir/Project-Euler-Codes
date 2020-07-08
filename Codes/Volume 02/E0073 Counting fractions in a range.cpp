# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
 
 If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
 
 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 
 It can be seen that there are 3 fractions between 1/3 and 1/2.
 
 How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper fractions for d ≤ 12,000?
*/

vector<int> muSieveTill(int maxNum){
    vector<int> mu(maxNum+1, 2);

    mu[1] = 1;
    for(int p = 2; p <= maxNum; p+=(p>2)+1){
        if(mu[p] != 2) continue;
        for(int multiple = p, mod = 1; multiple <= maxNum; multiple += p, mod++){
            if(mu[multiple] == 2) mu[multiple] = 1;
            mu[multiple] = ((mod % p == 0)? 0 : -mu[multiple]);
        }
    }
    return mu;
}

vector<vector<int>> divisorSieveTill(int maxNum){
    vector<vector<int>> divisors(maxNum+1);
    for(int divisor = 1; divisor <= maxNum; divisor++){
        for(int multiple = divisor; multiple <= maxNum; multiple += divisor)
            divisors[multiple].push_back(divisor);
    }
    return divisors;
}

ll countReducedFractionInRangeTillDenominator(ll numerator1, ll denominator1, ll numerator2, ll denominator2, int bound){
    vector<vector<int>> divisors = divisorSieveTill(bound);
    vector<int> mu = muSieveTill(bound);
    ll ans = 0;
    for(int num = 2; num <= bound; num++){
        int L = num*numerator1/denominator1;
        int R = (num*numerator2+denominator2-1)/denominator2 - 1;
        int term = 0;
        for(int divi : divisors[num]){
            term += mu[divi] * (R/divi - L/divi);
        }
        ans += term;
    }
    return ans;
}

int main(){
    Time(
        cout<<countReducedFractionInRangeTillDenominator(1, 3, 1, 2, 12000)<<endl;
    )
    return 0;
}

/*
Notes:
 This is like last problem but we need to count coprimes in a range, the range being floor(num*n1/d1)+1 to ceil(num*n2/d2)-1. Now using 
 mobius function mu(n) we can count coprimes less than k to a number n, the formula is- sum [d | n] (mu(d) * floor(k/d)). So using this we
 can find coprimes upto upper bound and subtract those lower than lower bound. We just need to compute divisors and mu by sieve first.
 Complexity: O(n log n)
*/
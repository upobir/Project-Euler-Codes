# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
 If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
 
 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 
 It can be seen that 2/5 is the fraction immediately to the left of 3/7.
 
 By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order of size, find the numerator of the fraction immediately 
 to the left of 3/7.
*/

class fraction{
private:
    ll numerator, denominator;
    void normalize(){
        if(denominator < 0) 
            numerator = -numerator, denominator = -denominator;
        ll gcd = __gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
public:
    fraction(ll numerator = 0, ll denominator = 1, bool normalized = false){
        assert(denominator != 0);
        this->numerator = numerator;
        this->denominator = denominator;
        if(!normalized)
            normalize();
    }

    ll getNumerator(){ return numerator;}
    ll getDenominator(){ return denominator;}

    bool operator<(fraction other){
        ll gcd1 = __gcd(numerator, other.numerator);
        ll gcd2 = __gcd(denominator, other.denominator);
        return numerator * other.denominator < other.numerator * denominator;
    }
};

int closestLeftFractionTillDenominator(int numerator, int denominator, int bound){
    fraction ans(0, 1);
    for(int denom = 2; denom <= bound; denom++){
        int numer = (ll(numerator)*ll(denom) + denominator-1)/denominator;
        numer--;
        fraction candidate(numer, denom);

        if(ans < candidate){
            ans = candidate;
        }
    }
    return ans.getNumerator();
}

int main(){
    Time(
        cout<<closestLeftFractionTillDenominator(3, 7, 1000000)<<endl;
    )
    return 0;
}

/*
Notes:
 For every possible denominator d we can easily find closest left fraction to a/b using n = ceil((a*d)/b)-1, then n/d is the closest left 
 fraction using d as denominator. although we do not test for gcd(n, d) = 1, but that's because if n/d is not reduced n'/d' has been 
 already tested and so n/d won't be answer.
 Complexity: O(n * log n)
*/
# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

 a^2 + b^2 = c^2
 For example, 32 + 42 = 9 + 16 = 25 = 52.

 There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 Find the product abc.
*/

vector<ll> getDivisors(ll num){
    vector<ll> ret;
    for(ll d = 1; d*d <= num; d++){
        if(num % d != 0) continue;
        ret.push_back(d);
        if(num/d != d) ret.push_back(num/d);
    }
    sort(ret.begin(), ret.end());
    return ret;
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

ll pythogoreanTripleProductOfSum(ll sum){
    sum /= 2;
    vector<ll> divisors = getDivisors(sum);

    vector<tuple<ll, ll, ll>> triples = pythagoreanTriplesWithSum(sum, divisors);

    if(!triples.empty()){
        ll a, b, c;
        tie(a, b, c) = triples[0];
        return a*b*c;
    }
    
    return -1;
}

int main(){
    Time(
        cout<<pythogoreanTripleProductOfSum(1000)<<endl;
    )
    return 0;
}

/*
Notes:
 We know that primitve pythagorean triples are a = m*m-n*n, b = 2*m*n, c = m*m+n*n (one of m, n is even). and by multiplying g with them we 
 get all triples. So sum = 2*m*(m+n)*g, we first fix m+n which must be odd, then find m >= (m+n)/2.
 Complexity: O(n^(2/3) * log n)
*/
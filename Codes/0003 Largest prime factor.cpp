# include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
# include "TimeMacro.h"

/*
Statement:
 The prime factors of 13195 are 5, 7, 13 and 29.

 What is the largest prime factor of the number 600851475143 ?
*/

vector<ll> primeFactorize(ll num){
    vector<ll> primes;
    for(ll p = 2; p*p <= num; p++){
        if(num % p != 0)
            continue;
        while(num % p == 0){
            num /= p;
            primes.push_back(p);
        }
    }
    if(num != 1)
        primes.push_back(num);
    return primes;
}

ll largestPrimeFactor(ll num){
    vector<ll> primes = primeFactorize(num);
    ll maxPrime = primes.back();
    return maxPrime;
}

int main(){
    Time(
        cout<<largestPrimeFactor(600851475143)<<endl;
    );
}

/*
Notes:
 We iterater until sqrt(num) and whenever find a divisor, use it to completely divide num. This makes sure that only primes are found.
 Complexity: O(sqrt(n))
*/
# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
 
 What is the 10001st prime number?
*/

vector<int> primeSieveTill(int maxNum){
    if(maxNum == 1) return vector<int>();
    vector<bool> oddComposite(maxNum/2+1);  // oddComposite[i] = whether 2*i+1 is non-prime
    vector<int> primes{2};

    for(int p = 3; p <= maxNum; p+=2){
        if(oddComposite[p>>1]) continue;

        primes.push_back(p);

        if(maxNum/p < p) continue;
        for(int multiple = p*p; multiple <= maxNum; multiple += p+p)
            oddComposite[multiple/2] = true;
    }
    return primes;
}

ll nthPrime(ll n){
    ll guessBound = n * (log(n+1) + log(log(n+1))) + 2;
    vector<int> primes = primeSieveTill(guessBound);
    assert(primes.size() >= n);
    return ll(primes[n-1]);
}

int main(){
    Time(
        cout<<nthPrime(10001)<<endl;
    );
    return 0;
}

/*
Notes:
 We find the nth prime by sieve, a bound for nth prime is n(ln n + ln ln n), which is modified here to work for any n. Then we sieve till 
 that bound. Do note that the sieve can be optimized more.
 Complexity: O(n * log n * log log n);
*/
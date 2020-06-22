# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statment:
 Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
 
 37 36 35 34 33 32 31
 38 17 16 15 14 13 30
 39 18  5  4  3 12 29
 40 19  6  1  2 11 28
 41 20  7  8  9 10 27
 42 21 22 23 24 25 26
 43 44 45 46 47 48 49
 
 It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 
 numbers lying along both diagonals are prime; that is, a ratio of 8/13 ≈ 62%.
 
 If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed. If this process is 
 continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10%?
*/

typedef unsigned long long ull;
ull modularMultiply(ull a, ull b, ull m){
    if(a >= m) a %= m;
    if(b >= m) b %= m;
    ull q = ull((long double)a * b / m);
    ll r = ll(a*b-q*m) % ll(m);
    return r < 0 ? r + m : r;
}

ll modularExpo(ll x, ll e, ll m){
    if(m == 1) return 0;
    ll ret = 1;
    while(e > 0){
        if(e & 1) ret = modularMultiply(ret, x, m);
        x = modularMultiply(x, x, m);
        e >>= 1;
    }
    return ret;
}

bool rabinMillerPrimalityCheck(ll number, int tests = 50){
    if(number < 4) return number > 1;
    if(number % 2 == 0) return false;

    ll x = number-1;
    int e = __builtin_ctzll(x);
    x >>= e;
    mt19937_64 rng((unsigned)chrono::system_clock::now().time_since_epoch().count());

    while(tests-- > 0){
        ll witness = rng()%(number-3)+2;
        witness = modularExpo(witness, x, number);
        if(witness <= 1) continue;
        for(int i = 0; i<e && witness != number-1; i++)
            witness = modularMultiply(witness, witness, number);
        
        if(witness != number-1) return false;
    }
    return true;
}

int squareSizeTillDiagonalPrimeLessThan(double percentage){
    int totalCount = 1;
    int primeCount = 0;
    for(ll i = 1, side = 3; ; i++, side += 2){
        totalCount += 4;
        primeCount += rabinMillerPrimalityCheck(4*i*i+2*i+1);
        primeCount += rabinMillerPrimalityCheck(4*i*i+1);
        primeCount += rabinMillerPrimalityCheck(4*i*i-2*i+1);
        if(totalCount*percentage/100.0 > primeCount) return side;
    }
}

int main(){
    Time(
        cout<<squareSizeTillDiagonalPrimeLessThan(10)<<endl;
    )
    return 0;
}

/*
Notes:
 We know the formula to find the numbers on diagonal from 0028, so we just add a layer of number and check how many primes are added. But
 since the numbers can be large we need faster prime checker, so I used randomized rabin miller, although there is a faster version of 
 rabin miller, I used randomized version for sake of generality.
 Complexity: O(X * log X * t)
*/
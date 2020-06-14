# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

 Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
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

string sumSelfPowersLastDigits(int maxNum, int digits){
    ll mod = 1;
    for(int i = 0; i<digits; i++) mod *= 10;
    ll sum = 0;
    for(int number = 1; number <= maxNum; number++){
        sum += modularExpo(number, number, mod);
        sum %= mod;
    }
    string ret = to_string(sum);
    while(ret.size() < digits) ret.insert(ret.begin(), '0');
    return ret;
}

int main(){
    Time(
        cout<<sumSelfPowersLastDigits(1000, 10)<<endl;
    )
    return 0;
}

/*
Notes:
 Since last 10 digits = number mod 10^10, so we just use modular exponentiation to get the individual terms. There is fear of overflow, so
 we use special multiplication to make sure no overflow happens
 Complexity: O(n * log n)
*/
# include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

/*
Statement:
 The prime factors of 13195 are 5, 7, 13 and 29.

 What is the largest prime factor of the number 600851475143 ?
*/

ll largestPrimeFactor(ll num){
    ll maxPrime = 0;
    for(ll divi = 2; divi*divi<=num; divi++){
        if(num % divi != 0) 
            continue;
        maxPrime = divi;
        while(num % divi == 0) num /= divi;
    }

    if(num != 1) maxPrime = num;
    return maxPrime;
}

int main(){
    cout<<largestPrimeFactor(600851475143)<<endl;
}

/*
Notes:
 We iterater until sqrt(num) and whenever find a divisor, use it to completely divide num. This makes sure that only primes are found.
 Complexity: O(sqrt(n))
*/
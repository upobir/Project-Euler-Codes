# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right, and 
 remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.

 Find the sum of the only eleven primes that are both truncatable from left to right and right to left.

 NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
*/

bool isPrime(ll number){
    if(number == 2) return true;
    if(number == 1 || number % 2 == 0) return false;

    for(ll divi = 3; divi*divi <= number; divi+=2){
        if(number % divi == 0) return false;
    }
    return true;
}

vector<ll> bfsGetLeftTruncatablePrimes(){
    vector<ll> truncatables;
    vector<int> addableDigits{1, 3, 7, 9};
    queue<ll> bfsQueue({2, 3, 5, 7});
    while(!bfsQueue.empty()){
        ll truncPrime = bfsQueue.front();
        bfsQueue.pop();
        truncatables.push_back(truncPrime);

        for(int d : addableDigits){
            ll newTruncPrime = truncPrime*10 + d;
            if(isPrime(newTruncPrime))
                bfsQueue.push(newTruncPrime);
        }
    }
    return truncatables;
}

ll sumTruncatablePrimes(){
    vector<ll> leftTruncatables = bfsGetLeftTruncatablePrimes();
    vector<ll> truncatablePrimes;

    for(ll truncPrime : leftTruncatables){
        ll mod = 10;
        bool possible = true;
        while(possible && mod <= truncPrime){
            ll testSuffix = truncPrime % mod;
            if(!isPrime(testSuffix)) possible = false;
            mod *= 10;
        }
        if(possible) truncatablePrimes.push_back(truncPrime);
    }

    ll sum = 0;
    for(ll truncPrime : truncatablePrimes)
        if(truncPrime >= 10) sum += truncPrime;
    return sum;
}

int main(){
    Time(
        cout<<sumTruncatablePrimes()<<endl;
    )
    return 0;
}

/*
Notes:
 First we use a bfs to get all left-truncatable prime, since this have an obvious recursive pattern and adding digit to right is easy. Once
 we get a list of those, we check each one for right-truncability.
 Complexity: O(X)
*/
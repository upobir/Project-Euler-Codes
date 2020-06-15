# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

 9 = 7 + 2×1^2
 15 = 7 + 2×2^2
 21 = 3 + 2×3^2
 25 = 7 + 2×3^2
 27 = 19 + 2×2^2
 33 = 31 + 2×1^2

 It turns out that the conjecture was false.

 What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
*/

class primesDynamicSieve{
private:
    vector<bool> isComposite;
    vector<int> primes;

    void resieveUntil(int maxNum){
        int prvMax = isComposite.size();
        isComposite.resize(maxNum);
        isComposite[1] = true;

        for(int p = 2; p < maxNum; p+=1 + (p>2)){
            if(isComposite[p]) continue;
            if(p >= prvMax) primes.push_back(p);

            for(int m = p * max(2, (prvMax-1)/p+1); m<maxNum; m += p)
                isComposite[m] = true;
        }
        return;
    }

public:
    primesDynamicSieve(){
        isComposite.resize(1);
    }

    int lastComputed(){
        return isComposite.size()-1;
    }

    bool isPrime(int number){
        while(number >= isComposite.size())
            resieveUntil(2*isComposite.size());
        return !isComposite[number];
    }

    int lastPrimeCount(){
        return primes.size();
    }

    int nthPrime(int n){
        while(n >= primes.size())
            resieveUntil(2*isComposite.size());
        return primes[n];
    }
};

int firstDisproveGoldbachOtherConjecture(){
    primesDynamicSieve sPrimes;
    int num = 1;
    while(true){
        num += 2;
        if(sPrimes.isPrime(num)) continue;

        bool possible = false;
        for(int sqNum = 1; !possible && 2*sqNum*sqNum < num; sqNum++){
            int remaining = num - 2*sqNum * sqNum;
            if(sPrimes.isPrime(remaining)){
                possible = true;
            }
        }

        if(!possible) return num;
    }
}

int main(){
    Time(
        cout<<firstDisproveGoldbachOtherConjecture()<<endl;
    )
    return 0;
}

/*
Notes:
 Like before we used a dynamic sieve to make the job more efficient for finding primes and for every odd number, we checked every square 
 upto it.
 Complexity: O(X * sqrt(X))
*/
# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values: 13, 23, 43, 53, 73, and 83, are 
 all prime.

 By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number is the first example having seven primes among the 
 ten generated numbers, yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member 
 of this family, is the smallest prime with this property.

 Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight 
 prime value family.
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

# define bit(position) (1ll << (position))

bool isPossiblePrimeFamily(int number, int base, int size, primesDynamicSieve &sPrimes){
    int goodDigits = base - size, tmpPrime = number;
    vector<vector<int>> positions(goodDigits+1);
    vector<int> basePower;

    while(tmpPrime){
        int digit = tmpPrime % base;
        if(digit < positions.size())
            positions[digit].push_back(basePower.size());
        basePower.push_back((basePower.empty())? 1 : basePower.back()*base);
        tmpPrime /= base;
    }

    for(int digit = 0; digit < positions.size(); digit++){
        for(int mask = 1; mask < bit(positions[digit].size()); mask++){
            int summand = 0;
            for(int element = 0; element < positions[digit].size(); element++)
                if(bit(element)&mask) summand += basePower[positions[digit][element]];
            
            int primes = 0;
            for(int i = 0, familyNum = number; i<base-digit; i++, familyNum += summand){
                if(sPrimes.isPrime(familyNum))
                    primes++;
                if(primes + (base-digit-1-i) < size) 
                    break;
                if(primes == size)
                    break;
            }
            if(primes == size)
                return true;
        }
    }
    return false;
}

ll smallestPrimeFamilyMember(int base, int size){
    primesDynamicSieve sPrimes;
    for(int i = 0; ;i++){
        int prime = sPrimes.nthPrime(i);
        if(isPossiblePrimeFamily(prime, base, size, sPrimes))
            return prime;
    }
}

int main(){
    Time(
        cout<<smallestPrimeFamilyMember(10, 8)<<endl;
    )
    return 0;
}

/*
Notes:
 We use a dynamic sieve to keep iterating on primes and check if this can be the first number of a k-family of primes, for that we fix a 
 digit and try to change subset of that digits to get k primes. There are two optimizations here, first we don't do this for all digit, 
 rather try with only digits s.t. it's still possible to get k primes with digits above that and when changing the digits when we come to 
 a point that all of the rest being prime won't still give us k primes, we break, this gives a so far good solution.
*/
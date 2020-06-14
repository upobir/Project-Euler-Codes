# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The first two consecutive numbers to have two distinct prime factors are:

 14 = 2 × 7
 15 = 3 × 5

 The first three consecutive numbers to have three distinct prime factors are:

 644 = 2² × 7 × 23
 645 = 3 × 5 × 43
 646 = 2 × 17 × 19.

 Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
*/

class primeFactorsDynamicSieve{
private:
    vector<vector<pair<int, int>>> primeFactors;

    void resieveUntil(int maxNum){
        int prvMax = primeFactors.size();
        primeFactors.resize(maxNum);

        for(int p = 2; p < maxNum; p+=1 + (p>2)){
            if(primeFactors[p].size() > 1) continue;
            if(primeFactors[p].size() == 1 && primeFactors[p].back().second > 1) continue;

            for(int m = p * ((prvMax-1)/p+1), m2 = m; m<maxNum; m += p, m2 = m){
                primeFactors[m].emplace_back(p, 0);
                while(m2 % p == 0){
                    primeFactors[m].back().second++;
                    m2 /= p;
                }
            }
        }
        return;
    }

public:
    vector<int> primes;

    primeFactorsDynamicSieve(){
        primeFactors.resize(1);
    }

    int lastComputed(){
        return primeFactors.size()-1;
    }

    const vector<pair<int, int>>& operator[](int number){
        while(number >= primeFactors.size())
            resieveUntil(2*primeFactors.size());
        return primeFactors[number];
    }
};

ll consecutiveKNumsWithKPrimeFactors(int count){
    primeFactorsDynamicSieve sPrimeFactors;
    int seen = 0, number = 1;
    while(true){
        if(sPrimeFactors[number].size() == count)
            seen++;
        else 
            seen = 0;
        if(seen == count)
            return number-count+1;
        number++;
    }
}

int main(){
    Time(
        cout<<consecutiveKNumsWithKPrimeFactors(4)<<endl;
    )
    return 0;
}

/*
Notes:
 As before we create a dynamic sieve class for getting prime factors of numbers, and keep checking until we see k numbers with k primes. 
 We keep track of how many numbers with k primes we have seen so far, so that this can be a linear process.
 Complexity: O(X * log log x)
*/
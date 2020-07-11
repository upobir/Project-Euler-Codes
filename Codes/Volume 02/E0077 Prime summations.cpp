# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 It is possible to write ten as the sum of primes in exactly five different ways:
 
 7 + 3
 5 + 5
 5 + 3 + 2
 3 + 3 + 2 + 2
 2 + 2 + 2 + 2 + 2
 
 What is the first value which can be written as the sum of primes in over five thousand different ways?
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

vector<ll> countKnapsackUnconstrained(vector<int> &weights, int maxSum){
    vector<ll> count(maxSum+1);
    count[0] = 1;
    for(int w : weights){
        for(int sum = w; sum <= maxSum; sum++){
            count[sum] += count[sum-w];
        }
    }
    return count;
}

int minSumWithPrimePartitionOver(int bound){
    primesDynamicSieve primes;
    int guessBound = 1;
    vector<int> weights;
    vector<ll> counts;
    for(int sum = 2; ;sum++){
        if(sum > guessBound){
            for(int num = guessBound+1; num <=2*guessBound; num++)
                if(primes.isPrime(num)) weights.push_back(num);
            guessBound *= 2;
            counts = countKnapsackUnconstrained(weights, guessBound);
        }
        if(counts[sum]-primes.isPrime(sum) > bound)
            return sum;
    }
}

int main(){
    Time(
        cout<<minSumWithPrimePartitionOver(5'000)<<endl;
    )
    return 0;
}

/*
Notes:
 Like coin summations we use a dp to find count of partitions using weights, also note that since we do not know the answer, we keep an
 guessbound which we scale by two and recompute the dp table. This makes the code work in amortized efficiency.
 Complexity: O(X^2)
*/
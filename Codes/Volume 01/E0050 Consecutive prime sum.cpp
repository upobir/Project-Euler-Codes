# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The prime 41, can be written as the sum of six consecutive primes:

 41 = 2 + 3 + 5 + 7 + 11 + 13
 This is the longest sum of consecutive primes that adds to a prime below one-hundred.

 The longest sum of consecutive primes below one-thousand that adds to a prime, contains 21 terms, and is equal to 953.

 Which prime, below one-million, can be written as the sum of the most consecutive primes?
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

int longestConseuctivePrimeSumPrimeTill(int maxNum){
    vector<int> primes = primeSieveTill(maxNum-1);
    vector<bool> isPrime(maxNum);
    for(int p : primes) isPrime[p] = true;

    int best = 0, ans = -1;
    for(int st = 0; st<primes.size(); st++){
        for(int fn = st+1, sum = primes[st]; fn<primes.size(); fn++){
            sum += primes[fn];
            if(sum >= maxNum) break;

            if(isPrime[sum]){
                int len = fn-st+1;
                if(len > best){
                    best = len;
                    ans = sum;
                }
            }
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<longestConseuctivePrimeSumPrimeTill(1000*1000)<<endl;
    )
    return 0;
}

/*
Notes:
 The code is simple, the twist is why it's fast, consider k length sums, p1+p2+...+pk= sum, then p1 <= maxNum/k, so for each we get maxNum/k
 sums, in the code however I implemented it so that from each starting term we keep going forward until sum becomes too big, basically both
 just count all possible sum < maxNum, so it's complexity is like sieve's.
 Complexity: O(n * log n)
*/
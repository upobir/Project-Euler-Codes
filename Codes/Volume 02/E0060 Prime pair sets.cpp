# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order the result will always be 
 prime. For example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four primes, 792, represents the lowest sum for a set 
 of four primes with this property.
 
 Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
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

ll SPRP[7] = {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL};
bool rabinMillerPrimalityCheckWithSPRP(ll number){
    if(number < 4) return number > 1;
    if(number % 2 == 0) return false;
    if(number % 3 == 0) return false;

    ll x = number-1;
    int e = __builtin_ctzll(x);
    x >>= e;

    for(int t = 0; t < 7; t++){
        ll witness = SPRP[t];
        witness = modularExpo(witness, x, number);
        if(witness <= 1) continue;
        for(int i = 0; i<e && witness != number-1; i++)
            witness = modularMultiply(witness, witness, number);
        
        if(witness != number-1) return false;
    }
    return true;
}

ll concatenatedNumber(int x, int y){
    if(y == 0) return x*10l;
    int tmp = y;
    ll ret = x;
    while(tmp){
        tmp /= 10;
        ret *= 10;
    }
    ret += y;
    return ret;
}

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

enum triBool{UNKNOWN=0, TRUE, FALSE};
bool memoizedConcatenationPrimeCheck(int x, int y, primesDynamicSieve &primes, vector<vector<triBool>> &memoConcatPrimes){
    if(memoConcatPrimes.size() <= x) memoConcatPrimes.resize(x+1);
    if(memoConcatPrimes[x].size() <= y) memoConcatPrimes[x].resize(y+1);

    if(memoConcatPrimes[x][y] != UNKNOWN) return memoConcatPrimes[x][y] == TRUE;
    
    int px = primes.nthPrime(x), py = primes.nthPrime(y);

    ll concatenated = concatenatedNumber(px, py);
    if(!rabinMillerPrimalityCheckWithSPRP(concatenated)){
        memoConcatPrimes[x][y] = FALSE;
        return false;
    }
    concatenated = concatenatedNumber(py, px);
    if(!rabinMillerPrimalityCheckWithSPRP(concatenated)){
        memoConcatPrimes[x][y] = FALSE;
        return false;
    }

    memoConcatPrimes[x][y] = TRUE;
    return true;
}

bool isConcatenationExtendable(vector<int> &v, int p, primesDynamicSieve &primes, vector<vector<triBool>> &memoConcatPrimes){
    for(int x : v){
        if(!memoizedConcatenationPrimeCheck(x, p, primes, memoConcatPrimes)) return false;
    }
    return true;
}

int minSumConcatenationPrimes(int count){
    primesDynamicSieve primes;
    vector<vector<pair<int, vector<int>>>> memo(count+1); 
    vector<vector<triBool>> memoConcatPrimes;

    for(int sum = 2; ;sum++){
        for(int cnt = 1; cnt <= count; cnt++){
            if(cnt == 1){
                int lastIndex = ((memo[cnt].empty())? -1 : memo[cnt].back().second[0]);
                if(primes.nthPrime(lastIndex+1) == sum)
                    memo[cnt].emplace_back(sum, vector<int>(1, lastIndex+1));
            }
            else{
                int index = 0;
                for(int i = int(memo[cnt-1].size())-1; i>= 0; i--){
                    int p = sum - memo[cnt-1][i].first;
                    if(p >= memo[cnt-1][i].first) break;

                    while(primes.nthPrime(index) < p) index++;
                    if(primes.nthPrime(index) > p) continue;
                    if(index >= memo[cnt-1][i].second.back()) continue;
                    
                    if(isConcatenationExtendable(memo[cnt-1][i].second, index, primes, memoConcatPrimes)){
                        memo[cnt].emplace_back(sum, memo[cnt-1][i].second);
                        memo[cnt].back().second.push_back(index);
                    }
                }
            }
        }
        if(!memo[count].empty()){
            return memo[count][0].first;
        }
    }
    
}

int main(){
    Time(
        cout<<minSumConcatenationPrimes(5)<<endl;
    )
    return 0;
}

/*
Notes:
 Here I struggled a lot to bring some form of generality, basically a list of prime sets are kept for each count <= input (sorted by sum). 
 to populate them with new sums, we consider list of count-1 and try to add with it a new prime, Since the concatenation prime check is
 very costly, we memoized that in a 2d vector too. that's about it, wish I could make it faster.
 Complexity: O(X^2)
*/
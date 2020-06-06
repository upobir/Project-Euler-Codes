# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Euler discovered the remarkable quadratic formula:

 n^2+n+41

 It turns out that the formula will produce 40 primes for the consecutive integer values 0≤n≤39. However, when n=40,402+40+41=40(40+1)+41 
 is divisible by 41, and certainly when n=41,412+41+41 is clearly divisible by 41.

 The incredible formula n2−79n+1601 was discovered, which produces 80 primes for the consecutive values 0≤n≤79. The product of the 
 coefficients, −79 and 1601, is −126479.

 Considering quadratics of the form:

 n^2+an+b, where |a|<1000 and |b|≤1000

 where |n| is the modulus/absolute value of n
 e.g. |11|=11 and |−4|=4
 Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive 
 values of n, starting with n=0.
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

int getPrimeChainLen(int a, int b, vector<bool> &isPrime){
    int x = 0;
    while(true){
        int value = x*x+a*x+b;
        if(value < 0) return x;
        if(!isPrime[value]) return x;
        x++;
    }
}

int coefProdOfMaxPrimeQuadPoly(int aBound, int bBound){
    int resBound = bBound*bBound + aBound*bBound + bBound;
    vector<int> primes = primeSieveTill(resBound);
    vector<bool> isPrime(resBound+1);
    for(int p : primes) isPrime[p] = true;

    int bestPrimeChain = 0, ans = 0;
    for(int i = 0, b = primes[0]; i<primes.size() && b <= bBound; i++, b = primes[i]){
        int start = lower_bound(primes.begin(), primes.end(), -aBound+b+1) - primes.begin();
        if(start == primes.size()) continue;

        for(int j = start, a = primes[j] - 1 - b; j<primes.size() && a <=aBound; j++, a = primes[j] - 1 - b){

            int len = getPrimeChainLen(a, b, isPrime);
            if(len > bestPrimeChain){
                bestPrimeChain = len;
                ans = a * b;
            }
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<coefProdOfMaxPrimeQuadPoly(0, 2)<<endl;
    )
    return 0;
}

/*
Notes:
 if the quadratic polynomial outputs prime at n = 0, then b is prime and if b is prime, bBound >=2 and then n^2+2 even gives two primes.
 so we can only look at polynomials which output prime at n = 0 and n = 1 -> b is prime and 1+a+b is prime, so we first find all prime upto
 max value b^2+ab+b, then iterate on primes p(0) and p(1) keeping the constraints in check. For each polynomial then we find the longest
 chain, which is actually very small.
 Complexity: O(x * n * m / log n / log m)
*/
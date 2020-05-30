# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

 Find the sum of all the primes below two million.
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

ll sumPrimesBelow(ll maxVal){
    vector<int> primes = primeSieveTill(maxVal-1);
    ll sum = 0;
    for(int p : primes)
        sum += p;
    return sum;
}

int main(){
    Time(
        cout<<sumPrimesBelow(2*1000*1000)<<endl;
    );
    return 0;
}

/*
Notes:
 Just using sieve to find the primes and adding them.
 Complexity(n * log log n)
*/
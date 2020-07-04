# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statment:
 Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of positive numbers less than or equal 
 to n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
 The number 1 is considered to be relatively prime to every positive number, so φ(1)=1.
 
 Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of 79180.
 
 Find the value of n, 1 < n < 10^7, for which φ(n) is a permutation of n and the ratio n/φ(n) produces a minimum.
*/

vector<int> phiSieveTill(int maxNum){
    vector<int> phi(maxNum+1);
    iota(phi.begin(), phi.end(), 0);

    for(int p = 2; p <= maxNum; p+=(p>2)+1){
        if(phi[p] != p) continue;

        for(int multiple = p; multiple <= maxNum; multiple += p)
            phi[multiple] -= phi[multiple]/p;
    }
    return phi;
}

string digitSignature(ll number){
    string ret = to_string(number);
    sort(ret.begin(), ret.end());
    return ret;
}

int maxRatioNbyPhiOfPermutationUntil(int maxBound){
    vector<int> phi = phiSieveTill(maxBound-1);
    int digitBound = 1;
    int ans = 0;
    double best = DBL_MAX;
    for(int num = 2; num < maxBound; num++){
        if(num == digitBound*10) digitBound *= 10;
        if(phi[num] < digitBound) continue;
        if(digitSignature(num) == digitSignature(phi[num])){
            double candidate = double(num)/double(phi[num]);
            if(best > candidate){
                best = candidate;
                ans = num;
            }
        }
    }
    return ans;
}

int main(){
    Time(
        cout<<maxRatioNbyPhiOfPermutationUntil(10000000);
    )
}

/*
Note:
 As before, using a sieve we found the phi values and checked digit signatures
 Complexity: O(n log log n * log n) 
*/
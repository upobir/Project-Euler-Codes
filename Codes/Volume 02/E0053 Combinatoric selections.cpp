# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
 There are exactly ten ways of selecting three from five, 12345:

 123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

 In combinatorics, we use the notation, (5C3)=10.

 In general, (nCr)=n!/(r!(n−r)!), where r≤n, n!=n×(n−1)×...×3×2×1, and 0!=1.

 It is not until n=23, that a value exceeds one-million: (2310)=1144066.

 How many, not necessarily distinct, values of (ncr) for 1≤n≤100, are greater than one-million?
*/

int indexFirstBinomialAboveThresholdInRow(ll n, ll thresh){
    if(thresh < 1) return 0;
    ll binomial = 1;
    for(int r = 1; r <= n/2; r++){
        binomial *= n-r+1;
        binomial /= r;
        if(binomial > thresh) return r;
    }
    return -1;
}

int distinctBinomialAboveThreshold(int maxNum, ll thresh){
    int ans = 0;
    for(int n = 1; n <= maxNum; n++){
        int r = indexFirstBinomialAboveThresholdInRow(n, thresh);
        if(r == -1) continue;
        ans += n+1-2*r;
    }
    return ans;
}

int main(){
    Time(
        cout<<distinctBinomialAboveThreshold(100, 1000*1000);
    )
    return 0;
}

/*
Notes:
 Since for a particular n, nCr increases upto n/2 and then decreases symmetrically, we check for r = 0 to n/2. when we get something bigger
 than the threshold we know the rest upot n/2 will also be big. In particular if we get first big value at x then this will stay big until 
 n-x. This way we can get the count of all values that are big in a particular row.
 Complexity: O(n^2)
*/
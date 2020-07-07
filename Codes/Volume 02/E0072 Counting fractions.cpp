# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Consider the fraction, n/d, where n and d are positive integers. If n<d  and HCF(n,d)=1, it is called a reduced proper fraction.
 
 If we list the set of reduced proper fractions for d ≤ 8 in ascending  order of size, we get:
 
 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/ 3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
 
 It can be seen that there are 21 elements in this set.
 
 How many elements would be contained in the set of reduced proper  fractions for d ≤ 1,000,000?
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

ll countReducedFractionsTillDenominator(int bound){
    vector<int> phi = phiSieveTill(bound);
    ll ans = 0;
    for(int num = 2; num <= bound; num++){
        ans += phi[num];
    }
    return ans;
}

int main(){
    Time(
        cout<<countReducedFractionsTillDenominator(1000*1000)<<endl;
    )
    return 0;
}

/*
Notes:
 for a fixed d, n/d < 1 is reduced iff gcd(n, d) = 1, count of such n is phi(d) (except for d = 1). So we can just sum phi(2),... ,
 phi(bound). after finding the phi values by sieve.
 Complexity: O(n * log log n)
*/
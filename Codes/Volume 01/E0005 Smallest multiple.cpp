# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

 What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

ll LCM(ll x, ll y){
    ll g = __gcd(x, y);
    return x * (y/g);
}

ll smallestMultipleNumTill(int maxNum){
    ll lcm = 1;
    for(int num = 1; num <= maxNum; num++){
        lcm = LCM(lcm, num);
    }
    return lcm;
}

int main(){
    Time(
        cout<<smallestMultipleNumTill(20)<<endl;
    )
    return 0;
}

/*
Notes:
 smallest such multiple is lcm of the numbers, which can be computed by product/gcd rule.
 Complexity: O(n * log n)
*/
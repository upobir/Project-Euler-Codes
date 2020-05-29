# include <bits/stdc++.h>
# include "TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

 What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

ll smallestMultipleNumTill(int maxNum){
    ll lcm = 1;
    for(int num = 1; num <= maxNum; num++){
        ll product = num * lcm;
        lcm = product / __gcd(ll(num), lcm);
    }
    return lcm;
}

int main(){
    Time(
        cout<<smallestMultipleNumTill(20)<<endl;
    )
    return 0;
}
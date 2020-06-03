# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.
*/

vector<ll> sigmaSieveTill(int maxNum){
    vector<ll> sigma(maxNum+1);

    for(int d = 1; d <= maxNum; d++){
        for(int multiple = d; multiple <= maxNum; multiple += d)
            sigma[multiple]+=d;
    }
    return sigma;
}

ll sumOfAmicableNumbersUntil(int maxNum){
    ll sum = 0;
    int guessBound = 1.5*maxNum;
    vector<ll> sigma = sigmaSieveTill(guessBound);
    for(int num = 1; num < maxNum; num++){
        ll sumOfDiv = sigma[num];
        if(sumOfDiv > num && sumOfDiv - num <= guessBound && sumOfDiv != 2*num && sigma[sumOfDiv - num] == sumOfDiv){
            sum += num;
        }
    }
    return sum;
}

int main(){
    Time(
        cout<<sumOfAmicableNumbersUntil(10000)<<endl;
    )
    return 0;
}

/*
Notes:
 If x and y are amicable then sigma(x) = y+x = sigma(y) [sigma is sum of all divisors], so we can use sieve to find sigma[x] for numbers
 and find the corresponding y which should be amicable paired. Now this paired other number can be higher than the maxNum, so we use a guess
 to find sigma for upto 1.5*maxNum. Since sigma(x)-x will be around O(x), so this in general works.
 Complexity: O(n * log n)
*/
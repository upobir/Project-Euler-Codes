# include <bits/stdc++.h>
# include "../TimeMacro.h"
using namespace std;
typedef long long int ll;

/*
Statement:
 Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

 1634 = 1^4 + 6^4 + 3^4 + 4^4
 8208 = 8^4 + 2^4 + 0^4 + 8^4
 9474 = 9^4 + 4^4 + 7^4 + 4^4
 As 1 = 1^4 is not a sum it is not included.

 The sum of these numbers is 1634 + 8208 + 9474 = 19316.

 Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/

ll sumFuncDigits(ll num, vector<ll> &funcMap){
    ll sum = 0;
    while(num){
        int digit = num % 10;
        sum += funcMap[digit];
        num /= 10;
    }
    return sum;
}

ll sumOfNumberEqualPowerDigitSum(int exponent){
    int guessBoundDigits = llround(exponent*log10(9) + log10(exponent*log10(9)))+1;
    int guessBound = 1;
    for(int i = 0; i<guessBoundDigits; i++) guessBound *= 10;

    vector<ll> powerMap(10);
    for(int digit = 0; digit<10; digit++){
        powerMap[digit] = 1;
        for(int i = 0; i<exponent; i++) powerMap[digit] *= digit;
    }

    ll sum = 0;
    for(int num = 10; num <guessBound; num++){
        if(sumFuncDigits(num, powerMap) == num)
            sum += num;
    }

    return sum;
}

int main(){
    Time(
        cout<<sumOfNumberEqualPowerDigitSum(5)<<endl;
    )
}

/*
Notes:
 We check all numbers upto a limit, for the limit we find digit count k s.t. 10^k > k*9^exponent, that is even minimal number with that 
 many digit is greater than digit sum, a rough estimate to this is 10^k/k > 9^exponent = x -> k-log10(k) = log10(x) -> k = log10(x)+
 log10(log10(x))
 Complexity: O(10^(n+log n) * log n)
*/